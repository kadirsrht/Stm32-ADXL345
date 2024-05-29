/*
 * adxl345.c
 *
 *  Created on: May 25, 2024
 *      Author: proje4
 */


#include"adxl345.h"
extern I2C_HandleTypeDef ADXL_I2C_PORT;

/*
 * If you didn't know devise address or You want can questioning device adress must use this function.
 * But device I2C adress defined in adxl345.h(ADXL_DEVICE_ADDRESS)
 */
int ADXL345_ScanDeviceId(I2C_HandleTypeDef hi2cx)
{
	for(uint8_t address=0; address<255; address++)
	{
		if(HAL_I2C_IsDeviceReady(&hi2cx, address,1, TIMEOUT) == HAL_OK)
		{
			return address;
		}
	}
	return -1;
}



/*
 * This function is use for reading any register address to
 */
ADCL345ReadStatus ADXL345_ReadRegisterData(I2C_HandleTypeDef hi2cx, uint16_t registerAddress, uint16_t sizeOfData, uint8_t *dataBuffer)
{
	if(HAL_I2C_Mem_Read(&hi2cx, ADXL_DEVICE_ADDRESS, registerAddress, 1, dataBuffer, sizeOfData, TIMEOUT)==HAL_OK)
	{
		return READ_SUCCESS;
	}
	return READ_FAIL;
}



/*
 * This function IS use for writing any register address to
 */
ADCL345WriteStatus ADXL345_WriteRegisterData(I2C_HandleTypeDef hi2cx, uint16_t registerAddress, uint16_t value)
{
	uint8_t data[2] = {0};
	data[0] = registerAddress;
	data[1] = value;

	if(HAL_I2C_Master_Transmit(&hi2cx, ADXL_DEVICE_ADDRESS, data, sizeof(data), TIMEOUT)==HAL_OK)
	{
		return WRITE_SUCCES;
	}
	return WRITE_FAIL;
}



/*
 * This FUNCTION read to device ID and init function
 */
ADCL345InitStatus ADXL345_Init(void)
{
	uint8_t dataBuffer = 0;
	ADXL345_ReadRegisterData(ADXL_I2C_PORT, DEVID, 1, &dataBuffer);

	if(dataBuffer != 0xE5)
	{
		return INIT_FAIL;
	}
	uint8_t tempReg = 0;
	PowerControlRegister_t powerControl = {0};//All save data set to 0
	powerControl.Wakeup = WAKEUP_8HZ;
	powerControl.Sleep = 0x00;
	powerControl.Measure = 0x01;
	powerControl.AUTO_SLEEP = 0x00;
	powerControl.Link = 0x00;
	powerControl.Reserved = 0x00;
	tempReg = *((uint8_t*)&powerControl);
	ADXL345_WriteRegisterData(ADXL_I2C_PORT, POWER_CTL, tempReg);

	DataFormatRegister_t dataFormatControl ={0};//All save data set to 0
	dataFormatControl.Range = RANGE_4G;
	dataFormatControl.Justify = 0x00;
	dataFormatControl.Full_res = 0x00;
	dataFormatControl.D4 = 0x00;
	dataFormatControl.INT_INVERT = 0x00;
	dataFormatControl.SPI = 0x00;
	dataFormatControl.SelfTest = 0x00;
	tempReg = *((uint8_t*)&dataFormatControl);
	ADXL345_WriteRegisterData(ADXL_I2C_PORT, DATA_FORMAT, tempReg);

	BWRATERegister_t BWRateControl ={0};//All save data set to 0
	BWRateControl.Rate = BW_RATE_800;
	BWRateControl.LowPower = 0x00;
	BWRateControl.RESERVED = 0x00;
	tempReg = *((uint8_t*)&BWRateControl);
	ADXL345_WriteRegisterData(ADXL_I2C_PORT, BW_RATE, tempReg);

	return INIT_SUCCES;
}
int16_t ADXL345_getAxisValue(uint8_t axis)
{

	uint8_t data[2] = {0};
	int16_t outputData = 0;
	ADXL345_ReadRegisterData(hi2c3, axis, 2, data);
	outputData = ((data[1]<<8) | data[0]);
	return outputData;
}

float ADXL345_getGValue(uint8_t axis, float scaleFactor)
{
	int16_t outputData = 0;
	float gData = 0;
 	outputData = ADXL345_getAxisValue(axis);
	gData = (float)(outputData * scaleFactor);
	return gData;
}
