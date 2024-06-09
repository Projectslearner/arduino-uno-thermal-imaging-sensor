/*
    Project name : Thermal Imaging Sensor
    Modified Date: 09-06-2024
    Code by : Projectslearner
    Website : https://projectslearner.com/learn/arduino-uno-thermal-imaging-sensor
*/

#include <Wire.h>
#include <SparkFunMLX90640.h>

#define MLX90640_ADDR 0x33 // Default I2C address of MLX90640
#define TA_SHIFT 8          // Default shift for MLX90640 temperature calculation

MLX90640 mlx;

void setup()
{
  Serial.begin(9600);
  Wire.begin();
  
  // Initialize MLX90640
  if (!mlx.begin(MLX90640_ADDR)) {
    Serial.println("Failed to communicate with MLX90640 sensor.");
    while (1);
  }
  
  // Set refresh rate (2 Hz by default)
  mlx.setRefreshRate(MLX90640::RATE_2_HZ);
}

void loop()
{
  float frame[768]; // 24x32 pixels
  float mlx90640To[192];
  
  // Get new data from MLX90640
  if (mlx.getFrame(frame)) {
    // Calculate object temperatures
    mlx.temperatureToSerial(frame, TA_SHIFT);
  }
}
