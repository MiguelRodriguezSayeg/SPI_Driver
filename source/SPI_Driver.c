#include "SPI_Driver.h"
#include "MKL27Z644.h"
void Init_SPI_Master(){
	SIM->SCGC5 |= SIM_SCGC5_PORTC_MASK; //Activa puerto C.
	SIM->SCGC4|=SIM_SCGC4_SPI0(1); //Inicializar reloj para SPI0. Se toma el de 24MHz.

	PORTC->PCR[4] = PORT_PCR_MUX(2); //Activa SPI0 SS
	//PORTC->PCR[7] = PORT_PCR_MUX(2); //Activa SPI0 MISO
	PORTC->PCR[6] = PORT_PCR_MUX(2); //Activa SPI0 MOSI
	PORTC->PCR[5] = PORT_PCR_MUX(2); //Activa SPI0 CLK


	SPI0->C1|=SPI_C1_MSTR(1); //Maestro
	SPI0->C1|=SPI_C1_SSOE(1); //GPIO con MODFEN 0
	SPI0->C2|=SPI_C2_MODFEN(1); //Modo SPI activado automático


	SPI0->C1|= SPI_C1_SPE(1); //Activar el SPI0
}

void Init_SPI_Slave(){
		SIM->SCGC5 |= SIM_SCGC5_PORTC_MASK; //Activa puerto C.
		SIM->SCGC4|=SIM_SCGC4_SPI0(1); //Inicializar reloj para SPI0. Se toma el de 24MHz.

		PORTC->PCR[4] = PORT_PCR_MUX(2); //Activa SPI0 SS
		//PORTC->PCR[7] = PORT_PCR_MUX(2); //Activa SPI0 MISO
		PORTC->PCR[6] = PORT_PCR_MUX(2); //Activa SPI0 MOSI
		PORTC->PCR[5] = PORT_PCR_MUX(2); //Activa SPI0 CLK

		//SPI0->C1&=~SPI_C1_SPIE(0); //SPI Interrupt desactivo
		//SPI0->C1&=~SPI_C1_SPTIE(0); //SPI Transmit Interrupt desactivado
		//SPI0->C1|=SPI_C1_MSTR(1); //Maestro
		//SPI0->C1&=~SPI_C1_CPOL(0); //Active high SPI clock
		//SPI0->C1&=~SPI_C1_CPHA(0); //First edge en el SPSCK ocurre a la mitad del primer ciclo de transferencia de datos.
		SPI0->C1|=SPI_C1_SSOE(1); //GPIO con MODFEN 0
		//SPI0->C1&=~SPI_C1_LSBFE(0); //Big endian

		//SPI0->C2|=SPI_C2_SPIMODE(0); //Modo 8 bits
		SPI0->C2|=SPI_C2_MODFEN(1); //Modo SPI activado automático


		SPI0->C1|= SPI_C1_SPE(1); //Activar el SPI0
}

uint_8 SPI_Write(uint_8 instructions,uint_8 size){
		while((((SPI0->S)& (SPI_S_SPTEF_MASK))!=SPI_S_SPTEF_MASK ));
		SPI0->DL=instructions;
		return SUCCESS;
}

uint_8 SPI_Read(uint_8* instructions,uint_8 size){
	uint_8 state = ERROR;
	uint_8 i;
	for(i=0;i<size;++i)
	{
		//SPI0->DL=0;
		while((((SPI0->S)& (SPI_S_SPTEF_MASK))!=SPI_S_SPTEF_MASK ));
		*instructions=SPI0->DL;
		state = SUCCESS;
	}
	return state;
}
