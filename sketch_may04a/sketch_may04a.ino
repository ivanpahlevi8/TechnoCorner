// create incremental variable global
int i = 0;

// create decremental variable global
int j = 1000;

TaskHandle_t Task1, Task2;

void codeForTask1( void * parameter ) {
   for (;;) {
      i++;
      Serial.print("Code is running on Core: ");
      Serial.println( xPortGetCoreID());
      Serial.print("Increment value : ");
      Serial.println(i);
      Serial.println("");
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
