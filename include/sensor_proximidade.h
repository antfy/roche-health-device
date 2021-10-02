#include <Arduino.h>

class SensorProximidade {
    public:
        // Construtor
        SensorProximidade(uint8_t digitalPin);
        
        // Métodos
        bool Activated();

    private:
        bool state;
        uint8_t digitalPin;
};