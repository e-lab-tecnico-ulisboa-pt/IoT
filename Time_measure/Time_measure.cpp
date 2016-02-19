/*
  Time_measure.cpp - Library to  measure times.
*/
#include "Arduino.h"
#include "Time_measure.h"

volatile float ics[12];    //matrix to hold the probes values
volatile unsigned int i = 0, ovf=0;          //iterator
volatile boolean aquire = false;  //flags
volatile boolean ovfl = false;  //overflow flags
volatile int modoop;
volatile double over[2];
int detetor_pin=7;

void configureIC(int z) {
  modoop = z;
  if (z == 0)
  {
    TCCR1A = 0;
    TCCR1B = 0b00000010;               //Noise canceler OFF; IC on falling edge; PS(3 LSBs) =8
    TIMSK1 |= (1 << ICIE1);            //Enable IC
    TIFR1 |= (1 << ICF1);              //Enable IC flag
    TIMSK1 |= (1 << TOIE1);            //Enable Overflow
    TIFR1 |= (1 << TOV1);              //Enable Overflow flag
  }
  if (z == 1)
  {
    TCCR1A = 0;
    TCCR1B = 0b0000101;               //Noise canceler OFF; IC on falling edge; PS(3 LSBs) =8
    TIMSK1 |= (1 << TOIE1);            //Enable Overflow
    TIFR1 |= (1 << TOV1);              //Enable Overflow flag
    Serial.println("OI");
    attachInterrupt(digitalPinToInterrupt(detetor_pin), isr_pin, CHANGE);
  }
}
void enableIC(boolean enable) {
  TIMSK1 = (enable == true) ? (TIMSK1 | (1 << ICIE1)) : (TIMSK1 & ~(1 << ICIE1)); //enables/disables IC
}
ISR(TIMER1_CAPT_vect) {
  TCNT1 = 0;                               // reset the counter
  ics[i] = ICR1;                        // save IC buf in array
  //Serial.println(ICR1);
  if (i == 11) {
    enableIC(false);                  // disable input capture interrupt for timer 1
    aquire = false;
  }
  i++;
}

ISR(TIMER1_OVF_vect) {
  ovf++;
}

void isr_pin(void) {
  ics[i] = TCNT1;           // save IC buf in array
  over[i]=ovf;
  i++;
}

float measureTime() {
  if (modoop == 0)
  {
    i = 0;
    float media = 0;
    aquire = true;
    ovfl = false;
    enableIC(true);
    while (aquire == true) {
      if (ovfl == true) {
        aquire = false;
        return 0;
      }
    }             //wait
    for (int j = 2; j < 12; j++) {
      float valor1 = 1. / (float)F_CPU * 8.*(float)ics[j];
      media = (media * (float)(j - 2) + valor1) / (float)(j - 1);
    }

    return (media);

  }

  if (modoop == 1)
  {
    i = 0;
    aquire = true;
    ovfl = false;
    //enableIC(true);
    while (aquire == true & i < 2);
    i=0;
    aquire = false;
    return ((ics[1]- ics[0] + (over[1]- over[0]) * 65536.) * 1024. / F_CPU);
  }
}
