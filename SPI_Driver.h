#ifndef SPI_DRIVER_H_
#define SPI_DRIVER_H_
#define ERROR 0
#define SUCCESS 1
typedef unsigned char uint_8;
void Init_SPI_Master(void);
void Init_SPI_Slave(void);
uint_8 SPI_Write(uint_8* instructions,uint_8 size);
uint_8 SPI_Read(uint_8* instructions,uint_8 size);
#endif
