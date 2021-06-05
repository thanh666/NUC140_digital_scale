#ifndef _MAIN_H_
#define _MAIN_H_

#include <stdio.h>
#include "NUC1xx.h"
#include "Driver\DrvSYS.h"
#include "Driver\DrvGPIO.h"
#include "LCD_Driver.h"
#include "Seven_Segment.h"
#include "Switches.h"
#include "port.h"
#include "eos.h"
#include "hx711.h"

void InitTIMER0(void);
void delay_loop(void);
//void TMR0_IRQHandler(void);
void Timer_initial(void);
void clock_init(void);
void delay_ms(int ms);
void  delay_t0(unsigned long ms);
void sleep_mode(void);
void deep_sleep_mode(void);

#endif
