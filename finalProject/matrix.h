#include <Adafruit_GFX.h>   // Core graphics library
#include <RGBmatrixPanel.h> // Hardware-specific library

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

RGBmatrixPanel matrix(A, B, C, CLK, LAT, OE, true);
int WEATHER_MODE = SUNNY;
bool on = true;
String mode = HOME;
int    textX   = matrix.width(),
       textMin;
String temperature = "0";
String schedule = "";

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
  matrix.print(schedule);
  textMin = sizeof(schedule) * -6;
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
