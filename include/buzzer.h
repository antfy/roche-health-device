#include <Arduino.h>

class Buzzer
{
public:
    // Construtor
    Buzzer(uint8_t buzzerPin);

    // Métodos
    void Bip(int times, int delay_ms);

private:
    uint8_t buzzerPin;
};