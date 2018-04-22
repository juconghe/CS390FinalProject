#include <WiFiEsp.h>
#include <WiFiEspClient.h>
#include <PubSubClient.h>
#include <Adafruit_GFX.h>   // Core graphics library
#include <RGBmatrixPanel.h> // Hardware-specific library
#include <TimeLib.h>

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

const char* ssid = "AHHA Lab Wifi";
const char* password =  "ramanujan";
int status = WL_IDLE_STATUS; // the Wifi radio's status
RGBmatrixPanel matrix(A, B, C, CLK, LAT, OE, true);


void callback(char* topic, byte* payload, unsigned int length) {
  matrix.fillScreen(0);
  matrix.setCursor(0, 1);
  char s[length + 1];
  for (int i = 0; i < length; i++) {
    s[i] = (char)payload[i];
  }
  s[length] = '\0';
  matrix.print(s);
  matrix.swapBuffers(false);
}

WiFiEspClient espClient;
PubSubClient client("io.adafruit.com", 1883, callback, espClient);
 
void reconnect() {
  while (!client.connected()) {
    Serial.println("Connecting to MQTT...");
 
    if (client.connect("MEGA", ADAFRUIT_USERNAME, AIO_KEY )) {
 
      Serial.println("connected and Subscribing");  
      client.subscribe(SLIDER_PATH, 1);
      client.publish(PUB_FEED_PATH, "Connect");
      
    } else {
      Serial.print("failed with state ");
      Serial.print(client.state());
      delay(2000);
 
    }
  }
}

void pm() {
      //M
      matrix.drawPixel(7, 5, matrix.Color333(7,0,7));
      matrix.drawPixel(7, 6, matrix.Color333(7,0,7));
      matrix.drawPixel(7, 7, matrix.Color333(7,0,7));
      matrix.drawPixel(7, 8, matrix.Color333(7,0,7));
      matrix.drawPixel(10, 5, matrix.Color333(7,0,7));
      matrix.drawPixel(10, 6, matrix.Color333(7,0,7));
      matrix.drawPixel(10, 7, matrix.Color333(7,0,7));   
      matrix.drawPixel(10, 8, matrix.Color333(7,0,7)); 
      matrix.drawPixel(8, 6, matrix.Color333(7,0,7));  
      matrix.drawPixel(9, 6, matrix.Color333(7,0,7));  
      //P
      matrix.drawPixel(5, 5, matrix.Color333(7,0,7));
      matrix.drawPixel(4, 5, matrix.Color333(7,0,7));
      matrix.drawPixel(3, 5, matrix.Color333(7,0,7));
      matrix.drawPixel(2, 5, matrix.Color333(7,0,7));
      matrix.drawPixel(2, 6, matrix.Color333(7,0,7));
      matrix.drawPixel(2, 7, matrix.Color333(7,0,7));   
      matrix.drawPixel(2, 8, matrix.Color333(7,0,7)); 
      matrix.drawPixel(5, 6, matrix.Color333(7,0,7));  
      matrix.drawPixel(5, 7, matrix.Color333(7,0,7));  
      matrix.drawPixel(4, 7, matrix.Color333(7,0,7)); 
      matrix.drawPixel(3, 7, matrix.Color333(7,0,7)); 
      //A
      //matrix.drawPixel(6, 8, matrix.Color333(7,0,7)); 
}

void am() {
      //M
      pm();
      //A
      matrix.drawPixel(5, 8, matrix.Color333(7,0,7)); 
}

void drawSun(){
       //matrix.drawCircle(7, 7, 7, matrix.Color333(0, 0, 7));
  matrix.setCursor(1, 9);   // next line
  matrix.setTextColor(matrix.Color333(0,7,7)); 
  matrix.print('*');
  matrix.setTextColor(matrix.Color333(0,4,7)); 
  matrix.print('R');
  matrix.setTextColor(matrix.Color333(0,0,7));
  matrix.print('G');
  matrix.setTextColor(matrix.Color333(4,0,7)); 
  matrix.print("B");
  matrix.setTextColor(matrix.Color333(7,0,4)); 
  matrix.print("*");
  
  }

void drawClock() {
  matrix.swapBuffers(false);
  int chour = hour();
  int cminute = minute();
  int csecond = second();
  matrix.fillScreen(matrix.Color333(0, 0, 0));
  matrix.setCursor(13, 2);   // start at top left, with one pixel of spacing
  matrix.setTextColor(matrix.Color333(0,7,0));
  Serial.println(chour);
  if (chour == 12) {
    matrix.print("12");
    pm();
  } else if (chour == 0) {
    matrix.print("12");
    am();
  } else if (chour < 12) {
    matrix.setCursor(15, 2);
    am();
    matrix.print(chour);
  } else {
    matrix.setCursor(13, 2);
    matrix.print(chour % 12);
    pm();
  }
    matrix.print(":");
    if (cminute <10) {
    matrix.print("0");
    matrix.print(cminute);
        } else {
    matrix.print(cminute);
    }
    matrix.print(":");
    if (csecond <10) {
    matrix.print("0");
    matrix.print(csecond);
        } else {
    matrix.print(csecond);
    }
}

void setup() {

  configTime(-4 * 3600, 0, "pool.ntp.org.", "time,nist.gov");
  Serial.println("Waiting for time");
  while (!time(&nullptr)) {
    Serial.print(".");
    delay(1000):
  }
  Serial.begin(115200);
 // initialize serial for ESP module
  Serial2.begin(9600);
  // initialize ESP module
  WiFi.init(&Serial2);
  
  WiFi.begin(ssid, password);
 
  // attempt to connect to WiFi network
  while ( status != WL_CONNECTED) {
    Serial.print("Attempting to connect to WPA SSID: ");
    Serial.println(ssid);
    // Connect to WPA/WPA2 network
    status = WiFi.begin(ssid, password);
  }
  Serial.println("Connected to the WiFi network");
  matrix.begin();
  matrix.setTextWrap(false); // Allow text to run off right edge
  matrix.setTextSize(1);
}

 
void loop() {

  if (!client.connected()) {
    reconnect();
  }
  drawClock();
  drawSun();
  delay(100);
  client.loop();

}
