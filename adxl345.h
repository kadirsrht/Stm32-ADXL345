/*
 * adxl345.h
 *
 *  Created on: May 25, 2024
 *      Author: proje4
 */

#ifndef INC_ADXL345_H_
#define INC_ADXL345_H_

#include "main.h"
#define ADXL_I2C_PORT 		hi2c3		//This line change should if different use i2c port

#define ADXL_DEVICE_ADDRESS 0xA6		//Devıce Register Adress
#define	DEVID				0x00		//Device ID
#define	THRESH_TAP			0x1D		//Tap threshold
#define	OFSX				0x1E		//X-axis offset
#define	OFSY				0x1F		//Y-axis offset
#define	OFSZ				0x20		//Z-axis offset
#define	DUR					0x21		//Tap duration
#define	Latent				0x22		//Tap latency
#define	Window				0x23		//Tap window
#define	THRESH_ACT			0x24		//Activity threshold
#define	THRESH_INACT		0x25		//Inactivity threshold
#define	TIME_INACT			0x26		//Inactivity time
#define	ACT_INACT_CTL		0x27		//Axis enable control for activity and inactivity detection
#define	THRESH_FF			0x28		//Free-fall threshold
#define	TIME_FF				0x29		//Free-fall time
#define	TAP_AXES			0x2A		//Axis control for single tap/double tap
#define	ACT_TAP_STATUS		0x2B		//Source of single tap/double tap
#define	BW_RATE				0x2C		//Data rate and power mode control
#define	POWER_CTL			0x2D		//Power-saving features contro
#define	INT_ENABLE 			0x2E		//Interrupt enable control
#define	INT_MAP				0x2F		//Interrupt mapping control
#define	INT_SOURCE 			0x30		//Source of ınterrupts
#define	DATA_FORMAT			0x31		//Data format control
#define	DATAX0				0x32		//X-Axis Data 0
#define	DATAX1 				0x33		//X-Axis Data 1
#define	DATAY0				0x34		//Y-Axis Data 0
#define	DATAY1 				0x35		//Y-Axis Data 1
#define	DATAZ0				0x36		//Z-Axis Data 0
#define	DATAZ1				0x37		//Z-Axis Data 1
#define	FIFO_CTL			0x38		//FIFO control
#define	FIFO_STATUS			0x39		//FIFO STATUS

#define TIMEOUT				1000		//TIMEOUT OVER VALUE

#define X					DATAX0		//X AXXIS REGISTER VALUE
#define Y					DATAY0		//Y AXXIS REGISTER VALUE
#define Z					DATAZ0		//Z AXXIS REGISTER VALUE

#define SCALE_FACTOR_2G		(float)1/256.0
#define SCALE_FACTOR_4G		(float)1/128.0
#define SCALE_FACTOR_8G		(float)1/64.0
#define SCALE_FACTOR_16G	(float)1/32.0


#define WAKEUP_8HZ			0x00		//WAKEUP BITS 8HZ
#define WAKEUP_4HZ			0x01		//WAKEUP BITS 4HZ
#define WAKEUP_2HZ			0x02		//WAKEUP BITS 2HZ
#define WAKEUP_1HZ			0x03		//WAKEUP BITS 1HZ

#define RANGE_2G 			0x00		//RANGE +-2G
#define RANGE_4G 			0x01		//RANGE +-4G
#define RANGE_8G 			0x02		//RANGE +-8G
#define RANGE_16G 			0x03		//RANGE +-16G

#define BW_RATE_1600		0x0F		//1600Hz Baud
#define BW_RATE_800			0x0E		//800Hz Baud
#define BW_RATE_400			0x0D		//400Hz Baud
#define BW_RATE_200			0x0C		//200Hz Baud
#define BW_RATE_100			0x0B		//100Hz Baud
#define BW_RATE_50			0x0A		//50Hz Baud
#define BW_RATE_25			0x09		//25Hz Baud

typedef enum{
	READ_FAIL=0,
	READ_SUCCESS=1,
}ADCL345ReadStatus;

typedef enum{
	INIT_FAIL=0,
	INIT_SUCCES=1,
}ADCL345InitStatus;

typedef enum{
	WRITE_FAIL=0,
	WRITE_SUCCES=1,
}ADCL345WriteStatus;

typedef struct{
	uint8_t Wakeup: 2; 		/* Bits 0-1  0x00->8Hz, 0x01->4Hz, 0x02->2Hz, 0x03->1Hz*/
	uint8_t Sleep: 1; 		// Bits 2 (Sleep)
	uint8_t Measure: 1; 	// Bits 3 (default 0x01)
	uint8_t AUTO_SLEEP: 1;	// Bits 4 ()
	uint8_t Link: 1;		// Bits 5 ()
	uint8_t Reserved: 2;	// Bits 6-7 (Reserved)
}PowerControlRegister_t;

typedef struct{
	uint8_t Range:	2;		//BİT 0-1, 0x00-> +-2g, 0x01-> +-4g, 0x02-> +-8g, 0x03-> +-16g
	uint8_t Justify: 1;		//BİT 2,0x00
	uint8_t Full_res: 1;	//BİT 3,0x00
	uint8_t D4: 1;			//BİT 4,Reserved 0x00
	uint8_t INT_INVERT: 1;	//BİT 5,0x00
	uint8_t SPI: 1;			//BİT 6,0x00
	uint8_t SelfTest: 1;	//BİT 7,0x00 no, 0x01 Ok
}DataFormatRegister_t;

typedef struct{
	uint8_t Rate:	4;		//BİT 0-1-2-3
	uint8_t LowPower: 1;	//BİT 4,
	uint8_t RESERVED: 3;	//BİT 5-6-7, 0X00
}BWRATERegister_t;

int ADXL345_ScanDeviceId(I2C_HandleTypeDef hi2cx);

ADCL345InitStatus ADXL345_Init(void);
ADCL345ReadStatus ADXL345_ReadRegisterData(I2C_HandleTypeDef hi2cx, uint16_t registerAddress, uint16_t sizeOfData, uint8_t *dataBuffer);
ADCL345WriteStatus ADXL345_WriteRegisterData(I2C_HandleTypeDef hi2cx, uint16_t registerAddress, uint16_t value);

int16_t ADXL345_getAxisValue(uint8_t axis);

float ADXL345_getGValue(uint8_t axis, float scaleFactor);

#endif /* INC_ADXL345_H_ */
