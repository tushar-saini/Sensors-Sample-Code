/***************************************************************************************************************
 * Modified by  : Tushar Saini
 * Email Id : tsaini1285@gmail.com
 * Original Source: https://lastminuteengineers.com/bmp180-arduino-tutorial/
 * BMP180 sensor datasheet: https://cdn-shop.adafruit.com/datasheets/BST-BMP180-DS000-09.pdf 
***************************************************************************************************************/
#include <Wire.h>
#include <Adafruit_BMP085.h>
#define seaLevelPressure_hPa 1013.25

Adafruit_BMP085 bmp;
bool initsuccess = true;
  
void setup() {
  Serial.begin(9600);
  if (!bmp.begin()) {
    Serial.println("Could not find a valid BMP085 sensor, check wiring!");
    initsuccess = false;
  }
}
  
void loop() {
  if (initsuccess) 
    showData();
  delay(500);
}

void showData() {
  Serial.print("Temperature = ");
  Serial.print(bmp.readTemperature());
  Serial.println(" *C");
  
  Serial.print("Pressure = ");
  Serial.print(bmp.readPressure());
  Serial.println(" Pa");

  Serial.print("Altitude = ");
  Serial.print(bmp.readAltitude());
  Serial.println(" meters");

  Serial.print("Pressure at sealevel (calculated) = ");
  Serial.print(bmp.readSealevelPressure());
  Serial.println(" Pa");

  Serial.print("Real altitude = ");
  Serial.print(bmp.readAltitude(seaLevelPressure_hPa * 100));
  Serial.println(" meters");
  
  Serial.println();
}
