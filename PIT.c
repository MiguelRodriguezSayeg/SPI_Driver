#include "PIT.h"
#include "MKL27Z644.h"

void (*ptr) (void);

void vfnInitPit(){
	SIM->SCGC6|=SIM_SCGC6_PIT_MASK; //Activa el módulo del PIT.
	PIT->MCR &= 0; //Se activa el PIT Standard Time y se activa para modo debug.
	PIT->CHANNEL[0].LDVAL=52500000;	//500ms + un cero
#ifdef PIT_INTERRUPT_EN
	NVIC->ISER[0]|=(1<<PIT_IRQn);
	PIT->CHANNEL[0].TCTRL|=PIT_TCTRL_TIE_MASK;
#endif
	PIT->CHANNEL[0].TCTRL|=PIT_TCTRL_TEN_MASK;
}
#ifdef PIT_INTERRUPT_EN

void vfnPITCallbackRegister1(void vfnCallback(void))
{
	ptr = vfnCallback;
}

void PIT_IRQ(void)
{
	ptr();
	PIT->CHANNEL[0].TFLG|=PIT_TFLG_TIF_MASK;
}
#endif
