// Library for blynk connection
#include <WiFi.h>
#include <WiFiClient.h>
#include <BlynkSimpleEsp32.h>

// library for DS18B20
#include <OneWire.h>
#include <DallasTemperature.h>

// Credential for blynk
#define BLYNK_TEMPLATE_ID "TMPL61gaBi6XW"
#define BLYNK_TEMPLATE_NAME "Technocorner2"

// library for AHT-10
#include <Adafruit_AHTX0.h>

// library for rain drop sensor
#define rainAnalog 1 
#define rainDigital 1 //(redefined later digital pin for rain drop data stream)

// Library for sound sensor
#define soundAnalog 2 //(redefined later analog pin for sound data stream)

// Library for pir sensor
#define pirAnalog 3 //(redefined later analog pin for pir data stream)

// Interface for infrared sensor
#define infraredAnalog 4 //(analog pin for infrared data stream)
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

// Credential for wifi
char ssid[] = "Kost Atria";///Enter your wifi name
char pass[] = "atriakost";// Enter wifi password
char auth[] = "3OWCiq-SwoQvyEv1DAsTJ_mK9Y9zmoTg";//Paste auth token you copied

// create task variable for multithreading
TaskHandle_t Task1, Task2;

// first thread function
void firstThreadFunction(void * parameter) {
  // start blybk
  Blynk.begin(auth, ssid, pass);
  for(;;) {
    Serial.println("Main Thread running....");
    // run blynk
    Blynk.run();
    
    //     send data to blynk using virtual pin
    Blynk.virtualWrite(V0, rainSensorAnalogValue);
    Blynk.virtualWrite(V1, soundSensorAnalogValue);
    Blynk.virtualWrite(V2, pirSensorAnalogValue);
    Blynk.virtualWrite(V3, infraredSensorAnalogValue);
    Blynk.virtualWrite(V4, dsSensorAnalogValue);
    delay(500);
    Serial.println("Data Send to Blynk");
  }
}

// create function to read data from sesnor
void secondThreadFunction (void * parameter) {
  // this function for second thread to read data from sensor

  for(;;) {
    // infinite loop for second thread to read sensor

    // start ds sensor
    sensorDs.requestTemperatures();
    
    // read analog value of rain drop sensor
    rainSensorAnalogValue = analogRead(rainAnalog);
  
    // read analog value of sound sensor
    soundSensorAnalogValue = analogRead(soundAnalog);
  
    // read analog value of pir sensor
    pirSensorAnalogValue = analogRead(pirAnalog);
  
    // read analog value of infrared snesor
    infraredSensorAnalogValue = analogRead(infraredAnalog);

    // read analog value of ds sensor
    dsSensorAnalogValue = sensorDs.getTempCByIndex(0);
  
    // show value to serial monitor for checking, make comment if it's not necessary
    Serial.printf("Rain sensor analog value : %.2f \n", rainSensorAnalogValue);
    Serial.printf("Sound sensor analog value : %.2f \n", soundSensorAnalogValue);
    Serial.printf("Pir sensor analog value : %.2f \n", pirSensorAnalogValue);
    Serial.printf("Infrared sensor analog value : %.2f \n", infraredSensorAnalogValue);
    Serial.printf("DS Sensor analog value : %.2f \n", dsSensorAnalogValue);
    Serial.printf("---------- NEW LINE ----------- \n\n");

    delay(1000);
  }
}

void setup() {
  Serial.begin(115200);

//  // pinMode for rain sensor interface
//  pinMode(rainDigital, INPUT);
//
//  // pinMode for infrared sensor interface
//  pinMode(infraredDigital, INPUT);

  // begin blynk connection
  Serial.println("Start to add task");

  // Add task to thread
  xTaskCreatePinnedToCore(    firstThreadFunction,    "Main Thread Function",    10000,      NULL,    2,    &Task1,    0);
   //delay(500);  // needed to start-up task1
  xTaskCreatePinnedToCore(    secondThreadFunction,    "Second Thread Function",    10000,    NULL,    2,    &Task2,    1);
}

void loop() {
  // put your main code here, to run repeatedly:
  
}
