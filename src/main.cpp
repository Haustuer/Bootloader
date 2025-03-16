#include <Arduino.h>
#include <ElegantOTA.h>
unsigned long ota_progress_millis = 0;
ESP8266WebServer server(80);

#include <WiFiManager.h> // https://github.com/tzapu/WiFiManager
WiFiManager wm;
#include "WebPage.h"
// OTA
void onOTAStart()
{
  Serial.println("OTA update started!");
}

void onOTAProgress(size_t current, size_t final)
{
  // Log every 1 second
  if (millis() - ota_progress_millis > 1000)
  {
    ota_progress_millis = millis();
    Serial.printf("OTA Progress Current: %u bytes, Final: %u bytes\n", current, final);
  }
}

void onOTAEnd(bool success)
{
  // Log when OTA has finished
  if (success)  {Serial.println("OTA update finished successfully!"); }
  else {   Serial.println("There was an error during OTA update!");  } 
}

void setup() {
  Serial.begin(115200);
  bool res;
  res = wm.autoConnect("AutoConnectAP"); // anonymous ap
  if(!res) {
      Serial.println("Failed to connect");     
  } 
  else {   
      Serial.println("connected...yeey :)");
  }
  Serial.println();
  Serial.println("Connected to the network");
  Serial.println(WiFi.localIP());
  ElegantOTA.begin(&server); 
  ElegantOTA.onStart(onOTAStart);
  ElegantOTA.onProgress(onOTAProgress);
  ElegantOTA.onEnd(onOTAEnd);

  server.on("/", []()
  { server.send(200, "text/html", MAIN_page); });
  server.begin();
}

void loop() {
    // OTA Loop
    server.handleClient();
    ElegantOTA.loop();
}
