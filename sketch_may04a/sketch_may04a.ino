// library for DS18B20
#include <OneWire.h>
#include <DallasTemperature.h>
// create global variable analog for each sensor
float rainSensorAnalogValue;
float soundSensorAnalogValue;
float pirSensorAnalogValue;
float infraredSensorAnalogValue;
float dsSensorAnalogValue;

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

// create global variable digital for each sensor
int rainSensorDigitalValue;
int soundSensorDigitalValue;
int pirSensorDigitalValue;
int infraredSensorDigitalValue;
// create incremental variable global
int i = 0;

// create decremental variable global
int j = 1000;

TaskHandle_t Task1, Task2;

void codeForTask1( void * parameter ) {
   for (;;) {
      // read analog value of rain drop sensor
    rainSensorAnalogValue = analogRead(rainAnalog);
  
    // if necessary, read digital value 
    rainSensorDigitalValue = digitalRead(rainDigital);
  
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
    Serial.printf("Rain sensor digital value : %.2f \n", rainSensorDigitalValue);
    Serial.printf("Sound sensor analog value : %.2f \n", soundSensorAnalogValue);
    Serial.printf("Pir sensor analog value : %.2f \n", pirSensorAnalogValue);
    Serial.printf("Infrared sensor analog value : %.2f \n", infraredSensorAnalogValue);
    Serial.printf("DS Sensor analog value : $.2f \n", dsSensorAnalogValue);
   }
}
void codeForTask2( void * parameter ) {
   for (;;) {
      j--;
      Serial.print("Code is running on Core: ");
      Serial.println( xPortGetCoreID());
      Serial.print("Decrement value : ");
      Serial.println(j);
      Serial.println("");
   }
}

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  
   xTaskCreatePinnedToCore(    codeForTask1,    "IncrementTask",    5000,      NULL,    2,    &Task1,    0);
   //delay(500);  // needed to start-up task1
   xTaskCreatePinnedToCore(    codeForTask2,    "DecrementTask",    5000,    NULL,    2,    &Task2,    1);
}

void loop() {
  // put your main code here, to run repeatedly:

}
