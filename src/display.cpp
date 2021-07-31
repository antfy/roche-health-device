#include <Arduino.h>

#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#include "display.h"
#include "display_images_bmp.h"

// construtores
Display::Display(uint8_t SCREEN_WIDTH, uint8_t SCREEN_HEIGHT, int DISPLAY_ADDRESS_I2C)
{
    this->SCREEN_WIDTH = SCREEN_WIDTH;
    this->SCREEN_HEIGHT = SCREEN_HEIGHT;
    this->DISPLAY_ADDRESS_I2C = DISPLAY_ADDRESS_I2C;

    // Declaration for an SSD1306 display connected to I2C (SDA, SCL pins)
    Adafruit_SSD1306 display(this->SCREEN_WIDTH, this->SCREEN_HEIGHT, &Wire, -1);

    this->display = display;
}

// funções
void Display::Start()
{

    if (!this->display.begin(SSD1306_SWITCHCAPVCC, this->DISPLAY_ADDRESS_I2C))
    {
        Serial.println(F("SSD1306 allocation failed"));
        for (;;)
            ;
    }

    this->display.clearDisplay();

    this->ShowStartingLogo();
}

void Display::ShowStartingLogo()
{
    this->display.clearDisplay();

    // Print Antfy Logo
    this->display.drawBitmap(
        (this->display.width() - ANTFY_LOGO_WIDTH) / 2,
        5,
        ANTFY_LOGO, ANTFY_LOGO_WIDTH, ANTFY_LOGO_HEIGHT, 1);

    // Print Starting message
    this->display.setTextSize(1);
    this->display.setTextColor(WHITE);

    for (int ponto = 1; ponto <= 4; ponto++)
    {
        this->display.setCursor(35, 50);

        switch (ponto)
        {
        case 1:

            this->display.println("Starting.");

            break;

        case 2:

            this->display.println("Starting..");

            break;
        case 3:

            this->display.println("Starting...");

            break;
        }

        delay(1000);
        this->display.display();
    }

    this->display.clearDisplay();
}

void Display::DisplayHearthBeat(int beat_bpm)
{
    this->display.clearDisplay();

    // Print Heart Icon
    this->display.drawBitmap(
        (this->display.width() - HEART_ICON_WIDTH) / 2,
        10,
        HEART_ICON, HEART_ICON_WIDTH, HEART_ICON_HEIGHT, 1);

    // Print Heart Beat
    String heart_beat_msg = String(beat_bpm);

    // Serial.println(heart_beat_msg);

    // Print Heart Beat
    this->display.setTextSize(2);
    this->display.setTextColor(WHITE);
    this->display.setCursor(30, 40);
    this->display.print(heart_beat_msg);

    // Print Heart Beat symbol
    this->display.setCursor(75, 40);
    this->display.print("BPM");

    this->display.display();
}

void Display::DisplayTemperature(float temp)
{

    this->display.clearDisplay();

    // Print Temp Icon
    this->display.drawBitmap(
        (this->display.width() - TEMPERATURA_ICON_WIDTH) / 2,
        8,
        TEMPERATURA_ICON, TEMPERATURA_ICON_WIDTH, TEMPERATURA_ICON_HEIGHT, 1);

    // Print Temp
    String temp_msg = String(temp, 1);

    // Serial.println(temp_msg);

    this->display.setTextSize(2);
    this->display.setTextColor(WHITE);
    this->display.setCursor(20, 40);
    this->display.print(temp_msg);

    // Print Temp symbol
    this->display.setCursor(85, 40);

    this->display.cp437(true);
    this->display.write(248); //  simbolo ° em Code page 437
    this->display.print("C");

    this->display.display();
}

void Display::DisplayOximeter(int SaO2)
{

    this->display.clearDisplay();

    // Print Oximeter Icon
    this->display.drawBitmap(
        (this->display.width() - OXIMETRO_ICON_ICON_WIDTH) / 2,
        8,
        OXIMETRO_ICON, OXIMETRO_ICON_ICON_WIDTH, OXIMETRO_ICON_ICON_HEIGHT, 1);

    // Print Oximeter
    String oxi_msg = String(SaO2);

    // Serial.println(oxi_msg);

    this->display.setTextSize(2);
    this->display.setTextColor(WHITE);
    this->display.setCursor(25, 40);
    this->display.print(oxi_msg);

    // Print Oximeter symbol
    this->display.setCursor(75, 40);
    this->display.print("SaO2");

    this->display.display();
}

void Display::DisplayBluetooth(bool connected)
{
    this->display.fillRect(110, 5, BlUETOOTH_DISCONNECTED_WIDTH, BlUETOOTH_DISCONNECTED_HEIGHT, BLACK);

    // this->display.clearDisplay();

    if (connected)
    {
        this->display.drawBitmap(
            110,
            5,
            BlUETOOTH_CONNECTED_ICON, BlUETOOTH_CONNECTED_ICON_WIDTH, BlUETOOTH_CONNECTED_ICON_HEIGHT, 1);
    }
    else
    {
        this->display.drawBitmap(
            110,
            5,
            BlUETOOTH_DISCONNECTED_ICON, BlUETOOTH_DISCONNECTED_WIDTH, BlUETOOTH_DISCONNECTED_HEIGHT, 1);
    }

    // this->display.setTextSize(2);
    // this->display.setTextColor(WHITE);
    // this->display.setCursor(25, 40);
    // this->display.print("Bluetooth Desconectado...");

    this->display.display();
}