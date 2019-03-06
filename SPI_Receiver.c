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

typedef unsigned char uint_8;

void ExecComands(void);
void Enable (uint_8 led);
void Disable (uint_8 led);
void TurnOn (uint_8 led);
void TurnOff (uint_8 led);
void Toogle (uint_8 led);
void Erase (uint_8 led);
void SendColor(uint_8 led);
void ImprimirContador (uint_8 contador);

enum function{
eEnable,
eDisable,
eTurnOn,
eTurnOff,
eToggle,
eErase};

enum colores{
eGreen,
eWhite,
eRed,
eYellow,};

void (*StateMachine[])(uint_8 led) =
{
	Enable,							//0
	Disable,						//1
	TurnOn,							//2
	TurnOff,						//3
	Toogle,							//4
	Erase							//5
};

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


int main (void)
{
	COMM_vfnDriverInitSlave();
	volatile uint_8 i = 0;
	EnableLed(GREEN);
	TurnOnLed(GREEN);
	while(1)
	{

		ToggleLed(GREEN);
		ExecComands();
		i++;
		i--;
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
		if(contador < data[1])
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
		else
		{
			ptrdata = &data[2];
			contador = 0;
		}
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
