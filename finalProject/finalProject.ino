#include <WiFiEsp.h>
#include <WiFiEspClient.h>
#include <PubSubClient.h>
#include <Adafruit_GFX.h>   // Core graphics library
#include <RGBmatrixPanel.h> // Hardware-specific library
#include "WiFiEspUdp.h"
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
WiFiEspUDP Udp;
RGBmatrixPanel matrix(A, B, C, CLK, LAT, OE, true);
IPAddress timeServer(132,163,97,3);
const int timeZone = -4;  // Eastern Daylight Time (USA)
unsigned int localPort = 8888;  // local port to listen for UDP packets




time_t getNtpTime();
void sendNTPpacket(IPAddress &address);


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
  matrix.fillScreen(matrix.Color333(0, 0, 0));
  matrix.setCursor(13, 2);   // start at top left, with one pixel of spacing
  matrix.setTextColor(matrix.Color333(0,7,0));
  Serial.println(hour());
  if (hour() == 12) {
    matrix.print("12");
    pm();
  } else if (hour() == 0) {
    matrix.print("12");
    am();
  } else if (hour() < 12) {
    matrix.setCursor(15, 2);
    am();
    matrix.print(hour());
  } else {
    matrix.setCursor(13, 2);
    matrix.print(hour() % 12);
    pm();
  }
    matrix.print(":");
    if (minute() <10) {
    matrix.print("0");
    matrix.print(minute());
        } else {
    matrix.print(minute());
    }
    matrix.print(":");
    if (second() <10) {
    matrix.print("0");
    matrix.print(second());
        } else {
    matrix.print(second());
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
  
  Udp.begin(localPort);
  Serial.println("waiting for sync");
  setSyncProvider(getNtpTime);
  
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


/*-------- NTP code ----------*/

const int NTP_PACKET_SIZE = 48; // NTP time is in the first 48 bytes of message
byte packetBuffer[NTP_PACKET_SIZE]; //buffer to hold incoming & outgoing packets

time_t getNtpTime()
{
  while (Udp.parsePacket() > 0) ; // discard any previously received packets
  Serial.println("Transmit NTP Request");
  sendNTPpacket(timeServer);
  uint32_t beginWait = millis();
  while (millis() - beginWait < 1500) {
    int size = Udp.parsePacket();
    if (size >= NTP_PACKET_SIZE) {
      Serial.println("Receive NTP Response");
      Udp.read(packetBuffer, NTP_PACKET_SIZE);  // read packet into the buffer
      unsigned long secsSince1900;
      // convert four bytes starting at location 40 to a long integer
      secsSince1900 =  (unsigned long)packetBuffer[40] << 24;
      secsSince1900 |= (unsigned long)packetBuffer[41] << 16;
      secsSince1900 |= (unsigned long)packetBuffer[42] << 8;
      secsSince1900 |= (unsigned long)packetBuffer[43];
      return secsSince1900 - 2208988800UL + timeZone * SECS_PER_HOUR;
    }
  }
  Serial.println("No NTP Response :-(");
  return 0; // return 0 if unable to get the time
}

// send an NTP request to the time server at the given address
void sendNTPpacket(IPAddress &address)
{
  // set all bytes in the buffer to 0
  memset(packetBuffer, 0, NTP_PACKET_SIZE);
  // Initialize values needed to form NTP request
  // (see URL above for details on the packets)
  packetBuffer[0] = 0b11100011;   // LI, Version, Mode
  packetBuffer[1] = 0;     // Stratum, or type of clock
  packetBuffer[2] = 6;     // Polling Interval
  packetBuffer[3] = 0xEC;  // Peer Clock Precision
  // 8 bytes of zero for Root Delay & Root Dispersion
  packetBuffer[12]  = 49;
  packetBuffer[13]  = 0x4E;
  packetBuffer[14]  = 49;
  packetBuffer[15]  = 52;
  // all NTP fields have been given values, now
  // you can send a packet requesting a timestamp:                 
  Udp.beginPacket(address, 123); //NTP requests are to port 123
  Udp.write(packetBuffer, NTP_PACKET_SIZE);
  Udp.endPacket();
}
