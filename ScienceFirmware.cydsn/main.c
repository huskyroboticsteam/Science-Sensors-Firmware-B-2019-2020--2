//This pseudo code is written in the PSoC Creator IDE so the bits of formatting are 
//from that.


#include "project.h"
#include "sensordefines.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "bme280.c"
//#include "CANCommon.h"



//include provided helper libraries for sensor boards
//#include "UVSENSOR_driver.h"

//uint8 BUFFERS [5] = {WEATHERCLICK_BUFFER, AIRQUALITY_BUFFER, UVSENSOR_BUFFER1, UVSENSOR_BUFFER2, SPECTRO_BUFFER};
//uint8 SENSOR_ADDRESSES[5] = {I2C_WEATHERCLICK_ADDRESS, I2C_AIRQUALITY_ADDRESS, I2C_UVSENSOR_ADDRESS_BYTE1, I2C_UVSENSOR_ADDRESS_BYTE2, I2C_SPECTROSCOPY_ADDRESS};
//uint8 STATUS_REGISTERS[5] = {};Read


//FUNCTION DEFINES
void BME280ReadAllData();
void iAQCoreReadAll(uint16_t *final[]);
uint16_t VEML6070ReadAll();
void delay(uint8 milliseconds);
int32 t_fine;
void user_delay_ms(uint32_t period);
int8_t user_i2c_write(uint8_t dev_id, uint8_t reg_addr, uint8_t *reg_data, uint16_t len);
int8_t user_i2c_read(uint8_t dev_id, uint8_t reg_addr, uint8_t *reg_data, uint16_t len);
void print_sensor_data(struct bme280_data *comp_data);
void multiRegisterI2CRead(uint8_t device, uint8_t reg[], uint8_t *data[]);
uint8_t initializeBME280();
uint8_t AS7265xReadReg(uint8_t reg);
void AS7265ReadAll(uint8_t *data[]);



struct bme280_dev dev;
struct bme280_settings settings;

uint8_t ASX7265xregs[24] = {0x14,0x15,0x16,0x17,0x18,0x19,0x1A,0x1B,0x1C,0x1D,0x1E,0x1F,0x20,0x21,0x22,0x23,0x24,0x25,0x26,0x27,0x28,0x29,0x2A,0x2B};


int main(void)
{
    CyGlobalIntEnable; /* Enable global interrupts. */ 
    I2CMaster_Start();
    
    //////////////////Initialize BME280/////////////////////
    //struct bme280_dev dev;
    int8_t rslt = BME280_OK;
    rslt = initializeBME280(&dev);
    
    
    //Initialize VEML6070
    I2CMaster_I2CMasterSendStart(I2C_VEML6070_CMD, I2C_WRITE, 1);
    I2CMaster_I2CMasterWriteByte(I2C_VEML6070_INITIALIZATION_VALUES, 1);
    I2CMaster_I2CMasterSendStop(10);
    
    PWM_Enable();
    PWM_Start();
    
    
    for(;;)
    {
      //check if sensor data update is needed (canbus timer?)
        
        
        //request data from weatherClick
        
        //request data from airQuality2Click
        //request data from UVSensor
        
        
        //process sensor data?
        
        //send data through canbus
        //CyDelay(
    }
    
    return 0;
}


uint8_t initializeBME280(){
    dev.dev_id = BME280_I2C_ADDR_PRIM;
    dev.intf = BME280_I2C_INTF;
    dev.read = user_i2c_read;
    dev.write = user_i2c_write;
    dev.delay_ms = user_delay_ms;
    
    settings.osr_h = BME280_OVERSAMPLING_1X;
	settings.osr_p = BME280_OVERSAMPLING_16X;
	settings.osr_t = BME280_OVERSAMPLING_2X;
	settings.filter = BME280_FILTER_COEFF_16;
	settings.standby_time = BME280_STANDBY_TIME_62_5_MS;
    dev.settings = settings;
    return bme280_init(&dev);
}


//get all data
void collectAll(uint32_t* data[]/*, struct bme280_dev *dev*/);
void collectAll(uint32_t* data[]/*, struct bme280_dev *dev*/)
{
    //bme280
	uint8_t rslt;
    uint8_t settings_sel;
    struct bme280_data comp_data;
    
    settings_sel = BME280_OSR_PRESS_SEL;
	settings_sel |= BME280_OSR_TEMP_SEL;
	settings_sel |= BME280_OSR_HUM_SEL;
	settings_sel |= BME280_STANDBY_SEL;
	settings_sel |= BME280_FILTER_SEL;
	rslt = bme280_set_sensor_settings(settings_sel, &dev);
	rslt = bme280_set_sensor_mode(BME280_NORMAL_MODE, &dev);
	rslt = bme280_set_sensor_settings(settings_sel, &dev);
	rslt = bme280_set_sensor_mode(BME280_NORMAL_MODE, &dev);
    
	rslt = bme280_get_sensor_data(BME280_ALL, &comp_data, &dev);
    dev.delay_ms(70);
    //comp_data pointers have the data
    *data[0] = comp_data.humidity;
    *data[1] = comp_data.pressure;
    *data[2] = comp_data.temperature;
    
    //iAQCore
    uint16_t dat[2];
    iAQCoreReadAll(&dat);
    *data[3] = dat[0];
    *data[4] = dat[1];
    
    //veml6070
    //uint16_t uv = VEML6070ReadAll();
    *data[5] = VEML6070ReadAll();
    
    //AS7265x
    uint8_t spec[5];
    AS7265ReadAll(&spec);
}

//get each sensor data



void iAQCoreReadAll(uint16_t *final[]){
    uint8_t regs[9];
    uint8_t data[9];
    for(uint8_t i = 0; i < 9; i++){
        regs[i] = 0xB5 + i;
    }
    
    multiRegisterI2CRead(I2C_AIRQUALITY_ADDRESS, regs, *data);
    
    uint16_t co2 = (data[0] << 8) + (data[1]);
    uint16_t tvoc = (data[7] << 8) + data[8];
    
    *final[0] = co2;
    *final[1] = tvoc;
}




uint16_t VEML6070ReadAll(){//edit
    uint8 msb, lsb;
    uint32 error;
    
//    if(I2CMaster_I2CMasterStatus() != I2CMaster_I2C_MSTR_NO_ERROR){
//        I2CMaster_I2CMasterClearStatus();
//    }
    I2CMaster_I2CMasterSendStart(I2C_VEML6070_UVDATA_MSB, I2C_READ, 1);
    I2CMaster_I2CMasterReadByte(I2CMaster_I2C_NAK_DATA, &msb, 100);
    I2CMaster_I2CMasterSendStop(1);
    
    I2CMaster_I2CMasterSendStart(I2C_VEML6070_UVDATA_LSB, I2C_READ, 1);
    I2CMaster_I2CMasterReadByte(I2CMaster_I2C_NAK_DATA, &lsb, 100);
    I2CMaster_I2CMasterSendStop(1);
    
    return ((msb << 8) + (lsb));
}

void AS7265xWrite(uint8_t reg, uint8_t data);
void AS7265xWrite(uint8_t reg, uint8_t data){
    uint8_t status;
    
    //check if sensor is busy
    I2CMaster_I2CMasterSendStart(I2C_SPECTRO_WRITE_ADDR, I2C_WRITE, 1);
    I2CMaster_I2CMasterWriteByte(I2C_SPECTRO_SLAVE_STATUS_REG, 1);
    I2CMaster_I2CMasterSendRestart(I2C_SPECTRO_READ_ADDR, I2C_READ, 1);
    while(1){ //check to see if sensor is busy or not
        I2CMaster_I2CMasterReadByte(I2CMaster_I2C_ACK_DATA, &status, 1);
        
        if((status & I2C_SPECTRO_SLAVE_TX_VALID) == 0){
            //I2CMaster_I2CMasterSendStop(1);
            break;
        }
    }
    //specify register to write to
    I2CMaster_I2CMasterSendRestart(I2C_SPECTRO_WRITE_ADDR, I2C_WRITE, 1);
    I2CMaster_I2CMasterWriteByte(I2C_SPECTRO_SLAVE_WRITE_REG, 1);
    I2CMaster_I2CMasterWriteByte(reg, 1);
    
    //check if sensor is busy
    I2CMaster_I2CMasterSendRestart(I2C_SPECTRO_WRITE_ADDR, I2C_WRITE, 1);
    I2CMaster_I2CMasterWriteByte(I2C_SPECTRO_SLAVE_STATUS_REG, 1);
    I2CMaster_I2CMasterSendRestart(I2C_SPECTRO_READ_ADDR, I2C_READ, 1);
    while(1){ //check to see if sensor is busy or not
        I2CMaster_I2CMasterReadByte(I2CMaster_I2C_ACK_DATA, &status, 1);
        
        if((status & I2C_SPECTRO_SLAVE_TX_VALID) == 0){
            //I2CMaster_I2CMasterSendStop(1);
            break;
        }
    }
    //enter data to save to register
    I2CMaster_I2CMasterSendRestart(I2C_SPECTRO_WRITE_ADDR, I2C_WRITE, 1);
    I2CMaster_I2CMasterWriteByte(I2C_SPECTRO_SLAVE_WRITE_REG, 1);
    I2CMaster_I2CMasterWriteByte(data, 1);
    
}


void AS7265ReadAll(uint8_t *data[]){
    //uint8_t regs[5];
    
    for(uint8_t i = 0; i < 24; i++){
        data[i] = AS7265xReadReg(ASX7265xregs[i]);
    }
}



uint8_t AS7265xReadReg(uint8_t reg){
    uint8_t status;
    uint8_t reading;
    
    //check if sensor is busy
    I2CMaster_I2CMasterSendStart(I2C_SPECTRO_WRITE_ADDR, I2C_WRITE, 1);
    I2CMaster_I2CMasterWriteByte(I2C_SPECTRO_SLAVE_STATUS_REG, 1);
    I2CMaster_I2CMasterSendRestart(I2C_SPECTRO_READ_ADDR, I2C_READ, 1);
    while(1){ //check to see if sensor is busy or not
        I2CMaster_I2CMasterReadByte(I2CMaster_I2C_ACK_DATA, &status, 1);
        
        if((status & I2C_SPECTRO_SLAVE_TX_VALID) == 0){
            //I2CMaster_I2CMasterSendStop(1);
            break;
        }
    }
    
    I2CMaster_I2CMasterSendRestart(I2C_SPECTRO_WRITE_ADDR, I2C_WRITE, 1);
    I2CMaster_I2CMasterWriteByte(I2C_SPECTRO_SLAVE_WRITE_REG, 1);
    I2CMaster_I2CMasterWriteByte(reg, 1);
    
    I2CMaster_I2CMasterSendRestart(I2C_SPECTRO_WRITE_ADDR, I2C_WRITE, 1);
    I2CMaster_I2CMasterWriteByte(I2C_SPECTRO_SLAVE_STATUS_REG, 1);
    I2CMaster_I2CMasterSendRestart(I2C_SPECTRO_READ_ADDR, I2C_READ, 1);
    while(1){ //check to see if sensor is busy or not
        I2CMaster_I2CMasterReadByte(I2CMaster_I2C_ACK_DATA, &status, 1);
        
        if((status & I2C_SPECTRO_SLAVE_TX_VALID) == 0){
            //I2CMaster_I2CMasterSendStop(1);
            break;
        }
    }
    I2CMaster_I2CMasterSendRestart(I2C_SPECTRO_WRITE_ADDR, I2C_WRITE, 1);
    I2CMaster_I2CMasterWriteByte(I2C_SPECTRO_SLAVE_READ_REG, 1);
    I2CMaster_I2CMasterSendRestart(I2C_SPECTRO_READ_ADDR, I2C_READ, 1);
    I2CMaster_I2CMasterReadByte(I2CMaster_I2C_NAK_DATA, &reading, 1);
    
    return reading;
}





void multiRegisterI2CRead(uint8_t device, uint8_t reg[], uint8_t* data[]){
   
    I2CMaster_I2CMasterSendStart(device, I2C_WRITE, 1);
    
    for(uint8_t i = 0; i < (sizeof(&reg)/sizeof(&reg[0])); i++){
        I2CMaster_I2CMasterWriteByte(reg[i], 1);
        I2CMaster_I2CMasterSendRestart(device, I2C_READ, 1);
        
        if(i == (sizeof(*reg)/sizeof(reg[0])) -1){
            I2CMaster_I2CMasterReadByte(I2CMaster_I2C_NAK_DATA, data[i], 1);
        } else{
            I2CMaster_I2CMasterReadByte(I2CMaster_I2C_ACK_DATA, data[i], 1);
        }
    }
    I2CMaster_I2CMasterSendStop(1);
}





void singleRegisterI2CWrite(uint8_t device, uint8_t reg, uint8_t data);
void singleRegisterI2CWrite(uint8_t device, uint8_t reg, uint8_t data){
    I2CMaster_I2CMasterSendStart(device, I2C_WRITE, 1);
    I2CMaster_I2CMasterWriteByte(reg, 1);
    I2CMaster_I2CMasterWriteByte(data, 1);
    I2CMaster_I2CMasterSendStop(1);
}


void singleRegisterI2CRead(uint8_t device, uint8_t reg, uint8_t *storage);
void singleRegisterI2CRead(uint8_t device, uint8_t reg, uint8_t *storage){
    I2CMaster_I2CMasterSendStart(device, I2C_WRITE, 1);
    I2CMaster_I2CMasterWriteByte(reg, 1);
    I2CMaster_I2CMasterSendRestart(device, I2C_READ, 1);
    I2CMaster_I2CMasterReadByte(I2CMaster_I2C_NAK_DATA, storage, 1);
    I2CMaster_I2CMasterSendStop(1);
}

void delay(uint8 milliseconds) {
    uint8 pause;
    clock_t now,then;

    pause = milliseconds*(CLOCKS_PER_SEC/1000);
    now = then = clock();
    while( (now-then) < pause )
        now = clock();
}



//////////////////////////////////////////////////BME280 driver setup//////////////////////////////////////////////////////

int8_t stream_sensor_data_normal_mode(struct bme280_dev *dev)
{
	int8_t rslt;
	uint8_t settings_sel;
	struct bme280_data comp_data;

	/* Recommended mode of operation: Indoor navigation */
	dev->settings.osr_h = BME280_OVERSAMPLING_1X;
	dev->settings.osr_p = BME280_OVERSAMPLING_16X;
	dev->settings.osr_t = BME280_OVERSAMPLING_2X;
	dev->settings.filter = BME280_FILTER_COEFF_16;
	dev->settings.standby_time = BME280_STANDBY_TIME_62_5_MS;

	settings_sel = BME280_OSR_PRESS_SEL;
	settings_sel |= BME280_OSR_TEMP_SEL;
	settings_sel |= BME280_OSR_HUM_SEL;
	settings_sel |= BME280_STANDBY_SEL;
	settings_sel |= BME280_FILTER_SEL;
	rslt = bme280_set_sensor_settings(settings_sel, dev);
	rslt = bme280_set_sensor_mode(BME280_NORMAL_MODE, dev);

	printf("Temperature, Pressure, Humidity\r\n");
	while (1) {
		/* Delay while the sensor completes a measurement */
		dev->delay_ms(70);
		rslt = bme280_get_sensor_data(BME280_ALL, &comp_data, dev);
		print_sensor_data(&comp_data);
	}
	return rslt;
}

void print_sensor_data(struct bme280_data *comp_data)
{
#ifdef BME280_FLOAT_ENABLE
        printf("%0.2f, %0.2f, %0.2f\r\n",comp_data->temperature, comp_data->pressure, comp_data->humidity);
#else
        printf("%ld, %ld, %ld\r\n",(long)comp_data->temperature, (long)comp_data->pressure, (long)comp_data->humidity);
#endif
}



int8_t user_i2c_write(uint8_t dev_id, uint8_t reg_addr, uint8_t *reg_data, uint16_t len)
{
    int8_t rslt = 0; /* Return 0 for Success, non-zero for failure */

    /*
     * The parameter dev_id can be used as a variable to store the I2C address of the device
     */
    I2CMaster_I2CMasterSendStart(dev_id, I2C_WRITE, 1);
    for(uint8 i = 0; i < len; i++){
        I2CMaster_I2CMasterWriteByte(reg_addr, 1);
        rslt = I2CMaster_I2CMasterWriteByte((reg_data[i]), 1);
    }
    I2CMaster_I2CMasterSendStop(1);
    return rslt;
}


int8_t user_i2c_read(uint8_t dev_id, uint8_t reg_addr, uint8_t *reg_data, uint16_t len)
{
    int8_t rslt = 0; /* Return 0 for Success, non-zero for failure */
    /*
     * The parameter dev_id can be used as a variable to store the I2C address of the device
     */
    I2CMaster_I2CMasterSendStart(dev_id, I2C_WRITE, 1);
    I2CMaster_I2CMasterWriteByte(reg_addr, 1);
    I2CMaster_I2CMasterSendRestart(dev_id, I2C_READ, 1);
    
    for(uint8 i = 0; i < len; i++){
        if(i != len - 1){
            rslt = I2CMaster_I2CMasterReadByte(I2CMaster_I2C_ACK_DATA, &(reg_data[i]), 1);
        }
        else{
            rslt = I2CMaster_I2CMasterReadByte(I2CMaster_I2C_NAK_DATA, &(reg_data[i]), 1);
        }
    }
    I2CMaster_I2CMasterSendStop(1);
    return rslt;
}

void user_delay_ms(uint32_t period)
{
    uint8 pause;
    clock_t now,then;

    pause = period*(CLOCKS_PER_SEC/1000);
    now = then = clock();
    while( (now-then) < pause )
        now = clock();
}
///////////////////////////////////////////BME280 Compensating raw data/////////////////////////////////////////////
//void bme280GetCompensationValues();
//void bme280GetCompensationValues(){
//    uint8 bufferLength = 32;
//    uint8 buffer [bufferLength];
//    int32 error;
//    I2CMaster_I2CMasterSendStart(I2C_WEATHERCLICK_ADDRESS, I2C_WRITE, 1);
//    I2CMaster_I2CMasterWriteByte(0x88, 1);                                  //0x88 is the first register
//    I2CMaster_I2CMasterSendStart(0x88, I2C_WRITE, 1);                       //to get compensation values
//    
//    for(uint8 i = 0; i < bufferLength; i++){
//        if(i != bufferLength - 1){
//            error = I2CMaster_I2CMasterReadByte(I2CMaster_I2C_ACK_DATA, &(buffer[i]), 1);
//        }
//        else{
//            error = I2CMaster_I2CMasterReadByte(I2CMaster_I2C_NAK_DATA, &(buffer[i]), 1);
//        }
//    }
//    I2CMaster_I2CMasterSendStop(1);
//}
//
//
//void bme280CompensationBitProcessing(uint8 buffer[]);
//void bme328CompensationBitProcessing(uint8 buffer[]){
//    uint32 compValues [18];
//    
//    compValues[0] = (buffer[1] << 8) + (buffer[0]);         //T1
//    compValues[1] = (buffer[3] << 8) + (buffer[2]);         //T2
//    compValues[2] = (buffer[5] << 8) + (buffer[4]);         //T3
//    compValues[3] = (buffer[7] << 8) + (buffer[6]);         //P1
//    compValues[4] = (buffer[9] << 8) + (buffer[8]);         //P2
//    compValues[5] = (buffer[11] << 8) + (buffer[10]);       //P3
//    compValues[6] = (buffer[13] << 8) + (buffer[12]);       //P4
//    compValues[7] = (buffer[15] << 8) + (buffer[14]);       //P5
//    compValues[8] = (buffer[17] << 8) + (buffer[16]);       //P6
//    compValues[9] = (buffer[19] << 8) + (buffer[18]);       //P7
//    compValues[10] = (buffer[21] << 8) + (buffer[20]);      //P8
//    compValues[11] = (buffer[23] << 8) + (buffer[22]);      //P9
//    compValues[12] = buffer[24];                            //H1
//    compValues[13] = (buffer[26] << 8) + (buffer[25]);      //H2
//    compValues[14] = buffer[27];                            //H3
//    compValues[15] = (buffer[28] << 4) + (buffer[29] & 15); //H4
//    compValues[16] = (buffer[29] & 240) + (buffer[30] << 4);//H5
//    compValues[17] = buffer[31];
//    
//}
//
//
//void bme280DataBitProcessing(uint8 buffer[]);
//void bme328DataBitProcessing(uint8 buffer[]){
//    uint32 dataRaw [3] = {(buffer[0] << 12) + (buffer[1] << 4) + buffer[2], (buffer[3] << 12) + (buffer[4] << 4) + buffer[5], (buffer[6] << 8) + (buffer[7])};
//    //(buffer[0] << 12) + (buffer[1] << 4) + buffer[2]      Pressure
//    //(buffer[3] << 12) + (buffer[4] << 4) + buffer[5]      Temperature
//    //(buffer[6] << 8) + (buffer[7])                        Humidity
//}
//
//int32 bme280TempCompensation(int32 a, uint32 buffer[]);
//int32 bme280TempCompensation(int32 a, uint32 buffer[]){
//    //int32 t_fine;
//    int32 var1, var2, T;
//    var1 = ((((a >> 3) - ((int32) T1 << 1 ))) * ((int32) T2)) >> 11;
//    var2 = (((((a >> 4) - ((int32) T1)) * ((a >> 4 ) - ((int32)T1))) >> 12) * ((int32)T3)) >> 14;
//    t_fine = var1 + var2;
//    T = (t_fine * 5 + 128) >> 8;
//    return T;    
//}
//
//
//uint32 bme280PressureCompensation(int32 a, uint32 comp[]);
//uint32 bme280PressureCompensation(int32 a, uint32 comp[]){
//    int64 var1, var2, p;
//    var1 = ((int64)t_fine) - 128000;
//    var2 = var1 * var1 * (int64)P6;
//    var2 = var2 + ((var1*(int64)P5) << 17);
//    var2 = var2 + (((int64)P4)<<35);
//    var1 = ((var1 * var1 * (int64)P3)>>8) + ((var1 + (int64)P2)<<12;
//    var1 = (((((int64)1)<<47)+var1))*((int64)P1)>>33;
//    
//    if(var1 == 0){
//        return 0;
//    }
//    p = 1048576 - a;
//    p = (((p<<31)-var2)*3125)/var1;
//    var1 = (((int64)P9) * (p>>13) * (p>>13)) >> 25;
//    var2 = (((int64)P8) * p) >> 19;
//    p = ((p + var1 + var2) >> 8) + (((int64)P7)<<4);
//    return (uint32)p;
//}
//
//
//uint32 bme280HumidityCompensation(int32 a, uint32 comp[]);
//uint32 bme280HumidityCompensation(int32 a, uint32 comp[]){
//    int32 var1;
//    
//    var1 = (t_fine - ((int32)76800));
//    var1 = (((((a << 14) - (((int32)H4) << 20) - (((int32)H5) *
//            var1)) + ((int32)16384)) >> 15) * (((((((var1 *
//            ((int32)H6))>> 10) * (((var1 * ((int32)H3)) >> 11 +
//            ((int32)32768))) >> 10) + ((int32)2097152)) * ((int32)H2) +
//            8192) >> 14));
//    var1 = (var1 - (((((var1 >> 15) * (var1 >> 15)) >> 7) *
//            ((int32)H1)) >> 4));
//    var1 = (var1 < 0 ? 0 : var1);
//    var1 = (var1 > 419430400 ? 149430400 : var1);
//    return (uint32)(var1 >> 12);
//}
//void bme280ReadAll();
//void bme280ReadAll(){
//    uint8 buffer [WEATHERCLICK_BUFFER_LENGTH];
//    int32 error;
//    I2CMaster_I2CMasterSendStart(I2C_WEATHERCLICK_ADDRESS, I2C_WRITE, 1);
//    I2CMaster_I2CMasterWriteByte(I2C_WEATHERCLICK_PRESSURE_MSB, 1);
//    I2CMaster_I2CMasterSendStart(I2C_WEATHERCLICK_PRESSURE_MSB, I2C_WRITE, 1);
//    
//    for(uint8 i = 0; i < WEATHERCLICK_BUFFER_LENGTH; i++){
//        if(i != WEATHERCLICK_BUFFER_LENGTH - 1){
//            error = I2CMaster_I2CMasterReadByte(I2CMaster_I2C_ACK_DATA, &(buffer[i]), 1);
//        }
//        else{
//            error = I2CMaster_I2CMasterReadByte(I2CMaster_I2C_NAK_DATA, &(buffer[i]), 1);
//        }
//    }
//    I2CMaster_I2CMasterSendStop(1);
//}






//canbus transmission method
//  sends data through canbus
//  (the format/type of the data will be determined later depending
//   on what needs to be sent, i.e. if all sensor data will always
//   be sent together, or if sensor data needs to be able to be sent
//   individually, etc.)