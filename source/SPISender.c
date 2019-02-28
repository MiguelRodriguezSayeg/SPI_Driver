#include "MKL27Z644.h"
#include "SPI_Driver.h"

int main(void) {
    volatile static int i = 0 ;
    uint_8 data[50]={0,255,0};
    Init_SPI_Master();
    //Init_SPI_Slave();
    while(1) {
    	SPI_Write(data,sizeof(data)/sizeof(uint_8));
        i++ ;
    }
    return 0 ;
}
