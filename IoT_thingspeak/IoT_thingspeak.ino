#include <SPI.h>
#include <Ethernet2.h>

#include "thingspeak.h"

void setup()
{
  Serial.begin(9600); // Start Serial for debugging on the Serial Monitor
  startEthernet(); // Start Ethernet on Arduino

}

void loop()
{
  thingspeak_loop();
     
  String analogValue0 = String(analogRead(A0), DEC);
  String analogValue1 = String(analogRead(A1), DEC);
  
  updateThingSpeak("field2="+analogValue0+"&field2="+analogValue1);

  delay(1000);
}
