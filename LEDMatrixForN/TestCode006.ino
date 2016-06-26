#include "MaxMatrix.h"

#define DIN 11
#define CS  10
#define CLK 9
#define DEVICE_NUMBER 2

MaxMatrix ledController(DIN, CS, CLK, DEVICE_NUMBER);

void setup() {
    // 初始設定
    ledController.init();
    // 設定亮度
    ledController.setIntensity(0);
    // 測試
    for (byte i = 0; i < 8; i++) {
        ledController.setDot(i, i, true);
    }
    delay(1000);
    // 清除畫面
    ledController.clear();
    Serial.begin(9600);
    Serial.println("Setting Complete!");
    ledController.setColumn(0, 1);
    ledController.setColumn(1, 2);
    ledController.setColumn(2, 3);
    ledController.setColumn(3, 4);
    ledController.setColumn(4, 16);
    ledController.setColumn(5, 32);
    ledController.setColumn(6, 64);
    ledController.setColumn(7, 255);
    ledController.setColumn(8, 127);
    ledController.setColumn(9, 63);
    ledController.setColumn(10, 31);
    ledController.setColumn(11, 15);
    ledController.setColumn(12, B11100000);
    ledController.setColumn(13, B10100000);
    ledController.setColumn(14, B00111100);
    ledController.setColumn(15, B11000011);
    delay(1000);
}

void loop() {
    ledController.shiftLeft(false, true);
    delay(200);
}
