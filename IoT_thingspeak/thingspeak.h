#ifndef THINGSPEAK_H
#define THINGSPEAK_H

#include <SPI.h>
#include <Ethernet2.h>

#define APIKEY "OBJFRNXGB2B8ZP9I"
#define UPDATE_PERIOD 2000 //ms
#define VERBOSE 0

extern void startEthernet();
extern void thingspeak_loop();
extern int updateThingSpeak(String tsData);

#endif
