#include <WiFiEsp.h>
#include <WiFiEspClient.h>
#include <PubSubClient.h>
#include <Adafruit_GFX.h>   // Core graphics library
#include <RGBmatrixPanel.h> // Hardware-specific library

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

const char* ssid = "Jucong";
const char* password =  "Hjc1995ma";
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

void setup() {
 
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
  matrix.setTextSize(2);
 
}

 
void loop() {

  if (!client.connected()) {
    reconnect();
  }
  delay(100);
  client.loop();

}
