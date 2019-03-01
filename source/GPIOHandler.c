#include "GPIOHandler.h"
#include "GPIO.h"
#include "MKL27Z644.h"

uint_8 Handler_TurnOnLed(uint_8 color,uint_8 estado){
	if(estado==eHabilitado){
		if(!TurnOnLed(color)){
			return SUCCESS;
		}
		else{
			return ERROR;
		}
	}
	else{
		return ERROR;
	}

}
uint_8 Handler_TurnOffLed(uint_8 color,uint_8 estado){
	if(estado==eHabilitado){
		if(!TurnOffLed(color)){
			return SUCCESS;
		}
		else{
			return ERROR;
		}
	}
	else{
		return ERROR;
	}

}
uint_8 Handler_ToggleLed(uint_8 color,uint_8 estado){
	if(estado==eHabilitado){
		if(!ToggleLed(color)){
			return SUCCESS;
		}
		else{
			return ERROR;
		}
	}
	else{
		return ERROR;
	}

}
uint_8 Handler_DisableLed(uint_8 color,uint_8 estado){
	if(estado==eHabilitado){
		if(!TurnOnLed(color)){
			return SUCCESS;
		}
		else{
			return ERROR;
		}
	}
	else{
		return ERROR;
	}

}
uint_8 Handler_EnableLed(uint_8 color,uint_8 estado){
	if(estado==eDeshabilitado){
		if(!TurnOnLed(color)){
			return SUCCESS;
		}
		else{
			return ERROR;
		}
	}
	else{
		return ERROR;
	}

}
