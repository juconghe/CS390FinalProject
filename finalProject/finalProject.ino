#include <WiFiEsp.h>
#include <WiFiEspClient.h>
#include <PubSubClient.h>
#include <Adafruit_GFX.h>   // Core graphics library
#include <RGBmatrixPanel.h> // Hardware-specific library
#include <TimeLib.h>
#include "NTP.h"
#include <ArduinoJson.h>
#include <string.h>

#define ADAFRUIT_USERNAME  "Jucong"
#define AIO_KEY  "01a85723468e409bb15488a77efe724c"
//#define TEMP_PATH ADAFRUIT_USERNAME "/feeds/temp"
#define PUB_FEED_PATH ADAFRUIT_USERNAME "/feeds/publish"
//#define CAL_PATH ADAFRUIT_USERNAME "/feeds/calendar"
//#define MUSIC_PATH ADAFRUIT_USERNAME "feeds/music"

#define CLK 11  // MUST be on PORTB! (Use pin 11 on Mega)
#define LAT A3
#define OE  9
#define A   A0
#define B   A1
#define C   A2

#define HOME "0"
#define SUNNY 1
#define RAIN 2
#define CLOUD 3
#define CAL "4"
#define MUSIC "5"
#define TEMP "6"
#define WEATHER "7"

int WEATHER_MODE = SUNNY;
const char* ssid = "AHHA Lab Wifi";
const char* password =  "ramanujan";
int status = WL_IDLE_STATUS; // the Wifi radio's status
RGBmatrixPanel matrix(A, B, C, CLK, LAT, OE, true);
bool on = true;
String mode = HOME;
int    textX   = matrix.width(),
       textMin;
String temperature = "0";

void callback(char* topic, byte* payload, unsigned int length) {
  char s[length + 1];
  for (int i = 0; i < length; i++) {
    s[i] = (char) payload[i];
  }
  s[length] = '\0';

  Serial.println("=====");
  String temp = String(s);
  String first_letter = String(temp[0]);
  String content = temp.substring(1);
  Serial.println(s);
    if (first_letter.equals(HOME)) {
       mode = HOME;
    } else if (first_letter.equals(CAL)) {
      mode = CAL;
      //schedule = String(s);
    } else if (first_letter.equals(TEMP)) {
      mode = TEMP;
      temperature = content;
    }else if (first_letter.equals(WEATHER)){
      mode = TEMP;
      WEATHER_MODE = content.toInt();
    } else if (first_letter.equals(MUSIC)) {
      mode = MUSIC;
    }
 }



WiFiEspClient espClient; 
PubSubClient client("io.adafruit.com", 1883, callback, espClient);

void reconnect() {
  while (!client.connected()) {
    Serial.println(F("Connecting to MQTT..."));
    if (client.connect("MEGA", ADAFRUIT_USERNAME, AIO_KEY )) {
      client.subscribe(PUB_FEED_PATH, 1);
      Serial.println(F("Connected"));
    } else {
      Serial.print(F("failed with state "));
      Serial.print(client.state());
      delay(2000);
    }
  }
}

void pm() {
  //      //M
  matrix.drawPixel(28, 4, matrix.Color333(9,9,9));
  matrix.drawPixel(28, 5, matrix.Color333(9,9,9));
  matrix.drawPixel(28, 6, matrix.Color333(9,9,9));
  matrix.drawPixel(28, 7, matrix.Color333(9,9,9));
  matrix.drawPixel(29, 5, matrix.Color333(9,9,9));
  matrix.drawPixel(30, 5, matrix.Color333(9,9,9));
  matrix.drawPixel(31, 4, matrix.Color333(9,9,9));
  matrix.drawPixel(31, 5, matrix.Color333(9,9,9));
  matrix.drawPixel(31, 6, matrix.Color333(9,9,9));
  matrix.drawPixel(31, 7, matrix.Color333(9,9,9));

  //P
  matrix.drawPixel(24, 4, matrix.Color333(9,9,9));
  matrix.drawPixel(24, 5, matrix.Color333(9,9,9));
  matrix.drawPixel(24, 6, matrix.Color333(9,9,9));
  matrix.drawPixel(24, 7, matrix.Color333(9,9,9));
  matrix.drawPixel(25, 4, matrix.Color333(9,9,9));
  matrix.drawPixel(26, 4, matrix.Color333(9,9,9));
  matrix.drawPixel(26, 5, matrix.Color333(9,9,9));
  matrix.drawPixel(26, 6, matrix.Color333(9,9,9));
  matrix.drawPixel(25, 6, matrix.Color333(9,9,9));
  //A
  //matrix.drawPixel(6, 8, matrix.Color333(9,9,9));
  // Drawing double column sign



}

void am() {
  //M
  pm();
  //A
  matrix.drawPixel(26, 7, matrix.Color333(9,9,9));
}

void drawSun() {
  //matrix.drawCircle(7, 7, 7, matrix.Color333(0, 0, 7));
  matrix.fillCircle(8, 7, 2, matrix.Color333(7, 4, 0));
  matrix.drawPixel(8, 3, matrix.Color333(7, 4, 0));
  matrix.drawPixel(5, 5, matrix.Color333(7, 4, 0));
  matrix.drawPixel(11, 5, matrix.Color333(7, 4, 0));
  matrix.drawPixel(4, 7, matrix.Color333(7, 4, 0));
  matrix.drawPixel(12, 7, matrix.Color333(7, 4, 0));
  matrix.drawPixel(5, 10, matrix.Color333(7, 4, 0));
  matrix.drawPixel(11, 10, matrix.Color333(7, 4, 0));
  matrix.drawPixel(8, 11, matrix.Color333(7, 4, 0));
}


void drawCloud() {
  //matrix.drawCircle(7, 7, 7, matrix.Color333(0, 0, 7));
  matrix.drawPixel(9, 4, matrix.Color333(0,4,7));
  matrix.drawPixel(10, 4, matrix.Color333(0,4,7));
  matrix.drawPixel(11, 4, matrix.Color333(0,4,7));
  matrix.drawPixel(8, 5, matrix.Color333(0,4,7));
  matrix.drawPixel(12, 5, matrix.Color333(0,4,7));
  matrix.drawPixel(6, 6, matrix.Color333(0,4,7));
  matrix.drawPixel(7, 6, matrix.Color333(0,4,7));
  matrix.drawPixel(13, 6, matrix.Color333(0,4,7));
  matrix.drawPixel(5, 7, matrix.Color333(0,4,7));
  matrix.drawPixel(8, 7, matrix.Color333(0,4,7));
  matrix.drawPixel(13, 7, matrix.Color333(0,4,7));
  matrix.drawPixel(14, 7, matrix.Color333(0,4,7));
  matrix.drawPixel(5, 8, matrix.Color333(0,4,7));
  matrix.drawPixel(9, 8, matrix.Color333(0,4,7));
  matrix.drawPixel(13, 6, matrix.Color333(0,4,7));
  matrix.drawPixel(13, 6, matrix.Color333(0,4,7));
  matrix.drawPixel(13, 6, matrix.Color333(0,4,7));
  matrix.drawPixel(13, 6, matrix.Color333(0,4,7));
  matrix.drawPixel(13, 6, matrix.Color333(0,4,7));
  matrix.drawPixel(13, 6, matrix.Color333(0,4,7));
  matrix.drawLine(13, 8, 15, 8, matrix.Color333(0,4,7));
  matrix.drawLine(4, 9, 4, 10, matrix.Color333(0,4,7));
  matrix.drawLine(17, 9, 17, 10, matrix.Color333(0,4,7));
  matrix.drawLine(5, 11, 15, 11, matrix.Color333(0,4,7));
}


void drawRain() {
  //matrix.drawCircle(7, 7, 7, matrix.Color333(0, 0, 7));
  matrix.drawLine(7, 4, 9, 4, matrix.Color333(0,4,7));
  matrix.drawLine(6, 5, 10, 5, matrix.Color333(0,4,7));
  matrix.drawPixel(5, 6, matrix.Color333(0,4,7));
  matrix.drawPixel(7, 6, matrix.Color333(0,4,7));
  matrix.drawPixel(9, 6, matrix.Color333(0,4,7));
  matrix.drawPixel(11, 6, matrix.Color333(0,4,7));
  matrix.drawLine(4, 7, 12, 7, matrix.Color333(0,4,7));
  matrix.drawPixel(5, 8, matrix.Color333(0,4,7));
  matrix.drawPixel(7, 8, matrix.Color333(0,4,7));
  matrix.drawPixel(9, 8, matrix.Color333(0,4,7));
  matrix.drawPixel(11, 8, matrix.Color333(0,4,7));
  matrix.drawPixel(6, 9, matrix.Color333(0,4,7));
  matrix.drawPixel(8, 9, matrix.Color333(0,4,7));
  matrix.drawPixel(10, 9, matrix.Color333(0,4,7));
  matrix.drawPixel(6, 11, matrix.Color333(0,4,7));
  matrix.drawPixel(8, 11, matrix.Color333(0,4,7));
  matrix.drawPixel(10, 11, matrix.Color333(0,4,7));
  
}



void drawClock() {
  matrix.setCursor(0, 4);   // start at top left, with one pixel of spacing
  matrix.setTextColor(matrix.Color333(9,9,9));
  int temp;
  if (hour() == 12) {
    matrix.print("12");
    pm();
    temp = 12;
  } else if (hour() == 0) {
    matrix.print("12");
    temp = 12;
    am();
  } else if (hour() < 12) {
    am();
    matrix.print(hour());
    temp = hour();
  } else {
    matrix.print(hour() % 12);
    temp = hour() % 12;
    pm();
  }
  //  matrix.print(":");
  if (minute() < 10) {
    matrix.print("0");
    matrix.print(minute());
  } else {
    matrix.print(minute());
  }

  if (on) {
    if (temp >= 10) {
       matrix.drawPixel(11, 5, matrix.Color333(9, 9, 9));
       matrix.drawPixel(11, 8, matrix.Color333(9, 9, 9));
    } else {
       matrix.drawPixel(5, 5, matrix.Color333(9, 9, 9));
       matrix.drawPixel(5, 8, matrix.Color333(9, 9, 9));
    }
  }
  on = !on;
}

void drawCalendar() {
  matrix.setTextSize(2);
  matrix.setTextWrap(false); // Allow text to run off right edge
  matrix.setTextColor(matrix.Color333(1,0,0));
  matrix.setCursor(textX, 1);
  matrix.print("Toyota payment 9:00AM-10:00AM CS589 10:00AM-11:15AM CS514 11:30AM-12:45PM  CS373 2:30PM-3:45PM CS390N 4:00PM-5:15PM");
  textMin = sizeof("Toyota payment 9:00AM-10:00AM CS589 10:00AM-11:15AM CS514 11:30AM-12:45PM  CS373 2:30PM-3:45PM CS390N 4:00PM-5:15PM") * -6;
  if((textX -= 6) < textMin) textX = matrix.width();
}

void drawTemp(){
     if(temperature.length() == 1){
        matrix.setCursor(20, 5);
      }else{
        matrix.setCursor(16, 5);
        }
     
     matrix.print(temperature);
     matrix.drawLine(28, 8, 31, 8, matrix.Color333(9,9,9));
     matrix.drawLine(28, 11, 31, 11, matrix.Color333(9,9,9));
     matrix.drawLine(28, 9, 28, 10, matrix.Color333(9,9,9));
};

void drawMusic(){
    matrix.drawLine(21, 9, 28, 9, matrix.Color333(0,4,0));
    matrix.drawLine(21, 10, 21, 14, matrix.Color333(0,4,0));
    matrix.drawLine(28, 10, 28, 14, matrix.Color333(0,4,0));
    matrix.drawLine(19, 15, 21, 15, matrix.Color333(0,4,0));
    matrix.drawLine(26, 15, 28, 15, matrix.Color333(0,4,0));

  }

void drawWeather(){
  
  if(WEATHER_MODE == RAIN){
      drawRain();
    }else if (WEATHER_MODE == CLOUD){
      drawCloud();
    }else{
      drawSun();
    }
}

  
void setup() {

  Serial.begin(115200);
  // initialize serial for ESP module
  Serial2.begin(9600);

  // initialize ESP module
  WiFi.init(&Serial2);
  WiFi.begin(ssid, password);

  // Attempt to connect to WiFi network
  while ( status != WL_CONNECTED) {
    Serial.print("Attempting to connect to WPA SSID: ");
    Serial.println(ssid);
    // Connect to WPA/WPA2 network
    status = WiFi.begin(ssid, password);
  }
  Serial.println(F("Connected to the WiFi network"));
  
  // Syncing Time 
  Udp.begin(localPort);
  time_t syncTime = getNtpTime();
  while (syncTime == 0) {
    Serial.println(F("Sycning time"));
    syncTime = getNtpTime();
    delay(1000);
  }
  setTime(syncTime);

  // Start displaying RGB Panel
  matrix.begin();
  matrix.setTextSize(1);

}








void loop() {

  if (!client.connected()) {
    reconnect();
  }
  matrix.fillScreen(0);
  if (mode == HOME) {
    matrix.setTextSize(1);
     textX   = matrix.width(),
    drawClock();
   // drawTemp();
   // drawWeather();
  } else if (mode == CAL){
    drawCalendar();
  } else if (mode == TEMP){
    matrix.setTextSize(1);
     textX   = matrix.width(),
    drawTemp();
    drawWeather();
  } else if (mode == MUSIC) {
    matrix.setTextSize(1);
    textX   = matrix.width(),
    drawClock();
    drawMusic();
  }
  matrix.swapBuffers(false);
  delay(200);
  client.loop();

}
