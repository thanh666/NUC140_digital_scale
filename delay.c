#include "main.h"

void delay_loop(void)
 {
 uint32_t i,j;
	for(i=0;i<3;i++)	
	{
		for(j=0;j<60000;j++);
    }
 
}
void delay_ms(int ms)
{
	int i;
	for(i=0;i<ms;i++)
		DrvSYS_Delay(500);		//delay 1ms
} 

void  delay_t0(unsigned long x)
{ 	SYSCLK->CLKSEL1.TMR0_S = 0;	//Select 12Mhz for Timer0 clock source
      SYSCLK->APBCLK.TMR0_EN = 1;	//Enable Timer0 clock source
	TIMER0->TCSR.MODE =  0;  //one shot mode
	TIMER0->TCSR.PRESCALE = 119;  // Set Prescale [0~255]
      TIMER0->TCMPR = 100*x;	 // Set TCMPR [0~16777215]
//Timeout = (1 / 12MHz) * ( 119 + 1 ) * 100 *x  (ms)
      TIMER0->TCSR.CRST = 1;	//Reset up counter
      TIMER0->TCSR.CEN = 1;		//Enable Timer0
	TIMER0->TISR.TIF = 1; //clear TIF
	TIMER0->TCSR.IE = 1; // enable interrupt
	 while(TIMER0->TISR.TIF == 0);
}



