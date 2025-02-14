#include "OV2640.h"
#include <WiFi.h>
#include <WebServer.h>
#include <WiFiClient.h>

#include "SimStreamer.h"
#include "OV2640Streamer.h"
#include "CRtspSession.h"

OV2640 cam;
WiFiServer rtspServer(8554);

unsigned long lastimage;
int msecPerFrame = 1000;

void setup() {
  Serial.begin(115200);
  while (!Serial) {;}
  cam.init(esp32cam_aithinker_config);
  lastimage = millis();

  IPAddress ip;
  WiFi.mode(WIFI_STA);
  WiFi.begin("SSID", "PASS");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(F("."));
  }
  ip = WiFi.localIP();
  Serial.println(F("WiFi connected"));
  Serial.println("");
  Serial.println(ip);
  rtspServer.begin();
}

CStreamer *streamer;
CRtspSession *session;
WiFiClient client;

void loop() {
  if (session) {
    if (millis() > lastimage + msecPerFrame) {
      session->handleRequests(0);

      session->broadcastCurrentFrame(millis());
      Serial.println("Delta time: " + (String)(millis() - lastimage));

      lastimage = millis();
    }

    if (session->m_stopped) {
      delete session;
      delete streamer;
      session = NULL;
      streamer = NULL;
    }
  } else {
    client = rtspServer.accept();
    if (client) {
      streamer = new OV2640Streamer(&client, cam);
      session = new CRtspSession(&client, streamer);
    }
  }
}
