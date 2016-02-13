/*
  KTProbes.cpp - Library to  read the conductivity and temperature probes with the Arduino Leonardo ETH.
  Created by Andre Torres, Feb 1, 2016.
*/
#include "Arduino.h"
#include "KTProbes.h"

volatile unsigned int ics[2][12];    //matrix to hold the probes values
volatile unsigned int i=0;            //iterator
volatile boolean aquire[2]={false, false};    //flags
volatile boolean ovfl[2]={false, false};    //overflow flags


void configureIC1(){
  TCCR1A=0;
  TCCR1B=0b00000010;                 //Noise canceler OFF; IC on falling edge; PS(3 LSBs) =8
  TIMSK1|= (1<<ICIE1);               //Enable IC 
  TIFR1|= (1<<ICF1);                 //Enable IC flag
  TIMSK1|= (1<<TOIE1);               //Enable Overflow 
  TIFR1|= (1<<TOV1);                 //Enable Overflow flag
}

void SetTimer3(){
  TCCR3A=0;
  TCCR3B=0b00000010;                 //Noise canceler OFF; IC on falling edge; PS(3 LSBs) =8
  TIMSK3|= (1<<ICIE3);               //Enable IC 
  TIFR3|= (1<<ICF3);                 //Enable IC flag
  TIMSK1|= (1<<TOIE3);               //Enable Overflow 
  TIFR1|= (1<<TOV3);                 //Enable Overflow flag
}
void enableIC(int timer,boolean enable){
  if (timer==0)
    TIMSK1=(enable==true)?(TIMSK1 | (1<<ICIE1)):(TIMSK1 & ~(1<<ICIE1));  //enables/disables IC
  else if (timer==1)
    TIMSK3=(enable==true)?(TIMSK3 | (1<<ICIE3)):(TIMSK3 & ~(1<<ICIE3));  //enables/disables IC
}

ISR(TIMER1_CAPT_vect){ 
  TCNT1 = 0;                               // reset the counter 
  ics[0][i]=ICR1;                          // save IC buf in array
if (i==11){
   enableIC(0,false);                  // disable input capture interrupt for timer 1
   aquire[0]=false;
 }
    i++;
}
ISR(TIMER1_OVF_vect){ 
  ovfl[0]=true;
}
ISR(TIMER3_CAPT_vect){ 
  TCNT3 = 0;                               // reset the counter 
  ics[1][i]=ICR3;
if (i==11){
   enableIC(1,false);                  // disable input capture interrupt for timer 3
   aquire[1]=false;
 }
    i++;
}
ISR(TIMER3_OVF_vect){ 
  ovfl[1]=true;
}
long int readProbe(int n){
  if (n != 0 && n!= 1) return 0;     //input discrimination
  i=0;
  float media=0;  
  aquire[n]=true;
  ovfl[n]=false;  
  enableIC(n,true);
  while(aquire[n]==true){
  if(ovfl[n]==true){
    ovfl[n]=true;
    aquire[n]=false;
    return 0;
    }  
  }             //wait 
  for(int j=2;j<12;j++){
    float valor1 = 1./(float)F_CPU*8.*(float)ics[n][j];
    media=(media*(float)(j-2)+valor1)/(float)(j-1);
  }
  return ((long int)(1./media));
}