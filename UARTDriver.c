#include <UARTDriver.h>
#include "MKL27Z644.h"
void UART_vfnDriverInit(){
	uint_16 bsr=SEL_CLK/((UART_BAUD_OSR+2)*UART_BAUD_RATE);
	MCG->C1 = MCG_C1_IREFSTEN_MASK | MCG_C1_IRCLKEN_MASK; //Activa el reloj MCG.

	SIM->SCGC5 |= SIM_SCGC5_LPUART0_MASK; //Enciende el LPUART0.
	SIM->SOPT2 |= SIM_SOPT2_LPUART0SRC(3); //Selecciona el reloj  MCG para la LPUART0.


	LPUART0->BAUD|=LPUART_BAUD_OSR(UART_BAUD_OSR); //Se selecciona un modificador
	LPUART0->BAUD|=LPUART_BAUD_SBNS(1); //doble stop bit
	LPUART0->BAUD|=LPUART_BAUD_SBR(bsr); //valor resultante con formula de abajo.

	// BSR=(8MHz/((OSR+1)*baudrate)

	LPUART0->STAT|=LPUART_STAT_MSBF(0); //LSB

	LPUART0->CTRL|=LPUART_CTRL_M(0); //modo 8 bit
	LPUART0->CTRL=LPUART_CTRL_PE(1);
	LPUART0->CTRL=LPUART_CTRL_PT(0);

	SIM->SCGC5 |= SIM_SCGC5_PORTA_MASK; //se activa la secciòn A, ahí está el LPUART0 para USB.
	PORTA->PCR[1] = PORT_PCR_MUX(2); //TX
	PORTA->PCR[2] = PORT_PCR_MUX(2);//RX

	LPUART0->CTRL|=LPUART_CTRL_TE(1); //ACTIVAR TX
	LPUART0->CTRL|=LPUART_CTRL_RE(1); //ACTIVAR RX
}
uint_8 UART_bfnSend(uint_8 valor){
	 if(LPUART0->STAT&LPUART_STAT_TC_MASK){
	        LPUART0->DATA=valor;
	        return SUCCESS;
	 }
	 return ERROR;
}
uint_8 UART_bfnRead(uint_8* valor){
	LPUART0->STAT |= LPUART_STAT_OR(1);
	if(LPUART0->STAT&LPUART_STAT_RDRF_MASK){
	        	*valor=LPUART0->DATA;
	        	return SUCCESS;
	}
	return ERROR;
}
