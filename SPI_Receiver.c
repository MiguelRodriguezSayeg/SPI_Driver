#include"Communication.h"
#include"GPIOHandler.h"
#include"GPIO.h"

#define ENABLE 			0b01010000
#define DISABLE 		0b01000000
#define TURN_ON 		0b00010000
#define TURN_OFF 		0b00100000
#define TOGGLE 			0b00110000
#define ERASE 			0b01100000

#define GREEN 			0b00000001
#define WHITE			0b00000010
#define RED 			0b00000100
#define YELLOW			0b00001000
#define PLACA 			0b00010010

#define TOP 			48
typedef unsigned char uint_8;


void Enable (uint_8 led);
void Disable (uint_8 led);
void TurnOn (uint_8 led);
void TurnOff (uint_8 led);
void Toogle (uint_8 led);
void Erase (uint_8 led);
void SendColor(uint_8 led);
void ImprimirContador (uint_8 contador);
uint_8 valueinarray(uint_8 valor, const uint_8 *arr,uint_8 size);
uint_8 checkArrays(uint_8 * array1,uint_8 * array2,uint_8 size);
void readingState(void);
void idleState(void);
void ExecComands(void);
void copyArrays(uint_8 * destiny,uint_8 * source,uint_8 size);
void cleanArray(uint_8 * source,uint_8 size);


/*
 * En la siguientes lineas declararemos las maquinas de estados que utilizaremos
 * con sus respectivos enum
 */
void (*StateMachine[])(uint_8 led) =
{
	Enable,							//0
	Disable,						//1
	TurnOn,							//2
	TurnOff,						//3
	Toogle,							//4
	Erase							//5
};
enum function{
eEnable,
eDisable,
eTurnOn,
eTurnOff,
eToggle,
eErase};


void (*reading_states[])(void) =
{
	readingState,
	idleState
};
enum Decoder
{
	sReading,
	sIdle
};

/*
 * Ahora haremos que tenemos las maquina de estados preparadas inicializaremos
 * las variables que ocuparemos en lo largo del programa
 */
/*
 * Variables compartidas entre las dos maquinas de estados
 */

uint_8 ready = 0;

/*
 * Lo siguiente son las variables que utilizaremos para estar leyendo en del SPI
 */
const uint_8 validColor[]={GREEN,WHITE,RED,YELLOW};
const uint_8 validCommand[]={ENABLE,DISABLE,TURN_ON,TURN_OFF,TOGGLE,ERASE};

uint_8 temporal[50]={0};
uint_8 spi = 0;

uint_8 state=sIdle;

uint_8 * ptrtemporal;
uint_8 * ptrspi = &spi;
enum Trama
{
	eStart,
	eIteraciones,
	eElem1
};

/*
 * Ahora declararemos las variables que utilizaremos para
 * ejecutar los comandos
 */
uint_8 data [50] = {0xFE,5,ENABLE|GREEN,TURN_ON|GREEN,DISABLE|GREEN,TURN_ON|GREEN,TURN_ON|GREEN};


uint_8 enable[7] =   {'e','n','a','b','l','e',' '};
uint_8 disable[8] =  {'d','i','s','a','b','l','e',' '};
uint_8 turn_on[8] =  {'t','u','r','n',' ','o','n',' '};
uint_8 turn_off[9] = {'t','u','r','n',' ','o','f','f',' '};
uint_8 toogle[7] =   {'t','o','o','g','l','e',' '};
uint_8 erase[6] =    {'e','r','a','s','e',' '};

uint_8 green[6] =    {'g','r','e','e','n',' '};
uint_8 white[6] =    {'w','h','i','t','e',' '};
uint_8 red[4] =   	 {'r','e','d',' '};
uint_8 yellow[7] =   {'y','e','l','l','o','w',' '};
uint_8 estados_colores[4] = {0,0,0,0};

enum colores{
eGreen,
eWhite,
eRed,
eYellow,};

/*
 * Ya inicializado todo esto podemos trabajar
 */
int main (void)
{
	COMM_vfnDriverInitSlave();
	while(1)
	{
		reading_states[state]();
		ExecComands();
	}
}

void ExecComands(void)
{
	static uint_8 * ptrdata = &data[2];
	static uint_8 contador = 0;

	uint_8 instruccion = 0;
	uint_8 led = 0;

	if(data[0] == 0xFE)
	{
		if((contador < data[1]) && (data[1] != 0))
		{
			instruccion = (*ptrdata & 0b11110000);
			led = (*ptrdata & 0b00001111);

			switch(instruccion)
			{
				case ENABLE:
					ImprimirContador(contador);
					StateMachine[eEnable](led);
					break;
				case DISABLE:
					ImprimirContador(contador);
					StateMachine[eDisable](led);
					break;
				case TURN_ON:
					ImprimirContador(contador);
					StateMachine[eTurnOn](led);
					break;
				case TURN_OFF:
					ImprimirContador(contador);
					StateMachine[eTurnOff](led);
					break;
				case TOGGLE:
					ImprimirContador(contador);
					StateMachine[eToggle](led);
					break;
				case ERASE:
					ImprimirContador(contador);
					StateMachine[eErase](led);
					break;
				default:
					ptrdata--;
					contador--;
			}
			ptrdata++;
			contador++;
		}
		else if(contador >= data[1])
		{
			contador = 0;
			ptrdata = &data[2];
			reiniciar();
		}
	}
	else
	{
		contador = 0;
		ptrdata = &data[2];
		reiniciar();
	}
}

void reiniciar (void)
{
	StateMachine[eErase](led);
	if(ready)
	{
		ready = 0;
		copyArrays(&data[0],&temporal[0],sizeof(temporal));
		cleanArray(&temporal[0],sizeof(temporal));
	}
}
void ImprimirContador (uint_8 contador)
{
	uint_8 numero_temp = 0;
	numero_temp = (contador / 10) + '0';
	COMM_bfnSendMsg(&numero_temp,sizeof (numero_temp));
	numero_temp = (contador % 10) + '0';
	COMM_bfnSendMsg(&numero_temp,sizeof (numero_temp));
}
void Enable (uint_8 led)
{
	switch(led)
	{
		case GREEN:
			Handler_EnableLed(led,estados_colores[eGreen]);
			estados_colores[eGreen] = 1;
			break;
		case WHITE:
			Handler_EnableLed(led,estados_colores[eWhite]);
			estados_colores[eWhite] = 1;
			break;
		case RED:
			Handler_EnableLed(led,estados_colores[eRed]);
			estados_colores[eRed] = 1;
			break;
		case YELLOW:
			Handler_EnableLed(led,estados_colores[eYellow]);
			estados_colores[eYellow] = 1;
			break;
	}
	COMM_bfnSendMsg(&enable[0],sizeof (enable)/sizeof (uint_8));
	SendColor(led);
}
void Disable (uint_8 led)
{
	switch(led)
		{
			case GREEN:
				Handler_DisableLed(led,estados_colores[eGreen]);
				estados_colores[eGreen] = 0;
				break;
			case WHITE:
				Handler_DisableLed(led,estados_colores[eWhite]);
				estados_colores[eWhite] = 0;
				break;
			case RED:
				Handler_DisableLed(led,estados_colores[eRed]);
				estados_colores[eRed] = 0;
				break;
			case YELLOW:
				Handler_EnableLed(led,estados_colores[eYellow]);
				estados_colores[eYellow] = 0;
				break;
		}
	COMM_bfnSendMsg(&disable[0],sizeof (disable)/sizeof (uint_8));
	SendColor(led);
}
void TurnOn (uint_8 led)
{
	switch(led)
	{
		case GREEN:
			if(estados_colores[eGreen])
			{
				Handler_TurnOnLed(led,estados_colores[eGreen]);
			}
			break;
		case WHITE:
			if(estados_colores[eWhite])
			{
				Handler_TurnOnLed(led,estados_colores[eWhite]);
			}
			break;
		case RED:
			if(estados_colores[eRed])
			{
				Handler_TurnOnLed(led,estados_colores[eRed]);
			}
			break;
		case YELLOW:
			if(estados_colores[eYellow])
			{
				Handler_TurnOnLed(led,estados_colores[eYellow]);
			}
			break;
	}
	COMM_bfnSendMsg(&turn_on[0],sizeof (turn_on)/sizeof (uint_8));
	SendColor(led);

}
void TurnOff (uint_8 led)
{
	switch(led)
		{
			case GREEN:
				if(estados_colores[eGreen])
				{
					Handler_TurnOffLed(led,estados_colores[eGreen]);
				}
				break;
			case WHITE:
				if(estados_colores[eWhite])
				{
					Handler_TurnOffLed(led,estados_colores[eWhite]);
				}
				break;
			case RED:
				if(estados_colores[eRed])
				{
					Handler_TurnOffLed(led,estados_colores[eRed]);
				}
				break;
			case YELLOW:
				if(estados_colores[eYellow])
				{
					Handler_TurnOffLed(led,estados_colores[eYellow]);
				}
				break;
		}
	COMM_bfnSendMsg(&turn_off[0],sizeof (turn_off)/sizeof (uint_8));
	SendColor(led);

}
void Toogle (uint_8 led)
{
	switch(led)
			{
				case GREEN:
					if(estados_colores[eGreen])
					{
						Handler_ToggleLed(led,estados_colores[eGreen]);
					}
					break;
				case WHITE:
					if(estados_colores[eWhite])
					{
						Handler_ToggleLed(led,estados_colores[eWhite]);
					}
					break;
				case RED:
					if(estados_colores[eRed])
					{
						Handler_ToggleLed(led,estados_colores[eRed]);
					}
					break;
				case YELLOW:
					if(estados_colores[eYellow])
					{
						Handler_ToggleLed(led,estados_colores[eYellow]);
					}
					break;
			}
	COMM_bfnSendMsg(&toogle[0],sizeof (toogle)/sizeof (uint_8));
	SendColor(led);
}
void Erase (uint_8 led)
{
	uint_8 i = 0;
	COMM_bfnSendMsg(&erase[0],sizeof (erase)/sizeof (uint_8));
	for(;i<50;i++)
		data[i] = 0;
}

void SendColor(uint_8 led)
{
	if(led == GREEN)
	{
		COMM_bfnSendMsg(&green[0],sizeof (green)/sizeof (uint_8));
	}
	if(led == WHITE)
	{
		COMM_bfnSendMsg(&white[0],sizeof (white)/sizeof (uint_8));
	}
	if(led == RED)
	{
		COMM_bfnSendMsg(&red[0],sizeof (red)/sizeof (uint_8));
	}
	if(led == YELLOW)
	{
		COMM_bfnSendMsg(&yellow[0],sizeof (yellow)/sizeof (uint_8));
	}
}

uint_8 valueinarray(uint_8 valor, const uint_8 *arr,uint_8 size)
{
		uint_8 i=0;
		for(i=0;i<size;i++)
		{
			if(*(arr+i)==valor)
			{
				return SUCCESS;
			}
		}
	return ERROR;
}

uint_8 checkArrays(uint_8 * array1,uint_8 * array2,uint_8 size)
{
	uint_8 i = 0;
	uint_8 state = SUCCESS;
	for(;i<size;i++,array1++,array2++)
	{
		if(*array1 != *array2)
		{
			state = ERROR;
		}
	}
	return state;
}


void idleState(void)
{
	COMM_bfnReceiveMosi(ptrspi);
	if(spi==0xFE)
	{
		ptrtemporal = &temporal[eStart];
		*ptrtemporal = spi;
		state = sReading;
		ptrtemporal = &temporal[eIteraciones];
	}
}


void readingState(void)
{

	static uint_8 tmpCount=0;
	static uint_8 contador=0;
	uint_8 valCol=ERROR;
	uint_8 valCom=ERROR;

	uint_8 instruccion;
	uint_8 led;

	if(ptrtemporal == &temporal[eIteraciones])
	{
		COMM_bfnReceiveMosi(ptrspi);
		*ptrtemporal = spi;
		tmpCount = 2;
	}

	if((temporal[eIteraciones]<=TOP) && (temporal[eIteraciones]!=0))
	{
		COMM_bfnReceiveMosi(ptrspi);
		ptrtemporal = &temporal[eElem1+contador];
		*ptrtemporal = spi;
	}

	if((contador<temporal[eIteraciones]) && (temporal[eIteraciones]<=48) && (temporal[eIteraciones]!=0))
	{
		instruccion=(*(ptrtemporal + contador))& 0b11110000;
		led=(*(ptrtemporal + contador))&0b00001111;

		valCol = valueinarray(led,&validColor[0],sizeof(validColor));
		valCom = valueinarray(instruccion,&validCommand[0],sizeof(validCommand));

		if(valCol & valCom)
		{
			tmpCount++;
			contador++;
		}
	}

	if((contador >= temporal[eIteraciones]) && (temporal[eIteraciones]!=0))
	{
		state=sIdle;
		ready = 1;
	}
}

void copyArrays(uint_8 * destiny,uint_8 * source,uint_8 size)
{
	uint_8 i = 0;
	for(;i<size;i++,destiny++,source++)
	{
		*destiny = *source;
	}
}
void cleanArray(uint_8 * source,uint_8 size)
{
	uint_8 i = 0;
	for(;i<size;i++,source++)
	{
		*source = 0;
	}
}


