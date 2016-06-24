#include <SPI.h>
/* Arduino 內建 SPI 腳位
 *  DIN MOSI(11)
 *  CS SS(10)
 *  CLK SCK(13)
 */
#include "font5x7.h"

#define reg_noop        0x00
#define reg_decode_mode 0x09
#define reg_brightness  0x0A
#define reg_scan_limit  0x0B
#define reg_shutdown    0x0C
#define reg_test        0x0F

#define DEVICE_NUMBER 2

byte columns[16] = {
    0x7F, 0x08, 0x08, 0x08, 0x7F, // H
    0x00, 0x44, 0x7D, 0x40, 0x00, // i
    0x00, 0x00, 0x5F, 0x00, 0x00  // !
};

void setup() {
    // 設定 SPI
    SPI.begin();
    // LED 模組初始化
    setCommand(reg_decode_mode, 0);
    setCommand(reg_brightness, 0);
    setCommand(reg_scan_limit, 7);
    setCommand(reg_shutdown, 1);
    setCommand(reg_test, 0);
    // 清除 MAX7219 的所有輸出
    clearAllLEDs();
    // 開啟 Serial 連接
    Serial.begin(9600);
    Serial.println("Setting Complete!");
    // Hi
    for (byte i = 0; i < 16; i++) {
        drawColumn(i, columns[i]);
    }
}

void loop() {
    
}

void drawColumn(byte column, byte value) {
    byte n = column / 8;
    byte c = column % 8;
    setCommand(n, c + 1, value);
}

void clearAllLEDs() {
    for (byte i = 0; i <  8; i++) {
        setCommand(i + 1, 0);
    }
}

void setCommand(byte command, byte value) {
    setCommand(255, command, value);
}

void setCommand(byte device, byte command, byte value) {
    digitalWrite(SS, LOW);
    for (byte i = 0; i < DEVICE_NUMBER; i++) {
        if (i == device || device == 255) {
            SPI.transfer(command);
           SPI.transfer(value);
        } else {
            SPI.transfer(reg_noop);
            SPI.transfer(0);
        }
    }
    digitalWrite(SS, HIGH);
}
