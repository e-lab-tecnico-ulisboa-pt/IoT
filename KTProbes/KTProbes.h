/*
  KTProbes.h - Library to  read the conductivity and temperature probes with the Arduino Leonardo ETH.
  Created by Andre Torres, Feb 1, 2016.
*/
#ifndef KTProbes_h
#define KTProbes_h

#include "Arduino.h"

void configureIC1();
void configureIC3();
void enableIC(int timer,boolean enable);
ISR(TIMER1_CAPT_vect);
ISR(TIMER1_OVF_vect);
ISR(TIMER3_CAPT_vect);
ISR(TIMER3_OVF_vect);
long int readProbe(int n);


#endif