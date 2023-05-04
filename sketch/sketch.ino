// Library for blynk connection
#include <WiFi.h>
#include <WiFiClient.h>
#include <BlynkSimpleEsp32.h>

// Credential for blynk
#define BLYNK_TEMPLATE_ID "TMPL61gaBi6XW"
#define BLYNK_TEMPLATE_NAME "Technocorner2"

// Credential for wifi
char ssid[] = "******************";///Enter your wifi name
char pass[] = "******************";// Enter wifi password
char auth[] = "3OWCiq-SwoQvyEv1DAsTJ_mK9Y9zmoTg";//Paste auth token you copied

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

// Interface for ds18b20
const int dsConnection = 4; //change number for certain port
OneWire oneWire(dsConnection);
DallasTemperature sensorDs(&oneWire);

// Define Maximum Value To Trigger Warning


// create global variable analog for each sensor
float rainSensorAnalogValue;
float soundSensorAnalogValue;
float pirSensorAnalogValue;
float infraredSensorAnalogValue;
float dsSensorAnalogValue;

// create global variable digital for each sensor
int rainSensorDigitalValue;
int soundSensorDigitalValue;
int pirSensorDigitalValue;
int infraredSensorDigitalValue;

// create task variable for multithreading
TaskHandle_t Task1;
TaskHandle_t Task2;

// create function for rainDrop algorithm
void RainDrop(int val1, int val2, int val3) {
  
}

// create function to read data from sesnor
void SecondThreadFunction () {
  // this function for second thread to read data from sensor

  for(;;) {
    // infinite loop for second thread to read sensor

    // start ds sensor
    sensorDs.requestTemperature();
    
    // read analog value of rain drop sensor
    rainSensorAnalogValue = analogRead(rainAnalog);
  
    // if necessary, read digital value 
    rainSensorDigitalValue = digitalRead(rainDigital);
  
    // read analog value of sound sensor
    soundSensorAnalogvalue = analogRead(soundAnalog);
  
    // read analog value of pir sensor
    pirSensorAnalogValue = analogRead(pirAnalog);
  
    // read analog value of infrared snesor
    infraredSensorAnalogValue = analogRead(infraredAnalog);

    // read analog value of ds sensor
    dsSensorAnalogValue = sensorDs.getTempCByIndex(0);
  
    // show value to serial monitor for checking, make comment if it's not necessary
    Serial.printf("Rain sensor analog value : %.2f \n", rainSensorAnalogValue);
    Serial.printf("Rain sensor digital value : %.2f \n", rainSensorDigitalValue);
    Serial.printf("Sound sensor analog value : %.2f \n", soundSensorAnalogValue);
    Serial.printf("Pir sensor analog value : %.2f \n", pirSensorAnalogValue);
    Serial.printf("Infrared sensor analog value : %.2f \n", infraredSensorAnalogValue);
    Serial.printf("DS Sensor analog value : $.2f \n", dsSensorAnalogValue);

    // send data to blynk using virtual pin
    Blynk.virtualWrite(V0, rainSensorAnalogValue);
    Blynk.virtualWrite(V1, soundSensorAnalogValue);
    Blynk.virtualWrite(V2, pirSensorAnalogValue);
    Blynk.virtualWrite(V3, infraredSensorAnalogValue);
    Blybk.virtualWrite(V4, dsSensorAnalogValue);
  }
}

void setup() {
  Serial.begin(115200);
  // declare pin for input
  // pinMode for rain sensor interface
  pinMode(rainAnalog, INPUT);
  pinMode(rainDigital, INPUT);

  // pinMode for sound sensor interface
  pinMode(soundAnalog, INPUT);

  // pinMode for pir sensor interface
  pinMode(pirAnalog, INPUT);

  // pinMode for infrared sensor interface
  pinMode(infraredAnalog, INPUT);
  pinMode(infraredDigital, INPUT);

  // begin blynk connection
  Blynk.begin(auth, ssid, pass);
}

void loop() {
  // put your main code here, to run repeatedly:
  
}
