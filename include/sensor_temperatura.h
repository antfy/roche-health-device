#include <Arduino.h>
#include <Wire.h>
#include <Adafruit_MLX90614.h>

class SensorTemperatura
{
public:
    void Start();

    float GetTempAmbiente();
    float GetObjAmbiente();

private:
    Adafruit_MLX90614 mlx;
};