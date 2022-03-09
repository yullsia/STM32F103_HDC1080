/**************************************************
 *           HDC1080 Device Driver                *
 *            MCU : STM32F103C8T6                 *
 *                  HDC1080.h                     *
 *           Junsu Shim 2022-03-09                *
 **************************************************/

/* HDC1080 include */
#include "stdint.h"
#include "stm32f1xx_hal.h"

/* HDC1080 define */
/* use I2C channel */
#define I2C1
//#define I2C2

/* HDC1080 address */
#define HDC_ADDR                0x40<<1

/* HDC1080 configuration */
#define SOFT_RESET              0x80
#define HEAT_ON                 0x20
#define HEAT_OFF                0x00
#define ACQUISITION             0x00
#define SEQUENCE                0x10
#define TRES_14BIT              0x00
#define TRES_11BIT              0x04
#define HRES_14BIT              0x00
#define HRES_11BIT              0x01
#define HRES_8bit               0x02

/* HDC1080 configuration area */
#define RESET                   0x8000
#define HEAT                    0x2000
#define MODE                    0x1000
#define BTST                    0x0800
#define TRES                    0x0400
#define HRES                    0x0300

/* HDC1080 typedef */
/* HDC1080 point */
typedef enum{
  TEMPERATURE      =      0x00,
  HUMIDITY         =      0x01,
  CONFIGURATION    =      0x02,
  SERIAL_ID1       =      0xFB,
  SERIAL_ID2       =      0xFC,
  SERIAL_ID3       =      0xFD,
  MANUFATURER_ID   =      0xFE,
  DEVICE_ID        =      0xFF
}HDC1080_point;

/* HDC1080 functions prototypes */
HAL_StatusTypeDef HDC1080_init               ( void );
HAL_StatusTypeDef HDC1080_SerialID           ( uint8_t* SerialID );
HAL_StatusTypeDef HDC1080_ManufacturerID     ( uint16_t* ManudacturerID );
HAL_StatusTypeDef HDC1080_DeviceID           ( uint16_t* DeviceID );
HAL_StatusTypeDef HDC1080_read_Tempreature   ( uint16_t* Tempreature );
HAL_StatusTypeDef HDC1080_read_Humidity      ( uint16_t* Humidity );