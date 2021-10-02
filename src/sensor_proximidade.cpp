#include <Arduino.h>
#include "sensor_proximidade.h"

// Construtor
SensorProximidade::SensorProximidade(uint8_t digitalPin)
{
    this->digitalPin = digitalPin;
    pinMode(this->digitalPin, INPUT_PULLUP);
}

// Método
bool SensorProximidade::Activated()
{
    return digitalRead(this->digitalPin) ? false : true;
}