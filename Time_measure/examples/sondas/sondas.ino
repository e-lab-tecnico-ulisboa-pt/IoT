#include <Time_measure.h>

#define pin_IC 4
void setup() {
 pinMode(pin_IC, INPUT);              // ICP1 pin (digital pin 4 on arduino) as input
  configureIC(0);
  Serial.begin(9600);                // initialize serial communication at 9600 bits per second
  while (!Serial);
}

void loop() {
  float a=measureTime();
  Serial.print(1/a,5);
  Serial.println(" Hz");
  delay(4000);
}
