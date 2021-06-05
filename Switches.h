#ifndef _SWITCHES_H_
#define _SWITCHES_H_

#include <stdio.h>
#include "NUC1xx.h"
#include "Driver\DrvGPIO.h"
#include "Driver\DrvSYS.h"

void OpenKeyPad(void);
void CloseKeyPad(void);
int get_switch(void);

int getSwitchEOS(void);

#endif

