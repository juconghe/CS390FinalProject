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
#define SLIDER_PATH ADAFRUIT_USERNAME "/feeds/slider"
#define PUB_FEED_PATH ADAFRUIT_USERNAME "/feeds/publish"

#define CLK 11  // MUST be on PORTB! (Use pin 11 on Mega)
#define LAT A3
#define OE  9
#define A   A0
#define B   A1
#define C   A2

#define HOME "0"
#define SUNNY "1"
#define RAIN "2"
#define CLOUD "3"
#define CAL "4"


const char* ssid = "CS390N";
const char* password =  "internetofthings";
int status = WL_IDLE_STATUS; // the Wifi radio's status
RGBmatrixPanel matrix(A, B, C, CLK, LAT, OE, true);
bool on = true;
String mode = HOME;
int    textX   = matrix.width(),
       textMin;



void callback(char* topic, byte* payload, unsigned int length) {
  char s[length + 1];
  for (int i = 0; i < length; i++) {
    s[i] = (char)payload[i];
  }
  s[length] = '\0';
  mode = String(s);
  Serial.println(mode);
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
  matrix.fillCircle(5, 11, 2, matrix.Color333(7, 4, 0));
  matrix.drawPixel(5, 7, matrix.Color333(7, 4, 0));
  matrix.drawPixel(2, 8, matrix.Color333(7, 4, 0));
  matrix.drawPixel(8, 8, matrix.Color333(7, 4, 0));
  matrix.drawPixel(1, 11, matrix.Color333(7, 4, 0));
  matrix.drawPixel(9, 11, matrix.Color333(7, 4, 0));
  matrix.drawPixel(2, 14, matrix.Color333(7, 4, 0));
  matrix.drawPixel(8, 14, matrix.Color333(7, 4, 0));
  matrix.drawPixel(5, 15, matrix.Color333(7, 4, 0));
}


void drawCloud() {
  //matrix.drawCircle(7, 7, 7, matrix.Color333(0, 0, 7));
  matrix.drawPixel(6, 8, matrix.Color333(0,4,7));
  matrix.drawPixel(7, 8, matrix.Color333(0,4,7));
  matrix.drawPixel(8, 8, matrix.Color333(0,4,7));
  matrix.drawPixel(5, 9, matrix.Color333(0,4,7));
  matrix.drawPixel(9, 9, matrix.Color333(0,4,7));
  matrix.drawPixel(3, 10, matrix.Color333(0,4,7));
  matrix.drawPixel(4, 10, matrix.Color333(0,4,7));
  matrix.drawPixel(10, 10, matrix.Color333(0,4,7));
  matrix.drawPixel(2, 11, matrix.Color333(0,4,7));
  matrix.drawPixel(5, 11, matrix.Color333(0,4,7));
  matrix.drawPixel(10, 11, matrix.Color333(0,4,7));
  matrix.drawPixel(11, 11, matrix.Color333(0,4,7));
  matrix.drawPixel(2, 12, matrix.Color333(0,4,7));
  matrix.drawPixel(6, 12, matrix.Color333(0,4,7));
  matrix.drawPixel(10, 10, matrix.Color333(0,4,7));
  matrix.drawPixel(10, 10, matrix.Color333(0,4,7));
  matrix.drawPixel(10, 10, matrix.Color333(0,4,7));
  matrix.drawPixel(10, 10, matrix.Color333(0,4,7));
  matrix.drawPixel(10, 10, matrix.Color333(0,4,7));
  matrix.drawPixel(10, 10, matrix.Color333(0,4,7));
  matrix.drawLine(10, 12, 12, 12, matrix.Color333(0,4,7));
  matrix.drawLine(1, 13, 1, 14, matrix.Color333(0,4,7));
  matrix.drawLine(13, 13, 13, 14, matrix.Color333(0,4,7));
  matrix.drawLine(2, 15, 12, 15, matrix.Color333(0,4,7));
}


void drawRain() {
  //matrix.drawCircle(7, 7, 7, matrix.Color333(0, 0, 7));
  matrix.drawLine(4, 8, 6, 8, matrix.Color333(0,4,7));
  matrix.drawLine(3, 9, 7, 9, matrix.Color333(0,4,7));
  matrix.drawPixel(2, 10, matrix.Color333(0,4,7));
  matrix.drawPixel(4, 10, matrix.Color333(0,4,7));
  matrix.drawPixel(6, 10, matrix.Color333(0,4,7));
  matrix.drawPixel(8, 10, matrix.Color333(0,4,7));
  matrix.drawLine(1, 11, 9, 11, matrix.Color333(0,4,7));
  matrix.drawPixel(2, 12, matrix.Color333(0,4,7));
  matrix.drawPixel(4, 12, matrix.Color333(0,4,7));
  matrix.drawPixel(6, 12, matrix.Color333(0,4,7));
  matrix.drawPixel(8, 12, matrix.Color333(0,4,7));
  matrix.drawPixel(3, 13, matrix.Color333(0,4,7));
  matrix.drawPixel(5, 13, matrix.Color333(0,4,7));
  matrix.drawPixel(7, 13, matrix.Color333(0,4,7));
  matrix.drawPixel(3, 15, matrix.Color333(0,4,7));
  matrix.drawPixel(5, 15, matrix.Color333(0,4,7));
  matrix.drawPixel(7, 15, matrix.Color333(0,4,7));
  
}



void drawClock() {
  matrix.setCursor(0, 1);   // start at top left, with one pixel of spacing
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
       matrix.drawPixel(11, 3, matrix.Color333(9, 9, 9));
       matrix.drawPixel(11, 6, matrix.Color333(9, 9, 9));
    } else {
       matrix.drawPixel(5, 3, matrix.Color333(9, 9, 9));
       matrix.drawPixel(5, 6, matrix.Color333(9, 9, 9));
    }
  }
  on = !on;
}

void scrollText() {
  matrix.setTextSize(2);
  matrix.setTextWrap(false); // Allow text to run off right edge
  matrix.setTextColor(matrix.Color333(1,0,0));
  matrix.setCursor(textX, 1);
  matrix.print("CS390N 11:30AM - 2:30PM  CS585 3:30PM - 5:30PM");
  textMin = sizeof("CS390N 11:30AM-2:30PM  CS585 3:30PM-5:30PM") * -6;
  if((textX -= 4) < textMin) textX = matrix.width();
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
    drawClock();
    drawTemp();
    drawWeather();
  } else if (mode == CAL){
    scrollText();
  } else {
    drawMusic();
  }
  matrix.swapBuffers(false);
  delay(200);
  client.loop();

}
