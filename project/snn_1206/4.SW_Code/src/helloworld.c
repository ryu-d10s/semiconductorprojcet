#include <stdio.h>
#include "platform.h"
#include "xil_printf.h"
#include "xil_io.h"
#include "sleep.h"
#include "peri_iic_ctrl.h"

#define  BASE_ADDR                  0x43C00000

#define  DOUBLE_BUFFER_ADDR_1       BASE_ADDR+0x04
#define  DOUBLE_BUFFER_ADDR_2       BASE_ADDR+0x08
#define  OVR1              	      BASE_ADDR+0x0c
#define  OVR2				            BASE_ADDR+0x10
#define  STATUS				         BASE_ADDR+28
#define  COORD 					      BASE_ADDR
#define  COLOR_KEY 		            BASE_ADDR+(4*20)
#define  PERI_SETUP                 BASE_ADDR+0x14

#define  CAM_rst_seq_done           0
#define  odd_even_write             1
#define  HSYNC_lock                 2
#define  Frame_lock                 3

#define  CAM_rst_req                14
#define  overlay_enable             13
#define  LCD_en                     11
#define  CAM_en                     9 
#define  Touch_rstb                 8 
#define  LCD_rstb                   7 
#define  LCD_mode                   6 
#define  LCD_shlr                   5 
#define  LCD_updn                   4 
#define  LCD_dith                   3 
#define  LCD_W_LED_en               2 
#define  LCD_W_LED_ctrl             1 
#define  LCD_DRV_ctrl               0 

int chk_status(void * addr, int bit_shift)
{
   u32 status = Xil_In32(addr);
   if(status & ((u32)1 << bit_shift))
   {
      return 1;
   }
   else
   {
      return 0;
   }
}

void bit_on(void * addr, int bit_shift)
{
   u32 value = *(u32 *)addr;
   value = value | (1<<bit_shift);
   *(u32 *)addr = value;
}

void bit_off(void * addr, int bit_shift)
{
   u32 value = *(u32 *)addr;
   value = value & ~((u32)1<<bit_shift);
   *(u32 *)addr = value;
}

int main()
{

	init_platform();
   Xil_ICacheEnable();
   Xil_DCacheEnable();
	peri_iic_initialize ();
   int I2C_error_count =0;

   if(Xil_In32(0xF800000C) != 0)
      Xil_Out32(0xF8000008,0xDF0D); // System-Level Control Registers SLCR unlock









	Xil_Out32(PERI_SETUP, 0x0000); // all reset state
	printf("Allreset\n");


   bit_on(PERI_SETUP, LCD_mode      );
   bit_on(PERI_SETUP, LCD_dith      );
   bit_on(PERI_SETUP, LCD_W_LED_en  );
   bit_on(PERI_SETUP, LCD_W_LED_ctrl);
   bit_on(PERI_SETUP, LCD_DRV_ctrl  );
   bit_on(PERI_SETUP, LCD_shlr      );
	printf("LCD_MODE_SETTING\n");

   bit_on(PERI_SETUP, CAM_rst_req   );
	printf("CAM reset request\n");




	Xil_Out32(DOUBLE_BUFFER_ADDR_1, (uint)0x10000000);
	Xil_Out32(DOUBLE_BUFFER_ADDR_2, (uint)0x10400000);
   // Set camera double buffer address

	Xil_Out32(COORD, (uint)0<<12 | (uint)300);
   // Set frame coordinate

	Xil_Out32(OVR1, (uint)0x10C00000);
	Xil_Out32(OVR2, (uint)0x11000000);
   // Set camera double buffer address

	unsigned int base1 = (uint)0x10C00000;
	unsigned int base2 = (uint)0x11000000;
	for(int y = 0; y<1080;y++)
	{
		for(int x = 0; x<1920 ; x++)
		{

			if (x<100)
			{
				Xil_Out16(base1, (uint)x<<12 | (uint)y);
				Xil_Out16(base2, (uint)x<<12 | (uint)y);
				base1 += 2;
				base2 += 2;
			}
			else if(y<540)
			{
				Xil_Out16(base1, 0x00);
				Xil_Out16(base2, 0x00);
				base1 += 2;
				base2 += 2;
			} else
			{
				Xil_Out16(base1, (uint)x<<12 | (uint)y);
				Xil_Out16(base2, (uint)x<<12 | (uint)y);
				base1 += 2;
				base2 += 2;
			}
		}
	}

   bit_on(PERI_SETUP, LCD_rstb       );
   bit_off(PERI_SETUP, CAM_rst_req   );
	printf("LCD, Camera reset escape\n");



	while(!chk_status(STATUS, CAM_rst_seq_done)) // wait for cam reset
	{
		printf("Wait cam rst\n");
	}


	peri_iic_check_id ();
	int i = 0;

	I2C_error_count += img_zn220_initialize(ZN220_IIC_SLAVE_ADDR);
	printf("cam I2C error count %d \n", I2C_error_count );

	usleep(1000);

   bit_on(PERI_SETUP, CAM_en    );
   bit_on(PERI_SETUP, Touch_rstb);


   bit_on(PERI_SETUP, LCD_en     );
   bit_off(PERI_SETUP, LCD_W_LED_en    );

    while(1){
    	volatile u32 a;
    	char c;

      if(chk_status(STATUS, odd_even_write))
      {
         printf("Even frame is in writting...\n");
      }
      else
      {
         printf("Odd frame is in writting...\n");
      }
      if(!chk_status(STATUS, HSYNC_lock    ))
      {
         printf("HSYNC lock is break!!!\n");
      }
      if(!chk_status(STATUS, Frame_lock    ))
      {
         printf("Frame lock is break!!!\n");
      }
    }

    cleanup_platform();
    return 0;
}
