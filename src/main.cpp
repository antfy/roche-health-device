#include <Arduino.h>

#include "display.h"

#define SCREEN_WIDTH 128         // OLED display width, in pixels
#define SCREEN_HEIGHT 64         // OLED display height, in pixels
#define DISPLAY_ADDRESS_I2C 0x3C // OLED display I2C address

Display display(SCREEN_WIDTH, SCREEN_HEIGHT, DISPLAY_ADDRESS_I2C);

void setup()
{

  // Inicializando porta serial
  Serial.begin(115200);
  while (!Serial)
    continue;

  // Inicializando display OLED
  display.Start();
}

void loop()
{
  // heart beat
  display.DisplayHearthBeat(1);
  delay(2000);
  display.DisplayHearthBeat(10);
  delay(2000);
  display.DisplayHearthBeat(100);
  delay(2000);

  // temperature
  display.DisplayTemperature(1.0);
  delay(2000);
  display.DisplayTemperature(10.345);
  delay(2000);
  display.DisplayTemperature(100.67);
  delay(2000);

  // oximeter
  display.DisplayOximeter(3);
  delay(2000);
  display.DisplayOximeter(30);
  delay(2000);
  display.DisplayOximeter(300);
  delay(2000);
}