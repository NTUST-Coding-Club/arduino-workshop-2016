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
}

void loop() {
    
}
