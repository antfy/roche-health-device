// LIBS ##############################################################
#include <Arduino.h>
#include <iostream>

#include <BLEDevice.h>
#include <BLEServer.h>
#include <BLEUtils.h>
#include <BLE2902.h>

#include <ArduinoJson.h>

#include "display.h"

// VARIAVEIS GLOBAIS #############################################################

// Display
#define SCREEN_WIDTH 128         // OLED display width, in pixels
#define SCREEN_HEIGHT 64         // OLED display height, in pixels
#define DISPLAY_ADDRESS_I2C 0x3C // OLED display I2C address

Display display(SCREEN_WIDTH, SCREEN_HEIGHT, DISPLAY_ADDRESS_I2C);

// Bluetooth
BLECharacteristic *bleSendCharacteristic = NULL;
BLEServer *bleServer = NULL;
bool deviceConnected = false;
bool startBleReconnection = false;


// Sensores
StaticJsonDocument<200> sensorsData;

#define SERVICE_UUID "4eba7cbc-a351-464c-bd64-5a0af8b52a8b" // UART service UUID
#define CHARACTERISTIC_UUID_RX "cc0eace0-430b-4ccd-add4-6556737c882b"
#define DHTDATA_CHAR_UUID "0d7df51f-d18f-4617-b0f4-f5c30fc5a0d3"
#define BLUETOOTH_NAME "ESP32_DEV"

// PROTÓTIPOS DE FUNÇÕES ########################################################

// Bluetooth
void bleInit();
void bleReconnect(BLEServer *bleServer);

// CLASSES GLOBAIS ##############################################################

class BluetoothServerCallbacks : public BLEServerCallbacks
{
  void onConnect(BLEServer *pServer)
  {
    Serial.println("Bluetooth Conectado");
    deviceConnected = true;
  };

  void onDisconnect(BLEServer *pServer)
  {
    Serial.println("Bluetooth Desconectado");
    deviceConnected = false;
    startBleReconnection = true;
  }
};

class BluetoothDataReceivedCallbacks : public BLECharacteristicCallbacks
{
  void onWrite(BLECharacteristic *bleSendCharacteristic)
  {
    std::string rxValue = bleSendCharacteristic->getValue();

    if (rxValue.length() > 0)
    {
      Serial.println("*********");
      Serial.print("Received Value: ");

      for (int i = 0; i < rxValue.length(); i++)
      {
        Serial.print(rxValue[i]);
      }
      Serial.println();
      Serial.println("*********");
    }

    // Processa o caracter recebido do aplicativo. Se for A acende o LED. B apaga o LED
    if (rxValue.find("A") != -1)
    {
      Serial.println("A");
    }
    else if (rxValue.find("B") != -1)
    {
      Serial.println("B");
    }
  }
};

// SETUP ##########################################################################
void setup()
{

  // Inicializando porta serial
  Serial.begin(115200);
  while (!Serial)
    continue;

  // Inicializando o bluetooth
  bleInit();

  // Inicializando display OLED
  display.Start();
  display.DisplayBluetooth(deviceConnected);
  delay(5000);
}

// LOOP ####################################################################
void loop()
{

  display.DisplayBluetooth(deviceConnected);

  // Dispositivo conectado via bluetooth
  while (deviceConnected)
  {
      
    // heart beat
    display.DisplayHearthBeat(10);
    display.DisplayBluetooth(deviceConnected);
    delay(1000);
    display.DisplayHearthBeat(140);
    display.DisplayBluetooth(deviceConnected);
    delay(1000);

    sensorsData["heartBeat"] = 140;

    // temperature
    display.DisplayTemperature(13);
    display.DisplayBluetooth(deviceConnected);
    delay(1000);
    display.DisplayTemperature(25.5);
    display.DisplayBluetooth(deviceConnected);
    delay(1000);

    sensorsData["temperature"] = 25.5;

    // oximeter
    display.DisplayOximeter(3);
    display.DisplayBluetooth(deviceConnected);
    delay(1000);
    display.DisplayOximeter(30);
    display.DisplayBluetooth(deviceConnected);
    delay(1000);
    display.DisplayOximeter(300);
    display.DisplayBluetooth(deviceConnected);
    delay(1000);

    sensorsData["oximeter"] = 300;

    // Enviando um valor por bluetooth
    // float valor = 19.78;
    char txString[200];
    // dtostrf(valor, 2, 2, txString);

    // String output;
    serializeJson(sensorsData, txString);

    Serial.println(txString);
    // serializeJsonPretty(sensorsData, Serial);

    bleSendCharacteristic->setValue(txString);
    bleSendCharacteristic->notify();
  }

  // Dispositivo desconectado ao bluetooth]
  // Inicializa a reconexão com o bluetooth
  if (startBleReconnection)
  {
    bleReconnect(bleServer);
    startBleReconnection = false;
  }
}

void bleInit()
{
  // Cria um dispositivo BLE
  uint16_t mtu = 200;
  BLEDevice::setMTU(mtu); // tamanho do pacote em bytes que o servidor bluetooth enviará. Esse parametro deve ser setado no smartphone também
  BLEDevice::init(BLUETOOTH_NAME);

  // Configura o dispositivo como Servidor BLE
  BLEServer *bleServer = BLEDevice::createServer();
  bleServer->setCallbacks(new BluetoothServerCallbacks());
  
  // Cria o servico UART
  BLEService *bleService = bleServer->createService(SERVICE_UUID);

  // Cria uma Característica BLE para envio dos dados
  bleSendCharacteristic = bleService->createCharacteristic(
      DHTDATA_CHAR_UUID,
      BLECharacteristic::PROPERTY_NOTIFY);

  bleSendCharacteristic->addDescriptor(new BLE2902());

  // Cria uma Característica BLE para recebimento de dados
  BLECharacteristic *bleReceiveCharacteristic = bleService->createCharacteristic(
      CHARACTERISTIC_UUID_RX,
      BLECharacteristic::PROPERTY_WRITE);

  bleReceiveCharacteristic->setCallbacks(new BluetoothDataReceivedCallbacks());

  // Inicia o serviço
  bleService->start();

  // Inicia a descoberta do ESP32
  bleServer->getAdvertising()->start();
  Serial.println("Esperando conexão Bluetooth...");
}

void bleReconnect(BLEServer *bleServer)
{

  // Inicia a descoberta do ESP32
  bleServer->startAdvertising();

  Serial.println("Reconectado ao Bluetooth...");
}