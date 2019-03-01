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
        uint_8 checksum = bMsgSize;
        for(;bMsgSize>=8;bMsgSize--)
        {
                if(SPI_Write(*bpMsgToSend,sizeof(uint_8)))
                {
                        bpMsgToSend++;
                        checksum--;
                }
                else
                        return ERROR;
        }
        if(checksum == 0)
                return SUCCESS;
        else
                return ERROR;
}
uint_8 COMM_bfnReceiveMosi (uint_8* bpData)
{
        if(SPI_Read(bpData,sizeof(uint_8)))
                return SUCCESS;
        else
                return ERROR;
}
void COMM_vfnDriverInit (void){
        UART_vfnDriverInitPorts();
}

uint_8 COMM_bfnSendMsg (uint_8* bpMsgToSend, uint_8 bMsgSize)
{
        uint_8 checksum = bMsgSize/8;
        for(;bMsgSize>=8;bMsgSize-=8)
        {
                if(UART_bfnSend(*bpMsgToSend))
                {
                        bpMsgToSend++;
                        checksum--;
                }
                else
                        return ERROR;
        }
        if(checksum == 0)
                return SUCCESS;
        else
                return ERROR;
}
uint_8 COMM_bfnReceiveMsg (uint_8* bpDataRx)
{
        if(UART_bfnRead(bpDataRx))
                return SUCCESS;
        else
                return ERROR;
}

