#include <KTProbes.h>

#define ICP1_pin 4                   //ICP1 pin 4 
#define ICP3_pin 13                  //ICP3 pin 13 
void setup() {
 pinMode(ICP1_pin, INPUT);              // ICP1 pin (digital pin 4 on arduino) as input
  pinMode(ICP3_pin, INPUT);              // ICP3 pin (digital pin 13 on arduino) as input
  configureIC1();
  configureIC3();
  Serial.begin(9600);                // initialize serial communication at 9600 bits per second

}

void loop() {
  long int a=readProbe(0);
  Serial.print("sonda1: ");
  Serial.print(a);
  Serial.println(" Hz");
  long int b=readProbe(1);
  Serial.print("sonda2: ");
  Serial.print(b);
  Serial.println(" Hz");  
  delay(1000);

}
