/*  Created by : Tushar Saini
 *  Email ID   : tsaini1285@gmail.com
 *  About      : ESP8266 code, to make HTTPS GET request.
 */
#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>

// Credentials for running ESP in AP mode.
const char* ssid = "SSID";
const char* pass = "WIFI_PASSWORD";

// Fingerprint for demo URL, expires on June 2, 2019, needs to be updated well before this date
const uint8_t fingerprint[20] = {0x5A, 0xCF, 0xFE, 0xF0, 0xF1, 0xA6, 0xF4, 0x5F, 0xD2, 0x11, 0x11, 0xC6, 0x1D, 0x2F, 0x0E, 0xBC, 0x39, 0x8D, 0x50, 0xE0};

void connectToWifi() {
  WiFi.begin(ssid, pass);
  Serial.print("Connecting to " + String(ssid));

  int i = 0;
  int trial = 15;
  while (WiFi.status() != WL_CONNECTED && i < trial) { // Wait for the Wi-Fi to connect
    delay(1000);
    Serial.print('.');
    i++;
  }
  Serial.println("");

  if (WiFi.status() != WL_CONNECTED) {
    Serial.println(String(ssid) + " is not available.");
  } else {
    Serial.println("Connection established!");  
    Serial.print("IP address:\t");
    Serial.println(WiFi.localIP());
  }
}

void setup() {
  Serial.begin(9600);
  Serial.println("Setting up.....");
  connectToWifi();
}

void loop() {
  bool Certi = false; // Set true to use fingerprint, false to use insecure connection.
  String https_url = "https://www.google.com";

  if(WiFi.status()== WL_CONNECTED){
    std::unique_ptr<BearSSL::WiFiClientSecure>client(new BearSSL::WiFiClientSecure);

    if (Certi == true) 
      client->setFingerprint(fingerprint);
    else
      client->setInsecure();  // Set 

    HTTPClient https;

    Serial.print("[HTTPS] begin...\n");
    if (https.begin(*client, https_url)) {  // HTTPS

      Serial.print("[HTTPS] GET...\n");
      // start connection and send HTTP header
      int httpCode = https.GET();

      // httpCode will be negative on error
      if (httpCode > 0) {
        // HTTP header has been send and Server response header has been handled
        Serial.printf("[HTTPS] GET... code: %d\n", httpCode);

        // file found at server
        if (httpCode == HTTP_CODE_OK || httpCode == HTTP_CODE_MOVED_PERMANENTLY) {
          String payload = https.getString();
          Serial.println(payload);
        }
      } else {
        Serial.printf("[HTTPS] GET... failed, error: %s\n", https.errorToString(httpCode).c_str());
      }

      https.end();
    } else {
      Serial.printf("[HTTPS] Unable to connect\n");
    }
  } else {
    Serial.println("WiFi Disconnected");
  }
}
