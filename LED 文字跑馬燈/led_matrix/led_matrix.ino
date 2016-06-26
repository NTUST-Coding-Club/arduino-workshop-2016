#include <MaxMatrix.h>
#include "font5x7.h"

#define MAT_DIN 11
#define MAT_CS  10
#define MAT_CLK 9

#define MAT_COUNT 2

MaxMatrix m(MAT_DIN, MAT_CS, MAT_CLK, MAT_COUNT);

void setup() {
  m.init();
  m.setIntensity(5);

  Serial.begin(9600);
}

int t = 4;
char buff[128] = "OwO ";

void loop() {
  for(int i = 0; i < t; i++) {
    int current = (buff[i] - 32) * 5;
    for(int j = 0; j < 5; j++) {
      m.setColumn(0, font5x7[current + j]);
      m.shiftLeft(true);
      delay(100);
    }
    m.setColumn(0, 0);
    m.shiftLeft(true);
    delay(100);
  }

  if(Serial.available()) {
    char c;
    t = 0;
    while(Serial.available()) {
      c = Serial.read();
      if(c == '\n') {
        break;
      } else {
        buff[t++] = c;
      }
    }
  }
}
