/**************************************************
 *           HDC1080 Device Driver                *
 *            MCU : STM32F103C8T6                 *
 *                 HDC1080.c                      *
 *           Junsu Shim 2022-03-09                *
 **************************************************/

/* Private include */
#include "HDC1080.h"
#include "i2c.h"
#include <math.h>

/* Private define */

/* Private typedef */

/* Private variables */
#ifdef I2C1
extern I2C_HandleTypeDef hi2c1;
#else
extern I2C_HandleTypeDef hi2c2;
#endif  

/* Private function prototypes */
static HAL_StatusTypeDef HDC1080_read( uint8_t point, uint8_t* buffer );
static HAL_StatusTypeDef HDC1080_write( uint8_t point, uint8_t* buffer );

/* Private functions code */
/**************************
 * HDC1080 initialization *
 **************************/
HAL_StatusTypeDef HDC1080_init( void ){
  HAL_StatusTypeDef error = HAL_OK;
  uint8_t HDC1080_conf[2];
  
  //HDC1080 set configuration
  HDC1080_conf[0] = SOFT_RESET | HEAT_OFF | ACQUISITION | TRES_14BIT | HRES_14BIT;
  HDC1080_conf[1] = 0x00;
  
  //I2C init
#ifdef I2C1
  MX_I2C1_Init();
#else
  MX_I2C2_Init();
#endif  
  //HDC1080 write configuration
  error = HDC1080_write(CONFIGURATION, &HDC1080_conf[0]);
  
  return error;
}

/**************************
 * Read HDC1080 Serial ID *
 **************************/
HAL_StatusTypeDef HDC1080_SerialID( uint8_t* SerialID ){
  HAL_StatusTypeDef error;
  uint8_t temp[6];
  int i;
  
  for(i = 0; i < 3; i++){
    error = HDC1080_read(SERIAL_ID1 + i, &temp[2 * i]);
    HAL_Delay(1);
    if(error != HAL_OK){
      return error;
    }
  }
  
  for(i = 0; i < 5; i++){
    SerialID[i] = temp[i];
  }
  return error;
}

/****************************
 * Read HDC Manufacturer ID *
 ****************************/
HAL_StatusTypeDef HDC1080_ManufacturerID( uint16_t* ManudacturerID ){
  return HDC1080_read(MANUFATURER_ID, (uint8_t*)ManudacturerID);
}

/**********************
 * Read HDC Device ID *
 **********************/
HAL_StatusTypeDef HDC1080_DeviceID( uint16_t* DeviceID ){
  return HDC1080_read(DEVICE_ID, (uint8_t*)DeviceID);
}

/************************
 * Read HDC Tempreature *
 ************************/
HAL_StatusTypeDef HDC1080_read_Tempreature( uint16_t* Tempreature ){
  HAL_StatusTypeDef error;
  uint16_t temp;
  
  error = HDC1080_read(DEVICE_ID, (uint8_t*)&temp);
  if(error != HAL_OK){
    *Tempreature = 0;
    return error;
  }
  
  *Tempreature = temp/(uint8_t)pow((float)2, (float)16) * 165 - 40;
  return error;
}

/*********************
 * Read HDC Humidity *
 *********************/
HAL_StatusTypeDef HDC1080_read_Humidity( uint16_t* Humidity ){
  HAL_StatusTypeDef error;
  uint16_t temp;
  
  error = HDC1080_read(DEVICE_ID, (uint8_t*)&temp);
  if(error != HAL_OK){
    *Humidity = 0;
    return error;
  }
  
  *Humidity = temp/(uint8_t)pow((float)2, (float)16) * 100;
  return error;
}

static HAL_StatusTypeDef HDC1080_read( uint8_t point, uint8_t* buffer ){
  HAL_StatusTypeDef error;
  
#ifdef I2C1
  error = HAL_I2C_Mem_Read_IT(&hi2c1, HDC_ADDR, point, 1, buffer, 2);
#else
  error = HAL_I2C_Mem_Read_IT(&hi2c2, HDC_ADDR, point, 1, buffer, 2);
#endif
  
  return error;
}

static HAL_StatusTypeDef HDC1080_write( uint8_t point, uint8_t* buffer ){
  HAL_StatusTypeDef error;
  
#ifdef I2C1
  error = HAL_I2C_Mem_Write_IT(&hi2c1, HDC_ADDR, point, 1, buffer, 2);
#else
  error = HAL_I2C_Mem_Write_IT(&hi2c2, HDC_ADDR, point, 1, buffer, 2);
#endif
  return error;
}