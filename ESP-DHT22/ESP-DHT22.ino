/***************************************************************************************************************
* Made by  : Tushar Saini
* Email Id : tsaini1285@gmail.com
* For DHT22 Datasheet: https://www.sparkfun.com/datasheets/Sensors/Temperature/DHT22.pdf
***************************************************************************************************************/
#include <DHT.h>
#define DHTPIN 33
#define DHTTYPE DHT22 

DHT dht(DHTPIN, DHTTYPE);

float tempc;
float dewpoint;
float humidity;

void setup() {
  Serial.begin(9600);
  dht.begin();
}

void loop() {
  humidity = dht.readHumidity();
  tempc = dht.readTemperature();
  
  if (isnan(humidity) || isnan(tempc)) {
    Serial.println(F("Failed to read from DHT sensor!"));
    tempc=0.0,humidity=0.0; dewpoint=0.0;
  } else {
    dewpoint = calDewpoint(humidity, tempc);
  
    Serial.print("Humidity: ");  Serial.println(humidity);
    Serial.print("Temperature (C): ");  Serial.println(tempc);
    Serial.print("Dewpoint: ");  Serial.println(dewpoint);
  }
  delay(1000);
}

float calDewpoint(float hum, float temp) {
  float Tda;
  Tda = log(hum/100) + (17.62 * temp) / (243.12 + temp);
  return 243.12 * Tda / (17.62 - Tda);
}
