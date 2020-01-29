//----------------------------------------INCLUDES---------------------------------------------------
#ifdef __CUSTOMER_CODE__
#include "defines.h"
#include "ql_trace.h"
#include "ql_system.h"
#include "ql_timer.h"
#include "HELPER_FUNCTIONS.h"
#include "MC60_GPIO.h"
#include "MC60_UART.h"
#include "MC60_STARTUP_COMMONS.h"
#include "MC60_GPS.h"
#include "MC60_GSM.h"
#include "MC60_GPIO.h"
#include "MC60_EXT_WDT.h"
#include "ql_power.h"
#include "MC60_FS.h"
#include "MC60_BTSGPIO.h"
#include "MC60_ADC.h"
#include "menu.h"

///----------------------------------------FUNCTION PROTO-------------------------------------------
void setup();
void loop();
///-----------------------------------------SETUP------------------------------------------------------



void setup()
{
	APP_DEBUG("testing\r\n");
	main_menu();
}


///------------------------------------------LOOP-----------------------------------------------------

void loop()
{

	wdtReset();
	option();

}

#endif

//u8 ser=0;
//if(Serial.available(&Serial)>0){
//	ser=Serial.read(&Serial);
//	APP_DEBUG("%c",ser);
//
//	if(ser=='a'){
//		freeSpace();
//		totalSpace();
//		checkFileExist();
//		fileOpen(Y_MODEM_FILE_NAME);
//		fileWrite("helloworld1234567891011121314151617181920");
//		ofset=0;
//		fileRead();
//		fileClose();
//	}
//	if(ser=='b'){
//			freeSpace();
//			totalSpace();
//			checkFileExist();
//			fileOpen(Y_MODEM_FILE_NAME);
//			fileRead();
//			fileClose();
//		}
//
//	}
