#include "GPIO.h"
#include "MKL27Z644.h"
uint_8 EnableLed(uint_8 color){
	SIM->SCGC5 |= SIM_SCGC5_PORTD_MASK;			//INICIALIZAR EL PUERTO
	switch(color){
		case ROJO:
			PORTD->PCR[puertoRojo] |= PORT_PCR_MUX(1);		//INICIALIZAR EL GPIO
			break;
		case VERDE:
			PORTD->PCR[puertoVerde] |= PORT_PCR_MUX(1);		//INICIALIZAR EL GPIO
			break;
		case AMARILLO:
			PORTD->PCR[puertoAmarillo] |= PORT_PCR_MUX(1);		//INICIALIZAR EL GPIO
			break;
		case BLANCO:
			PORTD->PCR[puertoBlanco] |= PORT_PCR_MUX(1);		//INICIALIZAR EL GPIO
			break;
		default:
			return 0;

	}
	return 1;
}
uint_8 DisableLed(uint_8 color){
	switch(color){
		case ROJO:
			PORTD->PCR[puertoRojo] &= ~PORT_PCR_MUX(1);		//INICIALIZAR EL GPIO
			break;
		case VERDE:
			PORTD->PCR[puertoVerde] &= ~PORT_PCR_MUX(1);		//INICIALIZAR EL GPIO
			break;
		case AMARILLO:
			PORTD->PCR[puertoAmarillo] &= ~PORT_PCR_MUX(1);		//INICIALIZAR EL GPIO
			break;
		case BLANCO:
			PORTD->PCR[puertoBlanco] &= ~PORT_PCR_MUX(1);		//INICIALIZAR EL GPIO
			break;
		default:
			return ERROR;

	}
	return SUCCESS;
}

uint_8 TurnOnLed(uint_8 color){
	SIM->SCGC5 |= SIM_SCGC5_PORTD_MASK;			//INICIALIZAR EL PUERTO
	switch(color){
		case ROJO:
			GPIOD->PDDR |= (1<<puertoRojo);	    //INICIALIZAR EL GPIO
			break;
		case VERDE:
			GPIOD->PDDR |= (1<<puertoVerde);	//INICIALIZAR EL GPIO
			break;
		case AMARILLO:
			GPIOD->PDDR |= (1<<puertoAmarillo);		//INICIALIZAR EL GPIO
			break;
		case BLANCO:
			GPIOD->PDDR |= (1<<puertoBlanco);		//INICIALIZAR EL GPIO
			break;
		default:
			return ERROR;

	}
	return SUCCESS;
}
uint_8 TurnOffLed(uint_8 color){
	SIM->SCGC5 |= SIM_SCGC5_PORTD_MASK;			//INICIALIZAR EL PUERTO
	switch(color){
		case ROJO:
			GPIOD->PDDR &= ~(1<<puertoRojo);	    //INICIALIZAR EL GPIO
			break;
		case VERDE:
			GPIOD->PDDR &= ~(1<<puertoVerde);	//INICIALIZAR EL GPIO
			break;
		case AMARILLO:
			GPIOD->PDDR &= ~(1<<puertoAmarillo);		//INICIALIZAR EL GPIO
			break;
		case BLANCO:
			GPIOD->PDDR &= ~(1<<puertoBlanco);		//INICIALIZAR EL GPIO
			break;
		default:
			return ERROR;

	}
	return SUCCESS;
}

uint_8 ToggleLed(uint_8 color){
	SIM->SCGC5 |= SIM_SCGC5_PORTD_MASK;
	switch(color){
		case ROJO:
			GPIOD->PDDR^=(1<<puertoRojo);
			break;
		case VERDE:
			GPIOD->PDDR^=(1<<puertoVerde);
			break;
		case AMARILLO:
			GPIOD->PDDR^=(1<<puertoAmarillo);
			break;
		case BLANCO:
			GPIOD->PDDR ^=(1<<puertoBlanco);
			break;
		default:
			return ERROR;

	}
	return SUCCESS;
}
