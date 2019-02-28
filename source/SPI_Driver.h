#ifndef SPI_DRIVER_H_
#define SPI_DRIVER_H_
typedef unsigned char uint_8;
void Init_SPI_Master(void);
void Init_SPI_Slave(void);
void SPI_Write(uint_8* instructions,uint_8 size);
void SPI_Read(uint_8* instructions,uint_8 size);
#endif
