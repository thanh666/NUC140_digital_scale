/* THIS CODE IS CREATED BY CONG THANH */
/* Email: vcthanh20@gmail.com */
/* PLEASE KEEP THIS LINE WHEN USING THIS LIB */

#include "main.h"
long weight;
void InitTIMER0(void)
{
	/* Step 1. Enable and Select Timer clock source */          
	SYSCLK->CLKSEL1.TMR0_S = 0;	//Select 12Mhz for Timer0 clock source 
	SYSCLK->APBCLK.TMR0_EN = 1;	//Enable Timer0 clock source
	/* Step 2. Select Operation mode */	
	TIMER0->TCSR.MODE = 1; //Select operation mode
	/* Step 3. Select Time out period = (Period of timer clock input) * (8-bit Prescale + 1) * (24-bit TCMP)*/
	TIMER0->TCSR.PRESCALE = 100;  // Set Prescale [0~255]
	TIMER0->TCMPR = 600;	   // Set TCMPR [0~16777215]
	//Timeout period = (1 / 12MHz) * ( 100 ) * 600 = 5 msec
	/* Step 4. Enable interrupt */
	TIMER0->TCSR.IE = 1;
	TIMER0->TISR.TIF = 1;	//Write 1 to clear for safty		
	NVIC_EnableIRQ(TMR0_IRQn);	//Enable Timer0 Interrupt
	/* Step 5. Enable Timer module */
	TIMER0->TCSR.CRST = 1;	//Reset up counter
	TIMER0->TCSR.CEN = 1;	//Enable Timer0
//	TIMER0->TCSR.TDR_EN=1;	// Enable TDR function
}

void TMR0_IRQHandler()
{
	unsigned int i;
	char buff[4] = {0, 0, 0, 0};
	
	if(weight==0)
	{
		buff[3] = 11;
		buff[2] = 11;
		buff[1] = 11;
		buff[0] = 0;
		DrvGPIO_SetBit(E_GPB, 11);	//tat loa
	}
	else if(weight>0)
	{
		if(weight<=10)
		{
			buff[3] = 11;
			buff[2] = 11;
			buff[1] = 11;
			buff[0] = weight%10;
		}
		if(weight>=10 && weight<100)
		{
			buff[3] = 11;
			buff[2] = 11;
			buff[1] = weight/10;		
			buff[0] = weight%10;
		}
		if(weight>=100 && weight<1000)
		{
			buff[3] = 11;
			buff[2] = (weight%1000)/100;
			buff[1] = ((weight%1000)%100)/10;
			buff[0] = weight%10;
		}
		if(weight>1000)
		{
			buff[3] = 9;
			buff[2] = 9;
			buff[1] = 9;
			buff[0] = 9;
			DrvGPIO_ClrBit(E_GPB, 11);
		}
	}
	else
	{
		if (weight<0 && weight >-10){
			buff[3] = 11;
			buff[2] = 11;
			buff[1] = 10;
			buff[0] = weight%10;
			buff[0] = -buff[0];
		}
		if (weight<=-10 && weight >-100){
		
			buff[3] = 11;
			buff[2] = 10;
			buff[1] = ((weight%1000)%100)/10;		buff[1] = -buff[1];
			buff[0] = weight%10;								buff[0] = -buff[0];
		}
		if(weight<=-100 && weight >-1000){
		
			buff[3] = 10;
			buff[2] = (weight%1000)/100;				buff[2] = -buff[2];
			buff[1] = ((weight%1000)%100)/10;		buff[1] = -buff[1];
			buff[0] = weight%10;								buff[0] = -buff[0];
		}
		if(weight<-1000)
		{
			buff[3] = 9;
			buff[2] = 9;
			buff[1] = 9;
			buff[0] = 9;
			DrvGPIO_ClrBit(E_GPB, 11);
		}
		DrvGPIO_SetBit(E_GPB, 11);
	}
	
	for(i=0; i<4; i++)
	{
		close_seven_segment();
		show_seven_segment(i,buff[i]);
		delay_ms(5);
	}
	TIMER0->TISR.TIF = 1;  // clear Interrupt flag
}
/* THIS CODE IS CREATED BY CONG THANH */
/* Email: vcthanh20@gmail.com */
/* PLEASE KEEP THIS LINE WHEN USING THIS LIB */
