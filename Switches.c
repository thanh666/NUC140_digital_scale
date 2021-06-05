#include "Switches.h"
#include "port.h"
int keybuff[3]={0,0,0};
void delay(void)
{
	int j;
	for(j=0;j<1000;j++);
}

void Delay(int count)
{
	while(count--)
	{
//		__NOP;
	 }
}

void OpenKeyPad(void)
{
	uint8_t i;
	for(i=0;i<6;i++)
	{
		DrvGPIO_Open(E_GPA, i, E_IO_QUASI);
	}
}

void CloseKeyPad(void)
{
	uint8_t i;
	for(i=0;i<6;i++)
	{
		DrvGPIO_Close(E_GPA, i);
	}
}

int getSwitchEOS(void)
{
	int tmp=0, key=0; 
	tmp=get_switch();
	keybuff[0]=keybuff[1];
	keybuff[1]=keybuff[2];
	keybuff[2]=tmp;
	if((keybuff[0]==keybuff[1])&&keybuff[2]==0)
		key=keybuff[1];
	return key;
}


int get_switch(void)
{
	//uint8_t act[4]={0x3b, 0x3d, 0x3e};    
//	int i,temp,pin;

	int key;
	//while(1){
		key=0;
	// Doc hang dau tien
		Row1 = 0; Row2 = 1; Row3 = 1;
		if(Col1 == 0) {
			Delay(20);
			if(Col1 == 0) {
				while(Col1 == 0);
				key = 1;  	
			}
		}

		if(Col2 == 0) {
			Delay(20);
			if(Col2  == 0) {
				      while(Col2  == 0);
				key = 2;      // Cho nha phim
			}
		}
		
		if(Col3 == 0) {
			Delay(20);
			if(Col3  == 0) {
				while(Col3  == 0);
				key = 3;      // Cho nha phim
			}
		}
		
	// Doc hang thu hai
		Row1 = 1; Row2 = 0; Row3 = 1;
		if(Col1== 0) {
			Delay(20);
			if(Col1== 0) {
				while(Col1== 0);
				key = 4;      // Cho nha phim
			}
		}
		
		if(Col2 == 0) {
			Delay(20);
			if(Col2 == 0) {
				while(Col2 == 0);
				key = 5;      // Cho nha phim
			}
		}
		
		if(Col3 == 0) {
			Delay(20);
			if(Col3 == 0) {
				while(Col3 == 0);
				key = 6;      // Cho nha phim
			}
		}
		
		// Doc hang thu ba
		Row1 = 1; Row2 = 1; Row3 = 0;
		if(Col1== 0) {
			Delay(20);
			if(Col1== 0) {
				while(Col1== 0);
				key = 7;      // Cho nha phim
			}
		}
		
		if(Col2 == 0) {
			Delay(20);
			if(Col2 == 0) {
				while(Col2 == 0);
				key = 8;      // Cho nha phim
			}
		}
		
		if(Col3 == 0) {
			Delay(20);
			if(Col3 == 0) {
			 while(Col3 == 0);
				key = 9;    
				// Cho nha phim
			}
		}
	return key;
	
		//return 0;
}

