#include "peri_iic_ctrl.h"
#include "zn220_initialize_list.h"

s32 peri_iic_initialize ()
{
	s32 Status = 0;
	XIicPs_Config *iic_cfg_Img, *iic_cfg_CVBS;

	iic_cfg_Img = XIicPs_LookupConfig (ZN220_IIC_DEVICE_ID);

	Status |= XIicPs_CfgInitialize (&XiicPs_Img, iic_cfg_Img, iic_cfg_Img->BaseAddress);


	if (Status != XST_SUCCESS)
	{
		printf ("IIC Initialize Fail.\r\n");
		return XST_FAILURE;
	}

	XIicPs_SetSClk (&XiicPs_Img, ZN220_IIC_SCLK);
	if (Status != XST_SUCCESS)
	{
		printf ("IIC Initialize Fail.\r\n");
		return XST_FAILURE;
	}

	return XST_SUCCESS;
}


s32 peri_iic_check_id ()
{
	s32 Status = 0;
	u8 img_iic_id = 0, cvbs_iic_id = 0;

	Status |= peri_iic_read_data (&XiicPs_Img, ZN220_IIC_SLAVE_ADDR, 0x04, &img_iic_id, 1);


	if (Status != XST_SUCCESS)
	{
		printf ("IIC Read ID Fail.\r\n");
		return XST_FAILURE;
	}
	else
	{
		printf ("Image Sensor ID = %x\r\n", img_iic_id);

		return XST_SUCCESS;
	}
}


s32 peri_iic_write_data (XIicPs *iic_Inst, u8 iic_Slave_Addr, u8 writeAddr, u8 writeData)
{
	s32 Status = 0;
	u8 writeBuffer[2] = {0};
	u32 try=0;
	u32 d;

	// 8Bit Register Address
	writeBuffer[0] = writeAddr;
	writeBuffer[1] = writeData;
	int error_count = 0;

	Status = XIicPs_MasterSendPolled(iic_Inst, writeBuffer, 2, iic_Slave_Addr);
	for(d = 0; d <200000; d++);
	while (Status != XST_SUCCESS)
	{
		error_count++;
		printf("error while I2C Write addr : %d, value : %d\n", writeAddr , writeData);
		printf("try again... : %d\n", try);
		try++;
		Xil_Out32(0xF8000224, 0x03);
		for(d = 0; d <800000; d++);
		Xil_Out32(0xF8000224, 0x00);
		for(d = 0; d <800000; d++);
		peri_iic_initialize ();
		Status = XIicPs_MasterSendPolled(iic_Inst, writeBuffer, 2, iic_Slave_Addr);
		for(d = 0; d <800000; d++);
		if(try == 10)
			return error_count;
	}
	try = 0;
	// Bus Wait
	while(XIicPs_BusIsBusy(iic_Inst))
	{
		printf("while write bus busy BUS RST...\n");
		Xil_Out32(0xF8000224, 0x03);
		for(d = 0; d <800000; d++);
		Xil_Out32(0xF8000224, 0x00);
		for(d = 0; d <800000; d++);
		peri_iic_initialize ();
		try++;
		if(try == 10)
			return error_count;
	};

	return error_count;
}


s32 peri_iic_read_data (XIicPs *iic_Inst, u8 iic_Slave_Addr, u8 readAddress, u8 *dataBuffer, u8 readNum)
{
	s32 Status = 0;
	u8 writeBuffer = 0;

	writeBuffer = readAddress;

	XIicPs_SetOptions(iic_Inst, XIICPS_REP_START_OPTION);

	// Register Address Set
	Status |= XIicPs_MasterSendPolled(iic_Inst, &writeBuffer, 1, iic_Slave_Addr);

	if (Status != XST_SUCCESS)
	{
		printf("error while I2C Read\n");
		return XST_FAILURE;
	}

	// Repeat Start Option Clear
	XIicPs_ClearOptions(iic_Inst, XIICPS_REP_START_OPTION);

	// Read Data
	Status |= XIicPs_MasterRecvPolled(iic_Inst, dataBuffer, readNum, iic_Slave_Addr);

	if (Status != XST_SUCCESS)
	{
		printf("error while I2C Read\n");
		return XST_FAILURE;
	}

	int d;
	int try = 0;
	int error_count = 0;
	// Bus Wait
	while(XIicPs_BusIsBusy(iic_Inst))
	{
		error_count++;
		printf("while write bus busy BUS RST...\n");
		Xil_Out32(0xF8000224, 0x03);
		for(d = 0; d <800000; d++);
		Xil_Out32(0xF8000224, 0x00);
		for(d = 0; d <800000; d++);
		peri_iic_initialize ();
		try++;
		if(try == 10)
			return error_count;
	};

	return XST_SUCCESS;
}


s32 img_zn220_initialize (u8 addr)
{
	s32 Status = 0;
	u32 i = 0;
	u32 d = 0;
	u8 img_iic_value;

	int err_cnt = 0;

	int temp = sizeof(zn220reg);


	for (i=0; i < sizeof(zn220reg)/sizeof(zn220reg_info); i++)
	{
		err_cnt  += peri_iic_write_data (&XiicPs_Img, addr, zn220reg[i].addr, zn220reg[i].initvalue);
	}
	printf ("IIC Initialize done.\r\n");

	return err_cnt;
}
