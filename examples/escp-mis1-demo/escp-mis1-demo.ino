#include "ESCP-MIS1.h"

ESCPMIS1 sensor;

void setup() {
  // put your setup code here, to run once:

  Serial.begin(19200);
  sensor.begin();
  sensor.setFluidDensity(997); // kg per cubic metre - 997 is the value for fresh water
  sensor.setAtmosphericPressure(1.000); // sets default atmospheric pressure (used for depth calculation) to 1 bar (= 1000 hPa)

}

void loop() {
  // put your main code here, to run repeatedly:

  Serial.print("Pressure: ");
  Serial.print(sensor.pressure());
  Serial.println(" bar");

  Serial.print("Temperature: ");
  Serial.print(sensor.temperature());
  Serial.println(" deg C");

  Serial.print("Depth below surface: ");
  Serial.print(sensor.depth());
  Serial.println(" metres");

  delay(5000);
}
