#include <Arduino.h>
#include <WiFiManager.h>
WiFiManager wm;
#include "WebPage.h"

void showMainPage()
{
  wm.server->send(200, "text/html", MAIN_page);
}

void bindServerCallback()
{
  //  wm.server->on("/", handleSetupRoute);
  wm.server->on("/index.html", showMainPage);
}

void setupWM()
{
  WiFi.mode(WIFI_STA);
  Serial.begin(115200);
  wm.setConfigPortalBlocking(false);  
  wm.setWebServerCallback(bindServerCallback);
  if (wm.autoConnect("AutoConnectAP"))
  {
    Serial.println("[WM] connected...yeey :)");
  }
  else
  {
    Serial.println("[WM] Configportal running");
  }
}

void loopWM()
{
  wm.process();
  if (!wm.getWebPortalActive())
  {
    Serial.println("[WM] Web Portal restart");
    wm.startWebPortal();
  }
}

void setup()
{
  setupWM();
}

void loop()
{
  loopWM();
}
