#ifndef SRC_PERI_IIC_CTRL_H_
#define SRC_PERI_IIC_CTRL_H_

#include "stdio.h"
#include "xiicps.h"

#define ZN220_IIC_DEVICE_ID 	XPAR_PS7_I2C_1_DEVICE_ID


#define ZN220_IIC_SCLK 		100000



#define ZN220_IIC_SLAVE_ADDR	(0x80>>1)



XIicPs XiicPs_Img;


// Common Functions
s32 peri_iic_initialize ();
s32 peri_iic_check_id ();
s32 peri_iic_write_data (XIicPs *iic_Inst, u8 iic_Slave_Addr, u8 writeAddr, u8 writeData);
s32 peri_iic_read_data (XIicPs *iic_Inst, u8 iic_Slave_Addr, u8 readAddress, u8 *dataBuffer, u8 readNum);
// Image Sensor
s32 img_zn220_initialize (u8 addr);

#endif /* SRC_PERI_IIC_CTRL_H_ */
