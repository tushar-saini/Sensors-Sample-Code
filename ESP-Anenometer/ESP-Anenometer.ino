/***************************************************************************************************************
* Made by  : Tushar Saini
* Email Id : tsaini1285@gmail.com
* For Argent's Weather Station Datasheet: https://www.argentdata.com/files/80422_datasheet.pdf
***************************************************************************************************************/

#include <SoftwareSerial.h>
#include "esp_attr.h"       // To store ISR on fast storage

/***************************** Wind Speed ******************************/
#define WIND_SPD_PIN 13 // Or other pins that support an interrupt

// Variables and constants used in calculating the windspeed.
volatile unsigned long timeSinceLastTick = 0;
volatile unsigned long lastTick = 0;
float windSpeed = 0.0;

// Interrupt for calculating when the las tick occurred.
void IRAM_ATTR windTick(void) {
  timeSinceLastTick = millis() - lastTick;
  lastTick = millis();
}

/***************************** Wind Direction ******************************/
#define WD_DIR 36

float winddirection;
String heading ="0";

void setup() {
  Serial.begin(9600);

  // Make sure input has software pull-up enabled
  // Or you can make harware pull-up.
  pinMode(WIND_SPD_PIN, INPUT_PULLUP);     
  attachInterrupt(digitalPinToInterrupt(WIND_SPD_PIN), windTick, RISING);
}

void loop() {
  getWindSpeed();
  getWindDirection();
}

void getWindSpeed() {
  // Calculate no of ticks in a second.
  if (timeSinceLastTick != 0)
    windSpeed = 1000.0/timeSinceLastTick;
  Serial.print("Windspeed: ");
  Serial.print(windSpeed*1.492);
  Serial.println(" mph");
}

void getWindDirection(){
  winddirection = 0;
  for (int i=0; i<1000; i++) {
   winddirection += analogRead(WD_DIR);
  }
  winddirection=int(winddirection/1000);

  if(winddirection>=350&&winddirection<500)
    heading="0";
  if(winddirection>=700&&winddirection<850)
    heading="45";
  if(winddirection>=1015)
    heading="90";
  if(winddirection>=980&&winddirection<1015)
    heading="135";
  if(winddirection>=850&&winddirection<980)
    heading="180";
  if(winddirection>=500&&winddirection<700)
    heading="225";
  if(winddirection<200)
    heading="270";
  if(winddirection>=200&&winddirection<350)
    heading="315";
  Serial.println("Heading: "+String(heading));
  delay(1000);
}
