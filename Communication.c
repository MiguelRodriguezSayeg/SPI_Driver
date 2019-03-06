#include "Communication.h"
#include "SPI_Driver.h"
#include "UARTDriver.h"
void COMM_vfnDriverInitMaster (void){
		Init_SPI_Master();
}
void COMM_vfnDriverInitSlave (void){
		Init_SPI_Slave();
		COMM_vfnDriverInit();
}
uint_8 COMM_bfnSendMosi (uint_8* bpMsgToSend, uint_8 bMsgSize)
{
	uint_8 state = ERROR;
        uint_8 checksum = bMsgSize;
        while(bMsgSize>=1)
        {
                if(SPI_Write(*bpMsgToSend,sizeof(uint_8)))
                {
                        bpMsgToSend++;
                        checksum--;
                        bMsgSize--;
                }
        }

        if(checksum == 0)
        {
        	state = SUCCESS;
        }
        else
        {
        	state = ERROR;
        }

        return state;
}
uint_8 COMM_bfnReceiveMosi (uint_8* bpData)
{
        while(SPI_Read(bpData,sizeof(uint_8)) != SUCCESS);
                return SUCCESS;
}
void COMM_vfnDriverInit (void)
{
        UART_vfnDriverInit();
}

uint_8 COMM_bfnSendMsg (uint_8* bpMsgToSend, uint_8 bMsgSize)
{
	uint_8 state = ERROR;
    uint_8 checksum = bMsgSize;
    while(bMsgSize>=1)
    {
            if(UART_bfnSend(*bpMsgToSend))
            {
                    bpMsgToSend++;
                    checksum--;
                    bMsgSize--;
            }
    }

    if(checksum == 0)
    {
    	state = SUCCESS;
    }
    else
    {
     	state = ERROR;
    }

    return state;
}
uint_8 COMM_bfnReceiveMsg (uint_8* bpDataRx)
{
        while(UART_bfnRead(bpDataRx) != SUCCESS);
             return SUCCESS;
}

