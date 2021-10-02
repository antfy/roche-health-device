#include <Arduino.h>
#include <Wire.h>
// #include <Adafruit_MLX90614.h>
#include "sensor_temperatura.h"

void SensorTemperatura::Start()
{
    this->mlx = Adafruit_MLX90614();

    // Inicializa o MLX90614
    this->mlx.begin();
}

float SensorTemperatura::GetTempAmbiente()
{
   return (float) this->mlx.readAmbientTempC();
}

float SensorTemperatura::GetObjAmbiente()
{
    return (float) this->mlx.readObjectTempC();
}