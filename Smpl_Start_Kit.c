/*---------------------------------------------------------------------------------------------------------*/
/*                                                                                                         */
/* Do an cuoi ki - Nhom 13                                                                                 */                                            
/*                                                                                                         */
/*---------------------------------------------------------------------------------------------------------*/

#include "main.h"

extern long weight;

int main(void)
{
	
	
	/* Unlock the protected registers */	
	UNLOCKREG();
   	/* Enable the 12MHz oscillator oscillation */
	DrvSYS_SetOscCtrl(E_SYS_XTL12M, 1);
 
     /* Waiting for 12M Xtal stalble */
    SysTimerDelay(5000);
 
	/* HCLK clock source. 0: external 12MHz; 4:internal 22MHz RC oscillator */
	DrvSYS_SelectHCLKSource(0);		
    /*lock the protected registers */
	LOCKREG();				
	DrvSYS_SetClockDivider(E_SYS_HCLK_DIV, 0); /* HCLK clock frequency = HCLK clock source / (HCLK_N + 1) */
	
	InitTIMER0();

	DrvGPIO_Open(E_GPB, 11, E_IO_OUTPUT);		//loa
	
	init_hx711(1,0,128); //GPA_1: data; GPA_0: clock, gain: chon che do chay cua chanel A.
	set_scale(-(9025/23));
	
	tare(10);
	while(1)
	{
		weight=get_units(10);
	  		
	}
}



