#define BLYNK_PRINT Serial


#include <ESP8266_Lib.h>
#include <BlynkSimpleShieldEsp8266.h>
#include <Adafruit_GFX.h>   // Core graphics library
#include <RGBmatrixPanel.h> // Hardware-specific library


#define CLK 8  // MUST be on PORTB! (Use pin 11 on Mega)
#define LAT A3
#define OE  9
#define A   A0
#define B   A1
#define C   A2


// or Software Serial on Uno, Nano...
#include <SoftwareSerial.h>
SoftwareSerial EspSerial(10, 11); // RX, TX

// Your ESP8266 baud rate:
#define ESP8266_BAUD 9600

// You should get Auth Token in the Blynk App.
// Go to the Project Settings (nut icon).
char auth[] = "7c75c07d1334448cbe7242ca05233218";

// Your WiFi credentials.
// Set password to "" for open networks.
char ssid[] = "weihai";
char pass[] = "weihaihenshuai";
RGBmatrixPanel *matrixptr;

ESP8266 wifi(&EspSerial);

void setup()
{
  // Debug console
  Serial.begin(57600);

  // Set ESP8266 baud rate
  EspSerial.begin(ESP8266_BAUD);
  delay(10);

  Blynk.begin(auth, wifi, ssid, pass);
  RGBmatrixPanel matrix(A, B, C, CLK, LAT, OE, false);
  matrixptr = &matrix;
//  matrixptr -> begin();
//  matrixptr -> setTextWrap(false);
//  matrixptr -> setTextSize(2);
  free(matrixptr -> backBuffer());
}

BLYNK_WRITE(V1)
{
//  int pinValue = param.asInt(); // assigning incoming value from pin V1 to a variable
  // You can also use:
  // String i = param.asStr();
  // double d = param.asDouble();
  Serial.println("1");
//  matrixptr -> fillScreen(0);
//  matrixptr -> setTextColor(matrixptr ->Color333(7,0,0));
//  matrixptr -> setCursor(0, 1);
//  matrixptr -> print(pinValue);
}

void loop()
{
  Blynk.run();
  // You can inject your own code or combine it with other sketches.
  // Check other examples on how to communicate with Blynk. Remember
  // to avoid delay() function!
}

