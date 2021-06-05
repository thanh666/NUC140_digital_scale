#ifndef _HX711_H_
#define _HX711_H_

#include "main.h"
#include <stdint.h>



void init_hx711(char dout, char pd_sck, char gain);
char is_ready(void);
void wait_ready(int ms);
char wait_ready_retry(int retries, int ms);

void set_gain(uint8_t gain);

long read(void);

long read_average(char times);

// returns (read_average() - OFFSET)
double get_value(char times);

// returns get_value() divided by SCALE
float get_units(char times);

// set the OFFSET value for tare weight;
void tare(char times);

// set the SCALE value; this value is used to convert the raw data to "human readable" data (measure units)
void set_scale(float scale);

// get the current SCALE
float get_scale(void);
	
// set OFFSET, the value that's subtracted from the actual reading (tare weight)
void set_offset(long offset);

// get the current OFFSET
long get_offset(void);

// puts the chip into power down mode
void power_down(void);

// wakes up the chip after power down mode
void power_up(void);

#endif

