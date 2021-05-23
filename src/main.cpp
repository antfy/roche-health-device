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

int i = 100;

void loop()
{
  if (i > 190)
  {
    i = 100;
  };

  display.HearthBeat(i);

  delay(1000);
  i++;
}