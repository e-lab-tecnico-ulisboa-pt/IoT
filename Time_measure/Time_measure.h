/*
  Time_measure.h - Library to  measure times.
*/
#ifndef Time_measure_h
#define Time_measure_h
#include "Arduino.h"

void configureIC(int z);
void enableIC(boolean enable);
void isr_pin(void);
ISR(TIMER1_CAPT_vect);
ISR(TIMER1_OVF_vect);
float measureTime();


#endif