#include <WiFiEsp.h>
#include <WiFiEspClient.h>
#include <PubSubClient.h>
#include <TimeLib.h>
#include "NTP.h"
#include <string.h>
#include "matrix.h"

#define ADAFRUIT_USERNAME  "Jucong"
#define AIO_KEY  "01a85723468e409bb15488a77efe724c"
#define PUB_FEED_PATH ADAFRUIT_USERNAME "/feeds/publish"

const char* ssid = "AHHA Lab Wifi";
const char* password =  "ramanujan";
int status = WL_IDLE_STATUS; // the Wifi radio's status

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
      schedule = String(s);
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

// Create an pubsub client
// first argument is the host address
// second argument is the port number
// third argument is the callback function, it calls everytime a message is received
// forth argument is the wifi client instance\
// more detail visit https://pubsubclient.knolleary.net/api.html#subscribe
PubSubClient client("io.adafruit.com", 1883, callback, espClient);

// function that check the connection of pubsub client periodically
void reconnect() {
  while (!client.connected()) {
    Serial.println(F("Connecting to MQTT..."));

    // first argument is the identifer of the machine, it can be anything you want
    // second argument is the user name of the server
    // third argument is the password of the server
    if (client.connect("MEGA", ADAFRUIT_USERNAME, AIO_KEY )) {

      // first argument ist he topic the PubSubClient subscribe
      // second argument is the quality of service, from 0 to 1
      client.subscribe(PUB_FEED_PATH, 1);
      Serial.println(F("Connected"));
    } else {
      Serial.print(F("failed with state "));
      Serial.print(client.state());
      delay(2000);
    }
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
