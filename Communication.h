#ifndef COMMUNICATION_H_
#define COMMUNICATION_H_
#include "SPI_Driver.h"
uint_8 COMM_bfnReceiveMosi (uint_8* bpData);
uint_8 COMM_bfnSendMosi (uint_8* bpMsgToSend, uint_8 bMsgSize);
void COMM_vfnDriverInitMaster (void);
void COMM_vfnDriverInitSlave (void);
void COMM_vfnDriverInit (void);
uint_8 COMM_bfnSendMsg (uint_8* bpMsgToSend, uint_8 bMsgSize);
uint_8 COMM_bfnReceiveMsg (uint_8* bpDataRx);
#endif
