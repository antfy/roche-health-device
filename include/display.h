#include <Arduino.h>

#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

class Display
{

public:
    // construtores
    Display(uint8_t SCREEN_WIDTH, uint8_t SCREEN_HEIGHT, int DISPLAY_ADDRESS_I2C);

    // funções
    void Start();

    void DisplayHearthBeat(int beat_bpm);
    void DisplayTemperature(float temp);
    void DisplayOximeter(int SaO2);
    void DisplayBluetooth(bool connected);

private:
    // funções
    void ShowStartingLogo();
    
    // atributos
    Adafruit_SSD1306 display;
    uint8_t SCREEN_WIDTH{128};
    uint8_t SCREEN_HEIGHT{64};
    
    int DISPLAY_ADDRESS_I2C{0x3C};
    
};