#include "GPIO.h"
#include "MKL27Z644.h"
uint_8 EnableLed(uint_8 color)
{
	SIM->SCGC5 |= SIM_SCGC5_PORTD_MASK;			//INICIALIZAR EL PUERTO
	switch(color)
	{
		case ROJO:
			PORTD->PCR[puertoRojo] |= PORT_PCR_MUX(1);		//INICIALIZAR EL GPIO
			PORTD->PCR[puertoRojo] |= PORT_PCR_PE(0b1);
			PORTD->PCR[puertoRojo] |= PORT_PCR_PS(0b1);
			break;
		case VERDE:
			PORTD->PCR[puertoVerde] |= PORT_PCR_MUX(1);		//INICIALIZAR EL GPIO
			PORTD->PCR[puertoVerde] |= PORT_PCR_PE(0b1);
			PORTD->PCR[puertoVerde] |= PORT_PCR_PS(0b1);
			break;
		case AMARILLO:
			PORTD->PCR[puertoAmarillo] |= PORT_PCR_MUX(1);		//INICIALIZAR EL GPIO
			PORTD->PCR[puertoAmarillo] |= PORT_PCR_PE(0b1);
			PORTD->PCR[puertoAmarillo] |= PORT_PCR_PS(0b1);
			break;
		case BLANCO:
			PORTD->PCR[puertoBlanco] |= PORT_PCR_MUX(1);		//INICIALIZAR EL GPIO
			PORTD->PCR[puertoBlanco] |= PORT_PCR_PE(0b1);
			PORTD->PCR[puertoBlanco] |= PORT_PCR_PS(0b1);
			break;
		case PLACA:
			SIM->SCGC5 |= SIM_SCGC5_PORTB_MASK;			//INICIALIZAR EL PUERTO
			PORTB->PCR[PLACA] |= PORT_PCR_MUX(1);		//INICIALIZAR EL GPIO
			break;
		default:
			return ERROR;
	}
	TurnOffLed(color);
	return SUCCESS;
}
uint_8 DisableLed(uint_8 color)
{

	TurnOffLed(color);
	switch(color)
	{
		case ROJO:
			PORTD->PCR[puertoRojo] &= ~PORT_PCR_MUX(1);			//INICIALIZAR EL GPIO
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
		case PLACA:
			PORTB->PCR[PLACA] &= ~ PORT_PCR_MUX(1);				//INICIALIZAR EL GPIO
			break;
		default:
			return ERROR;

	}
	return SUCCESS;
}

uint_8 TurnOffLed(uint_8 color)
{
	switch(color)
	{
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
		case PLACA:
			GPIOB->PDDR |= (1<<PLACA);					//INICIALIZAR EL GPIO
			break;
		default:
			return ERROR;
	}
	return SUCCESS;
}
uint_8 TurnOnLed(uint_8 color)
{

	switch(color)
	{
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
		case PLACA:
			GPIOB->PDDR &= ~(1<<PLACA);					//INICIALIZAR EL GPIO
			break;
		default:
			return ERROR;
	}
	return SUCCESS;
}

uint_8 ToggleLed(uint_8 color)
{

	switch(color)
	{
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
		case PLACA:
			GPIOB->PDDR ^=(1<<PLACA);					//INICIALIZAR EL GPIO
			break;
		default:
			return ERROR;
	}
	return SUCCESS;
}
