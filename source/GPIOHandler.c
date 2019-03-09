#include "GPIOHandler.h"
#include "GPIO.h"
#include "MKL27Z644.h"

uint_8 Handler_TurnOnLed(uint_8 color,uint_8 estado)
{
	uint_8 state = ERROR;
	if(estado==eHabilitado)
	{
		if(TurnOnLed(color))
		{
			state = SUCCESS;
		}
		else
		{
			state = ERROR;
		}
	}
	else
	{
		state = ERROR;
	}
	return state;

}
uint_8 Handler_TurnOffLed(uint_8 color,uint_8 estado)
{
	uint_8 state = ERROR;
	if(estado==eHabilitado)
	{
		if(TurnOffLed(color))
		{
			state = SUCCESS;
		}
		else
		{
			state = ERROR;
		}
	}
	else
	{
		state = ERROR;
	}
	return state;

}
uint_8 Handler_ToggleLed(uint_8 color,uint_8 estado)
{
	uint_8 state = ERROR;
	if(estado==eHabilitado)
	{
		if(ToggleLed(color))
		{
			state = SUCCESS;
		}
		else
		{
			state = ERROR;
		}
	}
	else
	{
		state = ERROR;
	}
	return state;
}
uint_8 Handler_DisableLed(uint_8 color,uint_8 estado)
{
	uint_8 state = ERROR;
	if(estado==eHabilitado)
	{
		if(DisableLed(color))
		{
			state = SUCCESS;
		}
		else
		{
			state = ERROR;
		}
	}
	else
	{
		state = ERROR;
	}
	return state;
}
uint_8 Handler_EnableLed(uint_8 color,uint_8 estado)
{
	uint_8 state = ERROR;
	if(estado==eDeshabilitado)
	{
		if(EnableLed(color))
		{
			state = SUCCESS;
		}
		else
		{
			state = ERROR;
		}
	}
	else
	{
		state = ERROR;
	}
	return state;
}
