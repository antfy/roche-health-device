#include <Arduino.h>
#include "buzzer.h"

// Construtor
Buzzer::Buzzer(uint8_t buzzerPin)
{
    this->buzzerPin = buzzerPin;

    pinMode(this->buzzerPin, OUTPUT);
}

// Métodos
void Buzzer::Bip(int times, int delay_ms)
{
    for (int i = 0; i < times; i++)
    {
        digitalWrite(this->buzzerPin, HIGH);
        delay(delay_ms);
        digitalWrite(this->buzzerPin, LOW);
        delay(delay_ms);
    }
    
}