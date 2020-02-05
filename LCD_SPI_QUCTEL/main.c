//#ifdef __CUSTOMER_CODE__
//
////#define REMOVE_PROGRAM_HANG // TO REMOVE PROGRAM HANG
//
//#include "defines.h"
//#include "ql_trace.h"
//#include "ql_system.h"
//#include "ql_timer.h"
//#include "HELPER_FUNCTIONS.h"
//#include "MC60_GPIO.h"
//#include "MC60_UART.h"
//#include "MC60_STARTUP_COMMONS.h"
//#include "MC60_GPS.h"
//#include "MC60_GSM.h"
//#include "MC60_BTSGPIO.h"
//#include "MC60_EXT_WDT.h"
//#include "ql_power.h"
//
//s32 gret;
//s32 adc1[10];
//s32 adc2[10];
//
//void setup()
//{
//	APP_DEBUG("SETUP IN TASK\r\n");
//	initializeZTIInterface();
//
//}
//
//void loop()
//{
//	static u32 pTme=0,cntr=0;
//	wdtReset();
//	ltoWConv.dataLong=readDATAFromBus(READ_DATA_FRAME,cntr);
//	APP_DEBUG("RESP: %d, %d , %d\r\n",(ltoWConv.dataWord[0] & 0xFFFF),(ltoWConv.dataWord[1] & 0x7FFF),ltoWConv.dataLong)
//	delay(500);
//}
//#endif



/////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////twi attiny to quct////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////
#ifdef __CUSTOMER_CODE__

//#define REMOVE_PROGRAM_HANG // TO REMOVE PROGRAM HANG

#include "defines.h"
#include "ql_trace.h"
#include "ql_system.h"
#include "ql_timer.h"
#include "HELPER_FUNCTIONS.h"
//#include "MC60_GPIO.h"
#include "MC60_UART.h"
#include "MC60_STARTUP_COMMONS.h"
#include "MC60_GPS.h"
#include "MC60_GSM.h"
//#include "MC60_GPIO.h"
#include "MC60_EXT_WDT.h"
#include "ql_power.h"

#include "DISP_SPI_INIT.h"
//#include "MC60_delay.h"

s32 gret;

void setup()
{
//    APP_DEBUG("SETUP IN TASK\r\n");
	init_Spi();
	disp_gpio_init();
	ILI9341_Init();
	ILI9341_setRotation(2);
	ILI9341_Fill(COLOR_BLUE);
	//ILI9341_printText("ZUPPA", 130, 140, COLOR_BLACK,COLOR_BLUE, 7);
	ILI9341_Puts(180, 140,"ZUPPA", &TM_Font_16x26 ,COLOR_BLACK,COLOR_BLUE);
//	APP_DEBUG("SETUP IN TASK\r\n");
}

void loop()
{
	wdtReset();

}
#endif
