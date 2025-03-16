#include <Arduino.h>
#include <WiFiManager.h> 
WiFiManager wm;
#include "WebPage.h"

void handleSetupRoute()
{  
  wm.server->send(200, "text/html", MAIN_page);      
}   

void bindServerCallback()
{
//  wm.server->on("/", handleSetupRoute); 
  wm.server->on("/index.html", handleSetupRoute);
}
void setup()
{
  WiFi.mode(WIFI_STA); 
  Serial.begin(115200);
  wm.setConfigPortalBlocking(false);
  // wm.setConfigPortalTimeout(60);
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
void loop()
{  
  wm.process();
  if (!wm.getWebPortalActive())
  {
    Serial.println("[WM] Web Portal restart");
    wm.startWebPortal();    
  }


}
