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

    delay(1000);

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

void Display::HearthBeat(int beat_bpm)
{
    this->display.clearDisplay();

    // Print Heart Icon
    this->display.drawBitmap(
        (this->display.width() - HEART_ICON_WIDTH) / 2,
        10,
        HEART_ICON, HEART_ICON_WIDTH, HEART_ICON_HEIGHT, 1);

    // Print Heart Beat
    String heart_beat_msg = String(beat_bpm) + " BPM";

    Serial.println(heart_beat_msg);

    this->display.setTextSize(2);
    this->display.setTextColor(WHITE);
    this->display.setCursor(23, 40);
    this->display.print(heart_beat_msg);

    this->display.display();
}