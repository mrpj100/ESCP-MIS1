# ESCP-MIS1
Arduino library for communicating with ES Systems ESCP-MIS1 pressure sensor

The pressure sensor is available from [ES Systems](https://esenssys.com/product/escp-mis1/). This library is for the I2C variant (the sensor is also available with a SPI interface, but that's not supported here).

It has been tested on an [Adafruit Feather M0 Adalogger](https://www.adafruit.com/product/2796).

# Wiring instructions
* Feather GND -> sensor pin 6
* Feather 3V -> sensor pin 5
* Feather SDA -> sensor pin 2
* Feather SCL -> sensor pin 3
* Leave sensor pins 1 and 4 unconnected
* You also need to provide two 4.7k pull-up resistors: between SDA and 3.3V and between SCL and 3.3V.