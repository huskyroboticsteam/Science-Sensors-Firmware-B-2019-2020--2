//This pseudo code is written in the PSoC Creator IDE so the bits of formatting are 
//from that.

#include "project.h"
#include "sensordefines.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

//#include <time.h>

//include provided helper libraries for sensor boards
//#include "UVSENSOR_driver.h"

//uint8 BUFFERS [5] = {WEATHERCLICK_BUFFER, AIRQUALITY_BUFFER, UVSENSOR_BUFFER1, UVSENSOR_BUFFER2, SPECTRO_BUFFER};
uint8 SENSOR_ADDRESSES[5] = {I2C_WEATHERCLICK_ADDRESS, I2C_AIRQUALITY_ADDRESS, I2C_UVSENSOR_ADDRESS_BYTE1, I2C_UVSENSOR_ADDRESS_BYTE2, I2C_SPECTROSCOPY_ADDRESS};
//uint8 STATUS_REGISTERS[5] = {};Read

void BME280ReadAllData();

void iAQReadAll();
void VEML6070ReadAll();
void delay(uint8 milliseconds);

int32 t_fine;

int main(void)
{
    CyGlobalIntEnable; /* Enable global interrupts. */ 
    
   
    //I2CMaster_Start();
    
    
    
    
    
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


//get all data
//get each sensor data


void VEML6070ReadAll(){
    uint8 buffer [2];
    uint32 error;
    
    I2CMaster_I2CMasterSendStart(I2C_UVSENSOR_UVDATA_MSB, I2C_READ, 1);
    I2CMaster_I2CMasterReadByte(I2CMaster_I2C_NAK_DATA, &buffer[0], 1);
    I2CMaster_I2CMasterSendStop(1);
    
    I2CMaster_I2CMasterSendStart(I2C_UVSENSOR_UVDATA_LSB, I2C_READ, 1);
    I2CMaster_I2CMasterReadByte(I2CMaster_I2C_NAK_DATA, &buffer[1], 1);
    I2CMaster_I2CMasterSendStop(1);
}



void iAQReadAll(){
    uint8 buffer [AIRQUALITY_BUFFER_LENGTH];
    int32 error;
    I2CMaster_I2CMasterSendStart(I2C_AIRQUALITY_ADDRESS, I2C_READ, 1);
    
    for(uint8 i = 0; i < AIRQUALITY_BUFFER_LENGTH; i++){
        if(i != AIRQUALITY_BUFFER_LENGTH - 1){
            error = I2CMaster_I2CMasterReadByte(I2CMaster_I2C_ACK_DATA, &(buffer[i]), 1);
        }
        else{
            error = I2CMaster_I2CMasterReadByte(I2CMaster_I2C_NAK_DATA, &(buffer[i]), 1);
        }
    }
    I2CMaster_I2CMasterSendStop(1);
}

void bme280GetData();
void bme280GetData(){
    
}


void bme280ReadAll();
void bme280ReadAll(){
    uint8 buffer [WEATHERCLICK_BUFFER_LENGTH];
    int32 error;
    I2CMaster_I2CMasterSendStart(I2C_WEATHERCLICK_ADDRESS, I2C_WRITE, 1);
    I2CMaster_I2CMasterWriteByte(I2C_WEATHERCLICK_PRESSURE_MSB, 1);
    I2CMaster_I2CMasterSendStart(I2C_WEATHERCLICK_PRESSURE_MSB, I2C_WRITE, 1);
    
    for(uint8 i = 0; i < WEATHERCLICK_BUFFER_LENGTH; i++){
        if(i != WEATHERCLICK_BUFFER_LENGTH - 1){
            error = I2CMaster_I2CMasterReadByte(I2CMaster_I2C_ACK_DATA, &(buffer[i]), 1);
        }
        else{
            error = I2CMaster_I2CMasterReadByte(I2CMaster_I2C_NAK_DATA, &(buffer[i]), 1);
        }
    }
    I2CMaster_I2CMasterSendStop(1);
}

void bme280GetCompensationValues();
void bme280GetCompensationValues(){
    uint8 bufferLength = 32;
    uint8 buffer [bufferLength];
    int32 error;
    I2CMaster_I2CMasterSendStart(I2C_WEATHERCLICK_ADDRESS, I2C_WRITE, 1);
    I2CMaster_I2CMasterWriteByte(0x88, 1);                                  //0x88 is the first register
    I2CMaster_I2CMasterSendStart(0x88, I2C_WRITE, 1);                       //to get compensation values
    
    for(uint8 i = 0; i < bufferLength; i++){
        if(i != bufferLength - 1){
            error = I2CMaster_I2CMasterReadByte(I2CMaster_I2C_ACK_DATA, &(buffer[i]), 1);
        }
        else{
            error = I2CMaster_I2CMasterReadByte(I2CMaster_I2C_NAK_DATA, &(buffer[i]), 1);
        }
    }
    I2CMaster_I2CMasterSendStop(1);
}


void bme280CompensationBitProcessing(uint8 buffer[]);
void bme328CompensationBitProcessing(uint8 buffer[]){
    uint32 compValues [18];
    
    compValues[0] = (buffer[1] << 8) + (buffer[0]);         //T1
    compValues[1] = (buffer[3] << 8) + (buffer[2]);         //T2
    compValues[2] = (buffer[5] << 8) + (buffer[4]);         //T3
    compValues[3] = (buffer[7] << 8) + (buffer[6]);         //P1
    compValues[4] = (buffer[9] << 8) + (buffer[8]);         //P2
    compValues[5] = (buffer[11] << 8) + (buffer[10]);       //P3
    compValues[6] = (buffer[13] << 8) + (buffer[12]);       //P4
    compValues[7] = (buffer[15] << 8) + (buffer[14]);       //P5
    compValues[8] = (buffer[17] << 8) + (buffer[16]);       //P6
    compValues[9] = (buffer[19] << 8) + (buffer[18]);       //P7
    compValues[10] = (buffer[21] << 8) + (buffer[20]);      //P8
    compValues[11] = (buffer[23] << 8) + (buffer[22]);      //P9
    compValues[12] = buffer[24];                            //H1
    compValues[13] = (buffer[26] << 8) + (buffer[25]);      //H2
    compValues[14] = buffer[27];                            //H3
    compValues[15] = (buffer[28] << 4) + (buffer[29] & 15); //H4
    compValues[16] = (buffer[29] & 240) + (buffer[30] << 4);//H5
    compValues[17] = buffer[31];
    
}


void bme280DataBitProcessing(uint8 buffer[]);
void bme328DataBitProcessing(uint8 buffer[]){
    uint32 dataRaw [3] = {(buffer[0] << 12) + (buffer[1] << 4) + buffer[2], (buffer[3] << 12) + (buffer[4] << 4) + buffer[5], (buffer[6] << 8) + (buffer[7])};
    //(buffer[0] << 12) + (buffer[1] << 4) + buffer[2]      Pressure
    //(buffer[3] << 12) + (buffer[4] << 4) + buffer[5]      Temperature
    //(buffer[6] << 8) + (buffer[7])                        Humidity
}

int32 bme280TempCompensation(int32 a, uint32 buffer[]);
int32 bme280TempCompensation(int32 a, uint32 buffer[]){
    //int32 t_fine;
    int32 var1, var2, T;
    var1 = ((((a >> 3) - ((int32) T1 << 1 ))) * ((int32) T2)) >> 11;
    var2 = (((((a >> 4) - ((int32) T1)) * ((a >> 4 ) - ((int32)T1))) >> 12) * ((int32)T3)) >> 14;
    t_fine = var1 + var2;
    T = (t_fine * 5 + 128) >> 8;
    return T;    
}


uint32 bme280PressureCompensation(int32 a, uint32 comp[]);
uint32 bme280PressureCompensation(int32 a, uint32 comp[]){
    int64 var1, var2, p;
    var1 = ((int64)t_fine) - 128000;
    var2 = var1 * var1 * (int64)P6;
    var2 = var2 + ((var1*(int64)P5) << 17);
    var2 = var2 + (((int64)P4)<<35);
    var1 = ((var1 * var1 * (int64)P3)>>8) + ((var1 + (int64)P2)<<12;
    var1 = (((((int64)1)<<47)+var1))*((int64)P1)>>33;
    
    if(var1 == 0){
        return 0;
    }
    p = 1048576 - a;
    p = (((p<<31)-var2)*3125)/var1;
    var1 = (((int64)P9) * (p>>13) * (p>>13)) >> 25;
    var2 = (((int64)P8) * p) >> 19;
    p = ((p + var1 + var2) >> 8) + (((int64)P7)<<4);
    return (uint32)p;
}


uint32 bme280HumidityCompensation(int32 a, uint32 comp[]);
uint32 bme280HumidityCompensation(int32 a, uint32 comp[]){
    int32 var1;
    
    var1 = (t_fine - ((int32)76800));
    var1 = (((((a << 14) - (((int32)H4) << 20) - (((int32)H5) *
            var1)) + ((int32)16384)) >> 15) * (((((((var1 *
            ((int32)H6))>> 10) * (((var1 * ((int32)H3)) >> 11 +
            ((int32)32768))) >> 10) + ((int32)2097152)) * ((int32)H2) +
            8192) >> 14));
    var1 = (var1 - (((((var1 >> 15) * (var1 >> 15)) >> 7) *
            ((int32)H1)) >> 4));
    var1 = (var1 < 0 ? 0 : var1);
    var1 = (var1 > 419430400 ? 149430400 : var1);
    return (uint32)(var1 >> 12);
}



void delay(uint8 milliseconds) {
    uint8 pause;
    clock_t now,then;

    pause = milliseconds*(CLOCKS_PER_SEC/1000);
    now = then = clock();
    while( (now-then) < pause )
        now = clock();
}



//canbus transmission method
//  sends data through canbus
//  (the format/type of the data will be determined later depending
//   on what needs to be sent, i.e. if all sensor data will always
//   be sent together, or if sensor data needs to be able to be sent
//   individually, etc.)