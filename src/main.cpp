#include <Arduino.h>
#include <ElegantOTA.h>
unsigned long ota_progress_millis = 0;

#include <WiFiManager.h> // https://github.com/tzapu/WiFiManager
WiFiManager wm;
#include "WebPage.h"
ESP8266WebServer otaServer(8080);
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
  if (success)
  {
    Serial.println("OTA update finished successfully!");
  }
  else
  {
    Serial.println("There was an error during OTA update!");
  }
}

void handleSetupRoute()
{
  // Replace <your_esp_ip> with the actual IP address of the ESP8266
  String page = FPSTR(MAIN_page);                           // Copy HTML from Flash memory to RAM
  page.replace("<your_esp_ip>", WiFi.localIP().toString()); // Replace the IP placeholder
  wm.server->send(200, "text/html", page);                  // Send modified page to client
}

void bindServerCallback()
{
  wm.server->on("/", handleSetupRoute); // overwrite/replace existing/default route
}
void setup()
{
  WiFi.mode(WIFI_STA); // explicitly set mode, esp defaults to STA+AP
  // put your setup code here, to run once:
  Serial.begin(115200);
  wm.setConfigPortalBlocking(false);
  // wm.setConfigPortalTimeout(60);
  wm.setWebServerCallback(bindServerCallback);
  // automatically connect using saved credentials if they exist
  // If connection fails it starts an access point with the specified name
  if (wm.autoConnect("AutoConnectAP"))
  {
    Serial.println("connected...yeey :)");
  }
  else
  {
    Serial.println("Configportal running");
  }

  ElegantOTA.begin(&otaServer);
  ElegantOTA.onStart(onOTAStart);
  ElegantOTA.onProgress(onOTAProgress);
  ElegantOTA.onEnd(onOTAEnd);
  otaServer.begin();
}
bool portalRunning = false;

void loop()
{
  otaServer.handleClient();
  ElegantOTA.loop();
  wm.process();
  if (!portalRunning)
  {
    Serial.println("Button Pressed, Starting Portal");
    wm.startWebPortal();
    portalRunning = true;
  }
  // put your main code here, to run repeatedly:
}
