#ifndef PIT_H_
#define PIT_H_
#define PIT_INTERRUPT_EN
#define PIT_IRQ PIT_DriverIRQHandler
typedef unsigned char uint_8;
void vfnPITCallbackRegister1(void vfnCallback(void));
void vfnInitPit();
#endif
