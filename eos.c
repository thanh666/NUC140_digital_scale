#include "eos.h"

void timer_interrupt_init(unsigned long x)
{ 	
	SYSCLK->CLKSEL1.TMR0_S = 0;	//Select 12Mhz for Timer0 clock source
  SYSCLK->APBCLK.TMR0_EN = 1;	//Enable Timer0 clock source
	TIMER0->TCSR.MODE =  1;  //periodic mode
	TIMER0->TCSR.PRESCALE = 119;  // Set Prescale [0~255]
      TIMER0->TCMPR = 100*x;	 // Set TCMPR [0~16777215]
//Timeout = (1 / 12MHz) * ( 119 + 1 ) * 100 *x  (ms)
      TIMER0->TCSR.CRST = 1;	//Reset up counter
      TIMER0->TCSR.CEN = 1;		//Enable Timer0
	TIMER0->TISR.TIF = 1; //clear TIF
	TIMER0->TCSR.IE = 1; // enable interrupt
	NVIC_EnableIRQ(TMR0_IRQn);	//Enable Timer0 Interrupt  
}
/*
* @fn  EOS_init (unsigned int x)
 * @brief   Initialize for Embedded Operating System:
 *            - timer interrupt in next x microsecond
 * @param  x : number of microsecond
 * @return  void */
void  EOS_init(unsigned int ms)
{
	SysTick->LOAD  = 12000000/1000*ms - 1;      /* set reload register*/ 
	SysTick->VAL   = 0;                     /*Load the SysTick Counter Value */
/* Enable SysTick IRQ and SysTick Timer */
	SysTick->CTRL  = 3; // ENABLE+ TICKINT
	DrvSYS_SelectSysTickSource(0); //select 12MHz
}


