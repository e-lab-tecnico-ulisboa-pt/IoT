#include <Time_measure.h>
#include <SPI.h>
#include <Ethernet2.h>

#include "thingspeak.h"

#define pin_IC 4
void setup() {
 pinMode(pin_IC, INPUT);              // ICP1 pin (digital pin 4 on arduino) as input
  configureIC(0);
  Serial.begin(9600);                // initialize serial communication at 9600 bits per second
  while (!Serial);
    startEthernet(); // Start Ethernet on Arduino
}

void loop() {
    thingspeak_loop();
  float a=measureTime();
  Serial.print(1/a,5);
  Serial.println(" Hz");
   String analogValue0 = String(1/a, DEC);
   updateThingSpeak("field2="+analogValue0+"&field2="+analogValue0);
  delay(4000);
}
