/***************************************************************************************************************
* Made by  : Tushar Saini
* Email Id : tsaini1285@gmail.com
* For CJMU-4514 Datasheet: https://www.sgxsensortech.com/content/uploads/2014/08/0278_Datasheet-MiCS-4514-rev-16.pdf
***************************************************************************************************************/
#include <SoftwareSerial.h>
#include <Wire.h>

#define ANALOG_NO2        A1   // Arduino analog pin
#define ANALOG_CO         A0   // Arduino analog pin
#define PIN_HEATING_NO2   8    // Arduino digital pin

#define PRE_HEAT_SECONDS 10    // Arduino digital pin

#define CALIB_R0_NO2      2200      // R0 calibration value for the NO2 sensor
#define CALIB_R0_CO       750000    // R0 calibration value for the CO sensor

double readNO2;
double readCO;
float s=0;

void setup() {
  Serial.begin(9600);
  Serial.println(F("Setting up..."));
  Wire.begin(); 
  delay(1000);
}

void loop() {
  MiCS();
  Serial.print("CO: ");  Serial.println(readCO);
  Serial.print("NO2: "); Serial.println(readNO2);
  delay(5000);
}

void initSensor(void) {
  Serial.print("Preheating NOx...");
  pinMode(PIN_HEATING_NO2, OUTPUT);
  
  digitalWrite(PIN_HEATING_NO2, HIGH);
  delay(PRE_HEAT_SECONDS * 1000);
  digitalWrite(PIN_HEATING_NO2, LOW);
}

int MiCS(void) {
  initSensor();
  unsigned long calib;
  float fVolt, fRes, fConc;

  // Read CO and convert into mg/m3.
  readCO = analogRead(ANALOG_CO);
  fVolt = (readCO * 3.3) / 1024.0;
  // Get Rs/R0 value
  calib = CALIB_R0_CO;
  fRes = (5000.0/fVolt - 1000) / calib;

  // Convert to ppm
  if (fRes > 0.7)
    fRes = 0.7;
  if (fRes > 0.6)
    fConc = (0.711 - fRes) / 0.011;
  else if (fRes > 0.3)
    fConc = (0.7 - fRes) / 0.01;
  else
    fConc = (0.3233 - fRes) / 0.00058;
  
  readCO = ((fConc/1000)*(28/24.5)); // Convert to mg/m3

  
  // Read NO2 and convert into ug/m3.
  readNO2 = analogRead(ANALOG_NO2);
  fVolt = 3.3;
  fVolt *= readNO2;
  fVolt /= 1024.0;

  // Get Rs/R0 value
  calib = CALIB_R0_NO2; 
  fRes = (5000.0/fVolt - 1000) / calib;

  // Convert to ppm
  if (fRes < 3.0)
    fRes = 3.0;
  if (fRes >= 3.0 && fRes < 8.0)
    fConc = (fRes - 0.5) / 0.25;
  else
    fConc = (fRes + 129.655) / 4.589;
  
  readNO2 = ((fConc)*(46/24.5)); // Convert to ug/m3
}
