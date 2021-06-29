/* Cardiff University ES Systems ESCP-MIS1 Arduino pressure/temperature sensor library

Title: Cardiff University ES Systems ESCP-MIS1 Arduino pressure/temperature sensor library

Description: This library provides a simple interface to ES Systems
ESCP-MIS1 sensor. It communicates over I2C and reads data from the sensor.

Authors: Dr Michael R Prior-Jones, Cardiff University, UK.

Acknowledgements:
API inspired by the BlueRobotics Keller LD library,
https://github.com/bluerobotics/BlueRobotics_KellerLD_Library

-------------------------------
The MIT License (MIT)
Copyright (c) 2021 Michael R Prior-Jones

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:
The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.
THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.
-------------------------------*/

#ifndef ESCP_MIS1
#define ESCP_MIS1

#include "Arduino.h"

class ESCPMIS1 {
    public:
        ESCPMIS1();

        /* This sets the fluid density for the depth() function in kg/m3.
           It defaults to 1029 kg/m3 for salt water. 
           Set it to 997 for fresh water.*/
        void setFluidDensity(float density);

        /* This sets the atmospheric pressure for the depth() function.
           The value is in bars (not millibars).
           It will default to 1.01325 bars, which is
           "standard atmospheric pressure at sea level". */ 

        void setAtmosphericPressure(float atmospheric_pressure);

        /* Sets the expected I2C address of the sensor.
           The default value is 0x28
           
           ES Systems sell the sensors with factory-set addresses:
           0x28, 0x29, 0x2A and 0x2B
           
           Note that the v1.4 datasheet confusingly uses
           0x50 in the I2C example on page 11 - 0x50 is the eight-bit
           value seen when address 0x28 is combined with the I2C "write" bit
           to make an 8-bit value. */
        void set7bitAddress(unsigned char newaddress);

        /* These three all perform an I2C read and then return the result.
           Note that this is not quite the same as the BlueRobotics library*/

        /* returns pressure in bar, which is the raw value from the sensor*/
        float pressure();
        
        /* returns temperature in degrees Celcius*/
        float temperature();

        /* returns depth in metres, using 
            the value set using setFluidDensity
            the value set using setAtmosphericPressure */
        float depth();

    private:
        float fluidDensity;
        unsigned char i2cAddress;
        float atmosphericPressure;
};

#endif