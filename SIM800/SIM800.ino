/***************************************************************************************************************
* Made by  : Tushar Saini
* Email Id : tsaini1285@gmail.com
* For AT Commands, reference: https://www.elecrow.com/wiki/images/2/20/SIM800_Series_AT_Command_Manual_V1.09.pdf
* For SSL Application: https://simcom.ee/documents/SIM800x/SIM800%20Series_SSL_Application%20Note_V1.02.pdf
***************************************************************************************************************/

#include <SoftwareSerial.h>
SoftwareSerial myGsm(10, 11);

void setup() {
  Serial.begin(9600);
  myGsm.begin(9600);  
  myGsm.println(F("Setting up....."));
}

void loop() {
  delay(2000);
  myGsm.println(F("AT+CFUN=1"));  // Set phone functionality to full functionality.
  delay(4000); GsmResponse();
  
  myGsm.println(F("AT+CGATT?"));  // Attach GPRS
  delay(2000); GsmResponse();
  
  myGsm.println(F("AT+SAPBR=3,1,\"CONTYPE\",\"GPRS\""));  // Activate Bearer profile.
  delay(2000); GsmResponse();
  
  myGsm.println(F("AT+SAPBR=3,1,\"APN\",\"airtelgprs.com\""));  // Set APN of network, here we are using Airtel sim.
  delay(2000); GsmResponse();
  
  myGsm.println(F("AT+SAPBR=1,1"));
  delay(2000); GsmResponse();
  
  myGsm.println(F("AT+SAPBR=2,1")); // Shows IP
  delay(2000); GsmResponse();

  myGsm.println("AT+HTTPINIT"); // Initialize  HTTP  Service
  delay(2000);
  
  myGsm.println(F("AT+HTTPPARA=\"URL\",\"https://google.com\"")); // Set parameters for HTTP session
  delay(2000); GsmResponse(); 

  myGsm.println(F("AT+HTTPSSL=1")); // Enable HTTPS function
  delay(2000); GsmResponse();

  myGsm.println(F("AT+HTTPACTION=0"));  // GET session start
  delay(2000); GsmResponse();
  
  myGsm.println(F("AT+HTTPREAD"));  // Read the data of HTTP server
  delay(5000); GsmResponse();

  myGsm.println(F("AT+HTTPTERM"));  // Terminate HTTP service
  delay(5000); GsmResponse();
}

void GsmResponse() {
  String inData = "";
  while (myGsm.available() > 0) {
    inData = myGsm.readString();
    Serial.println(inData);
    Serial.println(F("***"));
  }
}
