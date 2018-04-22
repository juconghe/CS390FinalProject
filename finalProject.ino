#include <WiFiEsp.h>
#include <WiFiEspClient.h>
#include <PubSubClient.h>

#define ADAFRUIT_USERNAME  "Jucong"
#define AIO_KEY  "01a85723468e409bb15488a77efe724c"
#define SUB_FEED_PATH ADAFRUIT_USERNAME "/feeds/test"
#define PUB_FEED_PATH ADAFRUIT_USERNAME "/feeds/testPub"

const char* ssid = "Jucong";
const char* password =  "Hjc1995ma";
int status = WL_IDLE_STATUS; // the Wifi radio's status

void callback(char* topic, byte* payload, unsigned int length) {
  Serial.println(topic);
  Serial.write(payload, length);
  Serial.println("");
}

WiFiEspClient espClient;
PubSubClient client("io.adafruit.com", 1883, callback, espClient);
 
void reconnect() {
  while (!client.connected()) {
    Serial.println("Connecting to MQTT...");
 
    if (client.connect("MEGA", ADAFRUIT_USERNAME, AIO_KEY )) {
 
      Serial.println("connected and Subscribing");  
      client.subscribe(SUB_FEED_PATH, 1);
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
 
}

 
void loop() {

  if (!client.connected()) {
    reconnect();
  }
  delay(100);
  client.loop();

}
