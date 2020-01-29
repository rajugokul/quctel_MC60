/*
 * ymodem.h
 *
 *  Created on: 13-Dec-2019
 *      Author: admin
 */

#ifndef YMODEM_H_
#define YMODEM_H_
//u8 read_serial_data[i];

//--------------------------------definition part--------------------------------------
#define CRC16_F
#define PACKET_HEADER_SIZE      ((u32)3)
#define PACKET_DATA_INDEX       ((u32)4)
#define PACKET_START_INDEX      ((u32)1)
#define PACKET_NUMBER_INDEX     ((u32)2)
#define PACKET_CNUMBER_INDEX    ((u32)3)
#define PACKET_TRAILER_SIZE     ((u32)2)
#define PACKET_OVERHEAD_SIZE    (PACKET_HEADER_SIZE + PACKET_TRAILER_SIZE - 1)
#define PACKET_SIZE             ((u32)128)
#define PACKET_1K_SIZE          ((u32)1024)

/* /-------- Packet in IAP memory ------------------------------------------\
 * | 0      |  1    |  2     |  3   |  4      | ... | n+4     | n+5  | n+6  |
 * |------------------------------------------------------------------------|
 * | unused | start | number | !num | data[0] | ... | data[n] | crc0 | crc1 |
 * \------------------------------------------------------------------------/
 * the first byte is left unused for memory alignment reasons                 */

#define FILE_NAME_LENGTH        ((u32)64)
#define FILE_SIZE_LENGTH        ((u32)16)

#define SOH                     ((u8)0x01)  /* start of 128-byte data packet */
#define STX                     ((u8)0x02)  /* start of 1024-byte data packet */
#define EOT                     ((u8)0x04)  /* end of transmission */
#define ACK                     ((u8)0x06)  /* acknowledge */
#define NAK                     ((u8)0x15)  /* negative acknowledge */
#define CA                      ((u32)0x18) /* two of these in succession aborts transfer */
#define CRC16                   ((u8)0x43)  /* 'C' == 0x43, request 16-bit CRC */
#define NEGATIVE_BYTE           ((u8)0xFF)

#define ABORT1                  ((u8)0x41)  /* 'A' == 0x41, abort by user */
#define ABORT2                  ((u8)0x61)  /* 'a' == 0x61, abort by user */

#define NAK_TIMEOUT             ((u32)0x100000)
#define DOWNLOAD_TIMEOUT        ((u32)5000) /* Five second retry delay */
#define MAX_ERRORS              ((u32)9)

#define YMODEM_TRANSMIT_TIMEOUT 27000 // 27 seconds

/* Exported functions ------------------------------------------------------- */
static struct ymodem1
{
	 u32 packet_length;
	 u32 file_done;
	 u32 errors;
	 u32 session_begin;
	 u32 ramsource;
	 s32 filesize;
	 char fileName[45];
	 u32 packets_received;
	 u8  transmitStatus;
	 u8  transmitPercentage;
	 u8  transmitInProgress;
	 u8  transmitSucess;
	 u8  transmitErrorCode;
	 u8  tx_cmp;
	 u32 ymodTxSendTime;
};

struct ymodem1 receive;


//--------------------------------------------decleration part-----------------------------------
u8 aPacketData[PACKET_1K_SIZE + PACKET_DATA_INDEX + PACKET_TRAILER_SIZE+4];
typedef enum
{
  COM_OK       = 0x00,
  COM_ERROR    = 0x01,
  COM_ABORT    = 0x02,
  COM_TIMEOUT  = 0x03,
  COM_DATA     = 0x04,
  COM_LIMIT    = 0x05
} COM_StatusTypeDef;

typedef enum
{
  HAL_OK       = 0,
  HAL_ERROR    = 1,
  HAL_BUSY     = 2,
  HAL_TIMEOUT  = 3,
  HAL_CONTINUE  = 4,
  HAL_EOT=5
} HAL_StatusTypeDef;

u8 zeroAll=0;
u8 oprComplete=0;

u8 packetDecodeStep=0;
u32 payloadCntr=0;

u32 pOprStartTime=0;

COM_StatusTypeDef Ymodem_Receive(u32 *p_size);
COM_StatusTypeDef Ymodem_Transmit();
void PrepareIntialPacket(u8 *p_data, const u8 *p_file_name, u32 length);
void PreparePacket( u8 *p_packet, u8 pkt_nr, u32 size_blk);
static HAL_StatusTypeDef ReceivePacket(u8 *p_data, u32 *p_length, u32 timeout);
u16 UpdateCRC16(u16 crc_in, u8 byte);
u16 Cal_CRC16(const u8* p_data, u32 size);
u8 CalcChecksum(const u8 *p_data, u32 size);
u8 aFileName[FILE_NAME_LENGTH];
//-----------------------decleration end----------------------------------------------
u8 writeChar(char c)
{
	APP_DEBUG("%c",c)
}

//-------------------------------user function-------------------------------------

COM_StatusTypeDef Ymodem_Receive( u32 *p_size )
{
	static u8 *file_ptr=0;
    static u8 file_size[FILE_SIZE_LENGTH]={0};
    u32 tmp=0,i=0;
    s8 errorCode=0;
    COM_StatusTypeDef result = COM_OK;
    if(zeroAll==1)
    {
    	zeroAll=0;
    	receive.packet_length=0;
    	oprComplete=0;
    	receive.file_done=0;
    	receive.errors=0;
    	receive.session_begin=0;
    	receive.ramsource=0;
    	receive.filesize=0;
    	receive.packets_received=0;
    	file_ptr=0;
    	memset(file_size,'\0',FILE_SIZE_LENGTH);
    }

  if ((oprComplete == 0) && (result == COM_OK))
  {
    if ((receive.file_done == 0) && (result == COM_OK))
    {
    	errorCode=ReceivePacket(aPacketData, &receive.packet_length, DOWNLOAD_TIMEOUT);
      switch(errorCode)
      {
        case HAL_OK:
        //	APP_DEBUG1("\r\n HAL_OK , SZ:%d\r\n",packet_length);
        	receive.errors = 0;
          switch (receive.packet_length)
          {
            case 2:
              /* Abort by sender */
              writeChar(ACK);
              result = COM_ABORT;
              break;
            case 0:
              /* End of transmission */
              writeChar(ACK);
              receive.file_done = 1;

              oprComplete=1;
              break;
            default:
              /* Normal packet */
            	//APP_DEBUG1("LENS => %d : %d\r\n",aPacketData[PACKET_NUMBER_INDEX],receive.packets_received)


                if (receive.packets_received == 0)
                {
                  /* File name packet */

                    /* File name extraction */
                    i = 0;
                    file_ptr = aPacketData + PACKET_DATA_INDEX;
                    while ( (*file_ptr != 0) && (i < FILE_NAME_LENGTH))
                    {
                      aFileName[i++] = *file_ptr++;
                    }

                    /* File size extraction */
                    aFileName[i++] = '\0';
                    i = 0;
                    file_ptr ++;
                    while ( (*file_ptr != ' ') && (i < FILE_SIZE_LENGTH))
                    {
                      file_size[i++] = *file_ptr++;
                    }
                    file_size[i++] = '\0';
                    receive.filesize=atoi(file_size);
//                    Str2Int(file_size, &filesize);

                    /* Test the size of the image to be sent */
                    /* Image size is greater than Flash size */
                    if (*p_size > (1000 + 1))
                    {
                      /* End session */
                      tmp = CA;
                      writeChar(&tmp);
                      writeChar(&tmp);
                      result = COM_LIMIT;
                    }
                    /* erase user application area */
//                    FLASH_If_Erase(APPLICATION_ADDRESS);
                    *p_size = receive.filesize;
                    APP_DEBUG1("\r\nFNAME: %s , FSIZE: %s , FSIZE(INT): %d\r\n",aFileName,file_size,receive.filesize)
                    writeChar(ACK);
                    writeChar(CRC16);
                    // VJ: create UFS FILE HERE
                    format();
                    fileOpen(Y_MODEM_FILE_NAME);

                }
                else /* Data packet */
                {
                	receive.ramsource = (u32) & aPacketData[PACKET_DATA_INDEX];
                  writeChar(ACK);
                  Y_fileWrite(&aPacketData[PACKET_DATA_INDEX],PACKET_1K_SIZE);

                }
                pOprStartTime=millis();
                receive.packets_received++;
                receive.session_begin = 1;
          }
          break;



        case HAL_BUSY: /* Abort actually */
        	writeChar(CRC16);

        	writeChar(CA);
        	writeChar(CA);
          result = COM_ABORT;
          break;

        case HAL_CONTINUE:
        	if(receive.session_begin==0)
        	{
        		 writeChar(CRC16); /* Ask for a packet */
        	}
        	;break;

        case HAL_EOT:

        	 writeChar(EOT);
        	 writeChar(ACK);
        	 receive.file_done = 1;
        	 oprComplete=1;
        	 errorCode=0;
        	 APP_DEBUG1("OPR DONE EOT\r\n");
        	 fileClose();

        	;break;

        default:
          if (receive.session_begin > 0)
          {
        	  receive.errors ++;
          if (receive.errors > MAX_ERRORS)
          {
            /* Abort communication */
        	  writeChar(CA);
        	  writeChar(CA);
          }
          else
          {
        	//  APP_DEBUG1("SESSION ERROR:%d\r\n",errors)
        	  writeChar(CRC16); /* Ask for a packet */
          }
          }
      }
    }
  }

  return result;
}



//--------------------------------ymodem receiver packet -------------------------------
static HAL_StatusTypeDef ReceivePacket(u8 *p_data, u32 *p_length, u32 timeout)
{
  u32 crc=0;
  u32 packet_size = 0;
  HAL_StatusTypeDef status=HAL_CONTINUE;
  u8 char1=0;
  static u32 pRcvTime=0;
  volatile s16 i=0;
  *p_length = 0;
if(packetDecodeStep==0)
{
if(Serial.available(&Serial)>0)
{
char1=Serial.read(&Serial);
     switch (char1)
     {
       case SOH:
         packet_size = PACKET_SIZE;
         packetDecodeStep=1;
         status=HAL_CONTINUE;
         pRcvTime=millis();
         payloadCntr=0;
         break;
       case STX:
         packet_size = PACKET_1K_SIZE;
         packetDecodeStep=1;
         status=HAL_CONTINUE;
         pRcvTime=millis();
         payloadCntr=0;
         break;
       case EOT:
          packetDecodeStep=0;
    	   status=HAL_EOT;
         break;
       case CA:
         packet_size=2;
         status=HAL_OK;
         break;
       case ABORT1:
       case ABORT2:
         status = HAL_BUSY;
         break;
       default:
         status = HAL_ERROR;
         break;
     }
     *p_data = char1;
 }
}
     if(packetDecodeStep==1)
     {
     if (packet_size >= PACKET_SIZE )
     {

    	 	  while(Serial.available(&Serial)>0)
    	 	  {
    	 	  p_data[payloadCntr+PACKET_NUMBER_INDEX]=Serial.read(&Serial);
    	 	  pRcvTime=millis();
    	 	  payloadCntr++;
    	 	  if(payloadCntr>=(packet_size+PACKET_OVERHEAD_SIZE))
    	 	  {
    	 		  status=HAL_OK;
    	 		  break;
    	 	  }
    	 	  else
    	 	      status=HAL_CONTINUE;
    	 	  }
    	if((millis()-pRcvTime)>=timeout)
    	 {
    	 status=HAL_ERROR;
    	 packetDecodeStep=0;
    	 }

       if(status!=HAL_CONTINUE)
       {
       if (status >= HAL_OK )
       {
    	   packetDecodeStep=0;
         if (p_data[PACKET_NUMBER_INDEX] != ((p_data[PACKET_CNUMBER_INDEX]) ^ NEGATIVE_BYTE))
         {
           packet_size = 0;
           status = HAL_ERROR;
         }
         else
         {
           /* Check packet CRC */

           crc = p_data[ packet_size + PACKET_DATA_INDEX ] << 8;
           crc += p_data[ packet_size + PACKET_DATA_INDEX + 1 ];
          // APP_DEBUG1("CRC CHECK, in:%d , CALC:%d , SZ: %d\r\n",crc,Cal_CRC16(&p_data[PACKET_DATA_INDEX], packet_size),packet_size)
           if (Cal_CRC16(&p_data[PACKET_DATA_INDEX], packet_size) != crc )
           {
             packet_size = 0;
             status = HAL_ERROR;
           }
         }
       }
       else
       {
         packet_size = 0;
       }
      }
     }
     }
   *p_length = packet_size;
   return status;
  }

u16 Cal_CRC16(const u8* p_data, u32 size)
{
  u32 crc = 0;
  const u8* dataEnd = p_data+size;

  while(p_data < dataEnd)

  crc = UpdateCRC16(crc, *p_data++);
  crc = UpdateCRC16(crc, 0);
  crc = UpdateCRC16(crc, 0);

  return crc&0xffffu;
}
u16 UpdateCRC16(u16 crc_in, u8 byte)
{
  u32 crc = crc_in;
  u32 in = byte | 0x100;

  do
  {
    crc <<= 1;
    in <<= 1;
    if(in & 0x100)
      ++crc;
    if(crc & 0x10000)
      crc ^= 0x1021;
  }

  while(!(in & 0x10000));

  return crc & 0xffffu;
}

void putString(u8 *str,int len,int offset)
{
	u32 i=0;
   APP_DEBUG1("WRITELEN: %d\r\n",len)
   Ql_UART_Write(UART_PORT1,&str[offset],len);
	for(i=offset;i<(offset+len);i++)
	{
		APP_DEBUG1("\r\n %d) %d",i,aPacketData[i])
	}
}

void Serial_PutByte(char byte)
{
	APP_DEBUG("%c",byte)
}


enum YModemTransmitStates
{
	YMOD_TX_STARTUP=0,
	YMOD_TX_INIT_PACKET,
	YMOD_TX_WAIT_INIT_ACK,
	YMOD_TX_PUT_DATA_PACKET,
	YMOD_TX_WAIT_DATA_ACK,
	YMOD_TX_END_TRANSMIT,
	EMPTY_PACKET_EOT,
	EMPTY_PACKET_WAIT_EOT
};

void transmitFail(u8 errorCode)
{
	          receive.transmitInProgress=0;
			  receive.transmitStatus=YMOD_TX_STARTUP;
			  receive.transmitPercentage=108;
			  receive.transmitSucess=0;
			  receive.transmitErrorCode=errorCode;
}

////////////////////////////////////ymodem_transmit////////////////////////////////
COM_StatusTypeDef Ymodem_Transmit ()
{
	u16 i=0;
  u32  size = 0, pkt_size=0;
  u8   fileExists;
  static u8 ack_recpt=0;
  u8 *p_buf_int;
  COM_StatusTypeDef result = COM_OK;
  static u32 blk_number = 1;
  u8 a_rx_ctrl[2]={0};
  u32 temp_crc=0;
  u8 c=0;
  switch(receive.transmitStatus)
  {

  case YMOD_TX_STARTUP:
  APP_DEBUG1("\r\nYMOD_TX_STARTUP\r\n");
  receive.ymodTxSendTime=millis();
  receive.transmitPercentage=0;
  receive.errors=0;
  blk_number=1;
  receive.transmitStatus=YMOD_TX_INIT_PACKET;
  ;break;

  case YMOD_TX_INIT_PACKET:
	  Ql_memset(receive.fileName,'\0',45);
	  Ql_sprintf(receive.fileName,"%s",Y_MODEM_FILE_NAME);
	  if(Ql_FS_Check(receive.fileName)>=0)
		  fileExists=1;
	  else
		  fileExists=0;
  APP_DEBUG1("\r\nYMOD_TX_INIT_PACKET,FILE: %s, STATUS: %d\r\n",receive.fileName,fileExists);
  if(fileExists==1)
  {
  receive.filesize=Ql_FS_GetSize(receive.fileName);
  Ql_memset(aPacketData,'\0',PACKET_1K_SIZE + PACKET_DATA_INDEX + PACKET_TRAILER_SIZE+4);
  PrepareIntialPacket(aPacketData, receive.fileName, receive.filesize);
  //putString(aPacketData,PACKET_SIZE + PACKET_HEADER_SIZE,1);

  temp_crc = Cal_CRC16(&aPacketData[PACKET_DATA_INDEX], PACKET_SIZE);
  aPacketData[PACKET_SIZE+PACKET_HEADER_SIZE+PACKET_START_INDEX]=(u8)(temp_crc >> 8);
  aPacketData[PACKET_SIZE+PACKET_HEADER_SIZE+PACKET_START_INDEX+1]=(u8)(temp_crc & 0xFF);
  APP_DEBUG1("CRC: %d , %d , %d\r\n",temp_crc, aPacketData[PACKET_SIZE+PACKET_HEADER_SIZE+PACKET_START_INDEX], aPacketData[PACKET_SIZE+PACKET_HEADER_SIZE+PACKET_START_INDEX+1])
  putString(aPacketData,PACKET_SIZE + PACKET_HEADER_SIZE+PACKET_TRAILER_SIZE,PACKET_START_INDEX);
  // Serial_PutByte((u8)(temp_crc >> 8));
 // Serial_PutByte((u8)(temp_crc & 0xFF));
  /*for(i=0;i<135;i++)
  {
	  APP_DEBUG1("%d , %d\r\n",aPacketData[i], [i])
  }*/
  receive.transmitStatus=YMOD_TX_WAIT_INIT_ACK;
  }
  else
  {
	  transmitFail(receive.transmitStatus);
  }
  ;break;

  case YMOD_TX_WAIT_INIT_ACK:
  if(Serial.available(&Serial)>0)
  {
	  c=Serial.read(&Serial);
	  APP_DEBUG1("\r\nIN DATA: %d\r\n",c)
	  if(c==ACK)
	  {
		  receive.transmitStatus=YMOD_TX_PUT_DATA_PACKET;
		  receive.ymodTxSendTime=millis();
		  blk_number=1;
		  APP_DEBUG1("\r\nACK: %d\r\n",c)
	  }
	  else if(c==CA)
	  {
		  APP_DEBUG1("\r\nABORT DATA: %d\r\n",c)
		  transmitFail(receive.transmitStatus);
		  delay(2);
		  result = COM_ABORT;
	  }
	  else
	     {
		  receive.errors++;

		  APP_DEBUG1("\r\nERRORS_)ENTRY: %d\r\n",c)
	     if (receive.errors >= MAX_ERRORS)
	     {
	       result = COM_ERROR;
	       APP_DEBUG1("\r\nERRORS_TERMN: %d\r\n",c)
	       transmitFail(receive.transmitStatus);
	     }
	     else
	     {
	    	 receive.transmitStatus=YMOD_TX_INIT_PACKET;
	    	 receive.ymodTxSendTime=millis();
	     }
	     }
  }
  ;break;

  case YMOD_TX_PUT_DATA_PACKET:
	  APP_DEBUG1("\r\nYMOD_TX_PUT_DATA_PACKET\r\n");
	  size=PACKET_1K_SIZE;
	  Ql_memset(aPacketData,'\0',PACKET_1K_SIZE + PACKET_DATA_INDEX + PACKET_TRAILER_SIZE+4);
	  PreparePacket(aPacketData, blk_number,size);
	  c = 0;
	  receive.errors = 0;
	  if (size >= PACKET_1K_SIZE)
	        {
	          pkt_size = PACKET_1K_SIZE;
	        }
	  else
	        {
	          pkt_size = PACKET_SIZE;
	        }
		temp_crc = Cal_CRC16(&aPacketData[PACKET_DATA_INDEX], pkt_size);
		aPacketData[pkt_size + PACKET_HEADER_SIZE+PACKET_START_INDEX]=(u8)(temp_crc >> 8);
		aPacketData[pkt_size + PACKET_HEADER_SIZE+PACKET_START_INDEX+1]=(u8)(temp_crc & 0xFF);
		putString(aPacketData,pkt_size + PACKET_HEADER_SIZE+PACKET_TRAILER_SIZE,PACKET_START_INDEX);
		blk_number++;
		receive.transmitPercentage=(blk_number*PACKET_1K_SIZE*100)/receive.filesize;
		receive.transmitStatus=YMOD_TX_WAIT_DATA_ACK;
	  break;

  case YMOD_TX_WAIT_DATA_ACK:
	  if(Serial.available(&Serial)>0)
	    {
	  	  c=Serial.read(&Serial);
	  	  if(c==ACK)
	  	  {
	  		  receive.transmitStatus=YMOD_TX_PUT_DATA_PACKET;
	  		  receive.ymodTxSendTime=millis();
	  		  if((blk_number*PACKET_1K_SIZE)>receive.filesize)
	  		  {
	  			  receive.transmitStatus=YMOD_TX_END_TRANSMIT;
	  			receive.transmitPercentage=100;
	  		  }
	  	  }else if(c==CA)
		  {
	  		transmitFail(receive.transmitStatus);
			  delay(2);
			  result = COM_ABORT;
		  }
		  else
		     {
			  receive.errors++;
		     }
		     if (receive.errors >= MAX_ERRORS)
		     {
		    	 transmitFail(receive.transmitStatus);
		       result = COM_ERROR;
		     }
	  }
	  ack_recpt=0;
      break;


  case YMOD_TX_END_TRANSMIT:
	  APP_DEBUG1("\r\nYMOD_TX_END_TRANSMIT\r\n");
	  c = 0x00;
	  receive.errors = 0;
	  if(ack_recpt==0){
		  ack_recpt=1;
		  Serial_PutByte(EOT);
		  Serial_PutByte(EOT);
	  }
		  if(Serial.available(&Serial)>0)
		  	    {
		  	  	  c=Serial.read(&Serial);
		  	  	  if(c==ACK)
		  	  	  {
		  	  		  receive.transmitStatus=EMPTY_PACKET_EOT;
		  	  		  receive.ymodTxSendTime=millis();
		  	  		ack_recpt=1;
		  	  	  }
		  	  	  else if(c==CA){
		  	  		  delay(2);
		  	  		transmitFail(receive.transmitStatus);

		  	  	  }
	            }
	  break;

  case EMPTY_PACKET_EOT:
	    APP_DEBUG1("\r\nEMPTY_PACKET_EOT\r\n");
		aPacketData[PACKET_START_INDEX] = SOH;
		aPacketData[PACKET_NUMBER_INDEX] = 0;
		aPacketData[PACKET_CNUMBER_INDEX] = 0xFF;
		for (i = PACKET_DATA_INDEX; i < (PACKET_SIZE + PACKET_DATA_INDEX); i++)
		    {
		      aPacketData [i] = 0x00;
		    }
		putString(&aPacketData[PACKET_START_INDEX],PACKET_SIZE + PACKET_HEADER_SIZE,PACKET_START_INDEX);
		temp_crc = Cal_CRC16(&aPacketData[PACKET_DATA_INDEX], PACKET_SIZE);
		Serial_PutByte(temp_crc >> 8);
		Serial_PutByte(temp_crc & 0xFF);
		receive.transmitInProgress=0;
		receive.transmitPercentage=100;
		receive.transmitSucess=1;
		receive.tx_cmp=1;
		receive.transmitStatus=YMOD_TX_STARTUP;
	break;

  }
  return result;
  }



///////////////////////////ymodem transmit dependency file//////////////////////////////////////
void PrepareIntialPacket(u8 *p_data, const u8 *p_file_name, u32 length)
{
  u32 i=0,j=0;
  u8 astring[10]={0};

  /* first 3 bytes are constant */
  p_data[0]=1;
  p_data[PACKET_START_INDEX] = SOH;
  p_data[PACKET_NUMBER_INDEX] = 0x00;
  p_data[PACKET_CNUMBER_INDEX] = 0xff;

  /* Filename written */
  for (i = 0; (p_file_name[i] != '\0') && (i < FILE_NAME_LENGTH); i++)
  {
    p_data[i + PACKET_DATA_INDEX] = p_file_name[i];
  }

  p_data[i + PACKET_DATA_INDEX] = 0x00;

  /* file size written */
  Int2Str (astring, length);
  i = i + PACKET_DATA_INDEX + 1;
  while (astring[j] != '\0')
  {
    p_data[i++] = astring[j++];
  }

  /* padding with zeros */
  for (j = i; j < PACKET_SIZE + PACKET_DATA_INDEX; j++)
  {
    p_data[j] = 0;
  }
}



void PreparePacket(u8 *p_packet, u8 pkt_nr, u32 size_blk)
{
  u8 *p_record;
  char *pktBlk;
  u32 i=0, size=0, packet_size=0;
  fileOpen(Y_MODEM_FILE_NAME);
  /* Make first three packet */
  packet_size = size_blk >= PACKET_1K_SIZE ? PACKET_1K_SIZE : PACKET_SIZE;
  size = size_blk < packet_size ? size_blk : packet_size;
  if (packet_size == PACKET_1K_SIZE)
  {
    p_packet[PACKET_START_INDEX] = STX;
  }
  else
  {
    p_packet[PACKET_START_INDEX] = SOH;
  }
  p_packet[PACKET_NUMBER_INDEX] = pkt_nr;
  p_packet[PACKET_CNUMBER_INDEX] = (~pkt_nr);

  pktBlk=getBlockFromFile(receive.fileName,pkt_nr-1,size);
  /* Filename packet has valid data */
  for (i = PACKET_DATA_INDEX; i < size + PACKET_DATA_INDEX;i++)
  {
	  p_packet[i]=pktBlk[i-PACKET_DATA_INDEX];
  }

  if ( size  <= packet_size)
  {
    for (i = size + PACKET_DATA_INDEX; i < packet_size + PACKET_DATA_INDEX; i++)
    {
      p_packet[i] = 0x1A; /* EOF (0x1A) or 0x00 */
    }
  }
  APP_DEBUG1("\r\n-------%d , %d , %d--------------\r\n%s\r\n",pkt_nr,size,receive.filesize,p_packet)
}



void Int2Str(uint8_t *p_str, uint32_t intnum)
{
  uint32_t i, divider = 1000000000, pos = 0, status = 0;

  for (i = 0; i < 10; i++)
  {
    p_str[pos++] = (intnum / divider) + 48;

    intnum = intnum % divider;
    divider /= 10;
    if ((p_str[pos-1] == '0') & (status == 0))
    {
      pos = 0;
    }
    else
    {
      status++;
    }
  }
}


#endif /* YMODEM_H_ */
