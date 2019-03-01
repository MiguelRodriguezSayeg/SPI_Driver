#include "MKL27Z644.h"
#ifndef GPIO_H_
#define GPIO_H_

#define SUCCESS 1
#define ERROR 0

#define ROJO 1
#define VERDE 2
#define AMARILLO 4
#define BLANCO 8
typedef unsigned char uint_8;

enum puertos{
	puertoRojo,
	puertoVerde,
	puertoBlanco,
	puertoAmarillo
};

uint_8 TurnOnLed(uint_8 color);
uint_8 TurnOffLed(uint_8 color);
uint_8 ToggleLed(uint_8 color);
uint_8 DisableLed(uint_8 color);
uint_8 EnableLed(uint_8 color);

#endif
