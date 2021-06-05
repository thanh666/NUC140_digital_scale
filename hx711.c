/* THIS LIB IS CREATED BY CONG THANH */
/* Email: vcthanh20@gmail.com */
/* PLEASE KEEP THIS LINE WHEN USING THIS LIB */

#include "hx711.h"

typedef struct {
	char PD_SCK_HX;
	char DOUT_HX;
	char GAIN_HX;

	long OFFSET_HX;
	float SCALE_HX;
} hx711;

hx711 scale;

uint8_t shiftInSlow(char Pin, char sck) // only work on port A from GPIOA_0 - GPIOA_15
{
	uint8_t value = 0;
	unsigned int i;
	
	for(i=0;i<8;i++)
	{
		DrvGPIO_SetBit(E_GPA, sck);
		value |= DrvGPIO_GetBit(E_GPA, Pin) << (7 - i);
		DrvGPIO_ClrBit(E_GPA, sck);
	}
	return value;
}

void init_hx711(char dout, char pd_sck, char gain)
{
	
	scale.PD_SCK_HX = pd_sck;
	scale.DOUT_HX = dout;
	
	DrvGPIO_Open(E_GPA, scale.PD_SCK_HX, E_IO_OUTPUT);		//clock output mode
	DrvGPIO_Open(E_GPA, scale.DOUT_HX, E_IO_INPUT);			//Data input pull-up
	DrvGPIO_EnableDigitalInputBit(E_GPA, scale.DOUT_HX);
	DrvGPIO_ClrBit(E_GPA, scale.PD_SCK_HX);
	set_gain(gain);
	
}

char is_ready(void){

	return DrvGPIO_GetBit(E_GPA, scale.DOUT_HX) == 0;
}

void wait_ready(int ms)
{
	while (!is_ready()) {
		delay_ms(ms);
	}
}

char wait_ready_retry(int retries, int ms)
{
	int count =0;
	while (count < retries) {
		if (is_ready()) {
			return 1;
		}
		delay_ms(ms);
		count++;
	}
	return 0;
}

void set_gain(uint8_t gain)
{
	switch (gain) {
		case 128:		// channel A, GAIN_HX factor 128
			scale.GAIN_HX = 1;
			break;
		case 64:		// channel A, GAIN_HX factor 64
			scale.GAIN_HX = 3;
			break;
		case 32:		// channel B, GAIN_HX factor 32
			scale.GAIN_HX = 2;
			break;
	}
}

long read(void)
{
	unsigned int i;
	unsigned long value = 0;
	uint8_t data[3] = { 0 };
	uint8_t filler = 0x00;
	wait_ready(0);
	
	
	
	data[2] = shiftInSlow(scale.DOUT_HX, scale.PD_SCK_HX);
	data[1] = shiftInSlow(scale.DOUT_HX, scale.PD_SCK_HX);
	data[0] = shiftInSlow(scale.DOUT_HX, scale.PD_SCK_HX);
	
	for (i = 0; i < scale.GAIN_HX; i++) {
		DrvGPIO_SetBit(E_GPA, scale.PD_SCK_HX);
		//DrvSYS_Delay(1);
		DrvGPIO_ClrBit(E_GPA, scale.PD_SCK_HX);
		//DrvSYS_Delay(1);
	}
	
	if (data[2] & 0x80) {
		filler = 0xFF;
	} else {
		filler = 0x00;
	}
	
	value = (((unsigned long)filler & 0xff) << 24 
				 | ((unsigned long)data[2] & 0xff) << 16 
				 | ((unsigned long)data[1] & 0xff ) << 8 
				 | ((unsigned long)data[0] & 0xff));
	
	return (long)value;
}

long read_average(char times)
{
	unsigned int i;
	long sum = 0;
	for (i = 0; i < times; i++) {
		sum += read();
		
		//delay_ms(1);
	}
	return sum / times;
}

double get_value(char times)
{
	return read_average(times) - scale.OFFSET_HX;
}

float get_units(char times)
{
	return get_value(times) / scale.SCALE_HX;
}

void tare(char times)
{
	double sum = read_average(times);
	set_offset(sum);
}

void set_scale(float SCALE_HX)
{
	scale.SCALE_HX = SCALE_HX;
}

float get_scale(void)
{
	return scale.SCALE_HX;
}

void set_offset(long OFFSET_HX)
{
	scale.OFFSET_HX = OFFSET_HX;
}

long get_offset(void)
{
	return scale.OFFSET_HX;
}

void power_down(void)
{
	DrvGPIO_ClrBit(E_GPA, scale.PD_SCK_HX);
	DrvGPIO_SetBit(E_GPA, scale.PD_SCK_HX);
}

void power_up(void)
{
	DrvGPIO_ClrBit(E_GPA, scale.PD_SCK_HX);
}

/* THIS LIB IS CREATED BY CONG THANH */
/* Email: vcthanh20@gmail.com */
/* PLEASE KEEP THIS LINE WHEN USING THIS LIB */
