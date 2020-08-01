/***************************************************************************************************************
* Made by  : Tushar Saini
* Email Id : tsaini1285@gmail.com
* For ZE-27 Datasheet: https://www.winsen-sensor.com/d/files/ZE27-O3.pdf
***************************************************************************************************************/
#include <SoftwareSerial.h>
SoftwareSerial o3sensor(10, 11);

void setup() {
	Serial.begin(9600);
	o3sensor.begin(9600);
  
  Serial.println("Setting up...");
  byte setConfig[] = {0xFF, 0x01, 0x78, 0x40, 0x00, 0x00, 0x00, 0x00, 0x47};  // Set to active mode.
  o3sensor.write(setConfig,sizeof(setConfig));
}
void loop() {
  byte measure[8];
  if(o3sensor.available() > 0) {
    byte measure[8];
    o3sensor.readBytes(measure,9);
    
    if (measure[0] == 255) {
      double ppm = double(measure[2] * 256 + measure[3]) / 1000;
      
      Serial.print("O3 concentration (ppm): ");
      Serial.println(ppm);
    }
  }
  delay(5000);
}
