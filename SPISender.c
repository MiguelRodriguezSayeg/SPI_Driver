#include "MKL27Z644.h"
#include "Communication.h"
#include "PIT.h"

#define ENABLE 			0b01010000
#define DISABLE 		0b01000000
#define TURN_ON 		0b00010000
#define TURN_OFF 		0b00100000
#define TOGGLE 			0b00110000
#define ERASE 			0b01100000

#define GREEN 0b00000001
#define RED 0b00000010
#define WHITE 0b00000100
#define YELLOW 0b00001000

void send_Data();

uint_8 j=0;
uint_8 data[]={0xFE,6,ENABLE|GREEN,ENABLE|YELLOW,TURN_ON|GREEN,TURN_ON|YELLOW,TURN_OFF|GREEN,TOGGLE|YELLOW};
    //uint_8 data[]={0xFE,2,0b01010001,0b01000001};
uint_8 tam=sizeof(data)/sizeof(uint_8);

int main(void) {
    vfnPITCallbackRegister1(send_Data);
    vfnInitPit();
    Init_SPI_Master();
    if(tam<=50){
    while(1) {
    	COMM_bfnSendMosi (&data[j], sizeof(uint_8));
    }
    }
    return 0 ;
}


void send_Data(){

	if(j==tam){
		j=0;
	}
	else
		j++;
}
