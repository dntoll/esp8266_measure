/**
 * BasicHTTPClient.ino
 *
 *  Created on: 24.05.2015
 *
 */

#include <Arduino.h>

#include <ESP8266WiFi.h>
#include <ESP8266WiFiMulti.h>

#include <ESP8266HTTPClient.h>

ESP8266WiFiMulti WiFiMulti;

const int photoTransistorPin = 2;
int lastState = HIGH;
unsigned long timeForLastState = -1;

bool states[100];
int times[100];

void setup() {

    Serial.begin(115200);
    Serial.println("Starting up...");
    WiFiMulti.addAP("...", "...");

    pinMode(photoTransistorPin, INPUT);
    
    lastState = digitalRead(photoTransistorPin);
    timeForLastState = millis();

    Serial.println("done setup...");
}

void checkServer(bool state, unsigned long elapsedTime) {
  // wait for WiFi connection
    if((WiFiMulti.run() == WL_CONNECTED)) {
        String stateStr = state ? "high" : "low";
        // turn LED on:
        Serial.println(stateStr + ":" + elapsedTime);

        String url = "/log/?state=";
        url = url + stateStr + "&time=" + elapsedTime;

        
        HTTPClient http;

        Serial.print("[HTTP] begin...\n");
        Serial.print(url + "\n");
        http.begin("www.familjentoll.se", 80, url); //HTTP

        Serial.print("[HTTP] GET...\n");
        // start connection and send HTTP header
        int httpCode = http.GET();
        if(httpCode) {
            // HTTP header has been send and Server response header has been handled
            Serial.printf("[HTTP] GET... code: %d\n", httpCode);

            // file found at server
            if(httpCode == 200) {
                String payload = http.getString();
                Serial.println(payload);
            }
        } else {
            Serial.print("[HTTP] GET... failed, no connection or no HTTP server\n");
        }
    } else {
            Serial.print("[HTTP] GET... failed, no connection or no HTTP server\n");
        }
}

void loop() {
    int buttonState = 0; 
    buttonState = digitalRead(photoTransistorPin);

    if (buttonState != lastState) {
      Serial.println("swapp state.");
      unsigned long now = millis();
      checkServer(lastState, now - timeForLastState);

      lastState = buttonState;
      timeForLastState = now;
      Serial.println("Done swapped state.");
    }
    
  
    delay(50);

    
}

