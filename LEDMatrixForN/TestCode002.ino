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
    delay(2000);
    // 清除畫面
    ledController.clear();
    Serial.begin(9600);
    Serial.println("Setting Complete!");
}

void loop() {
    if (Serial.available() > 0) {
        byte x = Serial.parseInt();
        byte y = Serial.parseInt();
        ledController.setDot(x, y, true);
    }
}
