/***************************************************************************************************************
* Made by  : Tushar Saini
* Email Id : tsaini1285@gmail.com
* For DFRobo-PM sensor Datasheet: https://wiki.dfrobot.com/PM2.5_laser_dust_sensor_SKU_SEN0177
***************************************************************************************************************/
#include <Arduino.h>
#define LENG 31   // 0x42 + 31 bytes equal to 32 bytes
unsigned char buf[LENG];

int PM01Value = 0;
int PM2_5Value = 0;
int PM10Value = 0;

void setup() {
  Serial.begin(9600);   //use serial0
  Serial.println("Setting up....");
  delay(1500);
}

void loop() {
  if(Serial.find(0x42)){    // Detect first byte.
    Serial.readBytes(buf,LENG);

    if(buf[0] == 0x4d){
      if(checkValue(buf,LENG)){
        PM01Value = transmitPM01(buf);    // Count PM1.0 value of the air detector module
        PM2_5Value = transmitPM2_5(buf);  // Count PM2.5 value of the air detector module
        PM10Value = transmitPM10(buf);    // Count PM10 value of the air detector module
      }
    }
  }

  static unsigned long OledTimer = millis();
  if (millis() - OledTimer >= 1000) {
    OledTimer=millis();
    
    Serial.print("PM1.0: "); Serial.print(PM01Value); Serial.println("  ug/m3");

    Serial.print("PM2.5: "); Serial.print(PM2_5Value); Serial.println("  ug/m3");

    Serial.print("PM1 0: "); Serial.print(PM10Value); Serial.println("  ug/m3");
    Serial.println);
  }
}

char checkValue(unsigned char *thebuf, char leng) {
  char receiveflag=0;
  int receiveSum=0;

  for(int i=0; i<(leng-2); i++){
    receiveSum=receiveSum+thebuf[i];
  }
  receiveSum=receiveSum + 0x42;

  if(receiveSum == ((thebuf[leng-2]<<8)+thebuf[leng-1])) {  // Check the serial data
    receiveSum = 0;
    receiveflag = 1;
  }
  return receiveflag;
}

int transmitPM01(unsigned char *thebuf) {
  int PM01Val;
  PM01Val=((thebuf[3]<<8) + thebuf[4]); //count PM1.0 value of the air detector module
  return PM01Val;
}

int transmitPM2_5(unsigned char *thebuf) {
  int PM2_5Val;
  PM2_5Val=((thebuf[5]<<8) + thebuf[6]);//count PM2.5 value of the air detector module
  return PM2_5Val;
}

int transmitPM10(unsigned char *thebuf) {
  int PM10Val;
  PM10Val=((thebuf[7]<<8) + thebuf[8]); //count PM10 value of the air detector module
  return PM10Val;
}
