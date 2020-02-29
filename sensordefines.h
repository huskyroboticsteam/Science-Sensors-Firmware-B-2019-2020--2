//create global variables of I2C addresses for each sensor board
#define I2C_WEATHERCLICK_ADDRESS        0x76    //BME280
#define I2C_AIRQUALITY_ADDRESS          0x5A    //iAQ-core
#define I2C_UVSENSOR_ADDRESS_BYTE1      0x71    //VEML6070
#define I2C_UVSENSOR_ADDRESS_BYTE2      0x73    //VEML6070
#define I2C_SPECTRO_READ_ADDR           0x93    //AS7265x
#define I2C_SPECTRO_WRITE_ADDR          0x92    //AS7265x

//Weatherclick I2C data on pages 31 and 32 of datasheet
//Register information starts on page 25 of datasheet
#define I2C_WEATHERCLICK_PRESSURE_MSB   0xF7    // Bit orientation
#define I2C_WEATHERCLICK_PRESSURE_LSB   0xF8    // 
#define I2C_WEATHERCLICK_PRESSURE_XLSB  0xF9    //  
#define I2C_WEATHERCLICK_TEMP_MSB       0xFA    // 
#define I2C_WEATHERCLICK_TEMP_LSB       0xFB    // [MSB],[LSB],[XLSB]
#define I2C_WEATHERCLICK_TEMP_XLSB      0xFC    // 
#define I2C_WEATHERCLICK_HUMIDITY_MSB   0xFD    // 
#define I2C_WEATHERCLICK_HUMIDITY_LSB   0xFE    // 
#define WEATHERCLICK_BUFFER_LENGTH      8

//                                              to request a read from this sensor
//                                              initiate a standard read (address + 1 to read)
//                                              the board will send back 9 bytes.
#define I2C_AIRQUALITY_READ_REG         0xB5    //Read register (no write register exists)
#define I2C_AIRQUALITY_CO2_READING_MSB  0u      //CO2 ppm MSB byte location
#define I2C_AIRQUALITY_CO2_READING_LSB  1u      //CO2 ppm LSB byte location
#define I2C_AIRQUALITY_STATUS_REGISTER  2u      //CO2 status register byte location
#define I2C_AIRQUALITY_STATUS_OK        0x00    //  stuff is fine
#define I2C_AIRQUALITY_STATUS_RUNIN     0x10    //  stuff is getting readu
#define I2C_AIRQUALITY_STATUS_BUSY      0x01    //  stuff is busy
#define I2C_AIRQUALITY_STATUS_ERROR     0x80    //  stuff is wrong
#define I2C_AIRQUALITY_RESISTANCE_REG1  3u      //Sensor resistor location (always zero)
#define I2C_AIRQUALITY_RESISTANCE_REG2  4u      //Sensor resistance MSB
#define I2C_AIRQUALITY_RESISTANCE_REG3  5u      //Sensor resistance LSB
#define I2C_AIRQUALITY_RESISTANCE_REG4  6u      //Sensor resistanve XLSB
#define I2C_AIRQUALITY_TVOC_MSB         7u      //TVOC ppb byte MSB location
#define I2C_AIRQUALITY_TVOC_LSB         8u      //TVOC ppb byte LSB location
#define AIRQUALITY_BUFFER_LENGTH    9u


#define I2C_VEML6070_UVDATA_LSB             0x71    //second 8 bits of total 16 bit data
#define I2C_VEML6070_UVDATA_MSB             0x73    //first 8 bits of total 16 bit data
#define I2C_VEML6070_ARA                    0x18    //used to check if an action can occur or not
                                                //check VEML6070 datasheet page 7 for details
#define I2C_VEML6070_CMD                    0x70
#define I2C_VEML6070_INITIALIZATION_VALUES  0x06
#define UVSENSOR_BUFFER_LENGTH              1
                                                

#define I2C_SPECTRO_SLAVE_STATUS_REG    0x00
#define I2C_SPECTRO_SLAVE_WRITE_REG     0x01
#define I2C_SPECTRO_SLAVE_READ_REG      0x02
#define I2C_SPECTRO_SLAVE_TX_VALID      0x02
#define I2C_SPECTRO_SLAVE_RX_VALID      0x01
#define SPECTRO_BUFFER_LENGTH           3


#define I2C_WRITE 0
#define I2C_READ 1


#define I2C_CLOCK_PIN P4A
#define I2C_DATA_PIN P4B


#define PIN_ON 1u
#define PIN_OFF 0u

#define PACKET_SOP 0x01u
#define PACKET_EOP 0x17u

#define TRANSFER_CMPLT      (0x00u)
#define TRANSFER_ERROR      (0xFFu)

#define CMD_DELAY 500;