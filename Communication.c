#include "Communication.h"
#include "SPI_Driver.h"
void COMM_vfnDriverInitMaster (void){
		Init_SPI_Master();
}
void COMM_vfnDriverInitSlave (void){
		Init_SPI_Slave();
}
uint_8 COMM_bfnSendMosi (uint_8* bpMsgToSend, uint_8 bMsgSize)
{
        uint_8 checksum = bMsgSize;
        for(;bMsgSize>=8;bMsgSize--)
        {
                if(SPI_Write(bpMsgToSend,sizeof(uint_8)))
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
