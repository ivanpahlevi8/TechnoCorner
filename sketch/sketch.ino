// library for DS18B20
#include <OneWire.h>
#include <DallasTemperature.h>

// library for AHT-10
#include <Adafruit_AHTX0.h>

// library for rain drop sensor
#define rainAnalog A1 //(redefined later analog pin for rain drop data stream)
#define rainDigital 1 //(redefined later digital pin for rain drop data stream)

// Library for sound sensor
#define soundAnalog A2 //(redefined later analog pin for sound data stream)

// Library for pir sensor
#define pirAnalog A3 //(redefined later analog pin for pir data stream)

// Interface for infrared sensor
#define infraredAnalog A4 //(analog pin for infrared data stream)
#define infraredDigital 2 //(digital pin for infrared data stream)

// Define Maximum Value To Trigger Warning

// create global variable analog for each sensor
int rainSensorAnalogValue;
int soundSensorAnalogValue;
int pirSensorAnalogValue;
int infraredSensorAnalogValue;

// create global variable digital for each sensor
int rainSensorDigitalValue;
int soundSensorDigitalValue;
int pirSensorDigitalValue;
int infraredSensorDigitalValue;

// create function for rainDrop algorithm
void RainDrop(int val1, int val2, int val3) {
  if
}

// create function to read data from sesnor
void SecondThreadFunction () {
  // this function for second thread to read data from sensor
}

void setup() {
  // declare pin for input
  
}

void loop() {
  // put your main code here, to run repeatedly:
  
}
