#include "ESCP-MIS1.h"
#include <Wire.h>

#define SENSOR_PRESSURE_REG 0x01
#define SENSOR_TEMPERATURE_REG 0x02
#define SENSOR_RESET_REG 0x10
#define SENSOR_SERIALNO_REG 0x11
#define SENSOR_FIRMWARE_REG 0x12
#define SENSOR_STATUS_REG 0x13

ESCPMIS1::ESCPMIS1() {
    fluidDensity = 1029; // default value is for seawater
    i2cAddress = 0x28; // i2c address for parts with "01" serial number 
    atmosphericPressure = 1.01325; // standard atmospheric pressure at sea level
}

void ESCPMIS1::setFluidDensity(float density) {
    fluidDensity = density;
}

void ESCPMIS1::setAtmosphericPressure(float atmospheric_pressure) {
    atmosphericPressure = atmospheric_pressure;
}

void ESCPMIS1::set7bitAddress(unsigned char newaddress) {
    i2cAddress = newaddress;
}

float ESCPMIS1::pressure() {
    float pressure_result = 0f;
     char byte_count = 0;

    // first, we write to the sensor to give the address of the pressure register
    Wire.beginTransmission(i2cAddress);
    Wire.write(SENSOR_PRESSURE_REG);
    Wire.endTransmission();

    // then we read back the result as 4 bytes and assemble them into the float variable
    Wire.requestFrom(i2cAddress,4, true); // request a 4 byte read

   
    while(Wire.available())    // we loop and check because the sensor may send fewer bytes than requested
    {
        unsigned char c = Wire.read();    // receive a byte as character
        *((unsigned char*)(&pressure_result) + (3-byte_count)) = c; // add it to the float
        byte_count++;
    }
    
    return pressure_result; // returns the value in bars
}

float ESCPMIS1::temperature() {
    float temperature_result = 0f;
     char byte_count = 0;

    // first, we write to the sensor to give the address of the temperature register
    Wire.beginTransmission(i2cAddress);
    Wire.write(SENSOR_TEMPERATURE_REG);
    Wire.endTransmission();

    // then we read back the result as 4 bytes and assemble them into the float variable
    Wire.requestFrom(i2cAddress,4, true); // request a 4 byte read

   
    while(Wire.available())    // we loop and check because the sensor may send fewer bytes than requested
    {
        unsigned char c = Wire.read();    // receive a byte as character
        *((unsigned char*)(&temperature_result) + (3-byte_count)) = c; // add it to the float
        byte_count++;
    }
    
    return temperature_result; // returns the value in Celcius
}

float ESCPMIS1::depth() {
    float pressure_result;
    float depth_pascals;
    float depth_metres;

    // get the pressure result
    pressure_result = pressure();

    // convert from pressure in bars to depth pressure in pascals -
    // we scale up to pascals and then subtract atmospheric pressure
    depth_pascals = (pressure_result * 100.0) - (atmosphericPressure *100.0);
    // now divide by fluid density and acceleration due to gravity to get depth in metres
    depth_metres = depth_pascals / (fluidDensity * 9.80665);

    return depth_metres;
};