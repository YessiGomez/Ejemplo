#include <Arduino.h>
#include <WiFi.h>
#include <HTTPClient.h>
#include <ArduinoJson.h>

class conexionWeb{
  private:

  public:
    conexionWeb(const char *_SSID, const char* _PASSWORD ){
      WiFi.begin(_SSID, _PASSWORD);
      while(WiFi.status()!= WL_CONNECTED){
          delay(500);
          Serial.print("...");
      }
    }

}; 

class DateTime
{
private:
  int defaultTime;
  struct tm timeinfo;
  const char *ntpServer = "pool.ntp.org";
  const long gmtOffset_sec = 0;
  const int daylightOffset_sec = 0;

public:
  char timeStringBuff[20];
  DateTime()
  {
    defaultTime = 0;
    configTime(gmtOffset_sec, daylightOffset_sec, ntpServer);
    getTime();
  }

  void getTime()
  {   
    setLocalTime();
  }

  void setLocalTime()
  {
    
    if (!getLocalTime(&timeinfo))
    {
    }
    strftime(timeStringBuff, sizeof(timeStringBuff), "%Y-%m-%dT%H:%M:%SZ", &timeinfo);
  }
};
conexionWeb *webInterface;
DateTime *reloj;
StaticJsonDocument<512> horaActual;


const char *ssid="INFINITUM8007_2.4";
const char *passwrd="dL7qPVxkBX";


void setup() {
  Serial.begin(115200);
  webInterface= new conexionWeb(ssid,passwrd);
  reloj=new DateTime();
  
}
int s=0;
void loop() {
  s++;
  horaAct.clear();
  reloj->getTime();
  horaAct["hora"]=reloj->timeStringBuff;
  horaAct["Sumatoria"]=s;
  serializeJson(horaAct,Serial);
  Serial.println("__");
  delay(1000);
}

