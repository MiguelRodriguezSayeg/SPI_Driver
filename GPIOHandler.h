#ifndef GPIOHANDLER_H_
#define GPIOHANDLER_H_

typedef unsigned char uint_8;

enum led{
	eDeshabilitado,
	eHabilitado
};

uint_8 Handler_TurnOnLed(uint_8 color,uint_8 estado);
uint_8 Handler_TurnOffLed(uint_8 color,uint_8 estado);
uint_8 Handler_ToggleLed(uint_8 color,uint_8 estado);
uint_8 Handler_DisableLed(uint_8 color,uint_8 estado);
uint_8 Handler_EnableLed(uint_8 color,uint_8 estado);

#endif
