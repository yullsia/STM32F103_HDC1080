# STM32F103_HDC1080

//This is the code to use HDC1080 in stm32f103.
//However, if you have stm32 hal, you can use it in other stm32 series.
//The I2C channel can be changed in the header file, and it is changed according to the I2C channel used by STM32.

# function
- HDC1080_init
- HDC1080_SerialID
- HDC1080_ManufacturerID
- HDC1080_DeviceID
- HDC1080_read_Tempreature
- HDC1080_read_Humidity

HDC1080_init : This function sets the I2C initialization for communicating with the HDC1080 and the configuration of the HDC1080.
There are no parameters.

HDC1080_SerialID : This function gets the serial ID of HDC1080. The parameter is uint8_t* and requires a total of 6 bytes.

HDC1080_ManufacturerID : This function requests the manufacturer ID of HDC1080. The parameter is uint16_t and requires a total of 2 bytes.

HDC1080_DeviceID : This function requests the device ID of HDC1080. The parameter is uint16_t* and requires a total of 2 bytes.

HDC1080_read_Tempreature : This function reads the temperature measured by HDC1080. The parameter is uint16_t* and requires a total of 2 bytes.

HDC1080_read_Humidity : This function reads the humidity measured by HDC1080. The parameter is uint16_t* and requires a total of 2 bytes.
