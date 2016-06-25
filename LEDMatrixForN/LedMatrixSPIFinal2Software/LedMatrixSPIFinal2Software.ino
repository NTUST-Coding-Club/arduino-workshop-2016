#include "font5x7.h"

#define reg_noop        0x00
#define reg_decode_mode 0x09
#define reg_brightness  0x0A
#define reg_scan_limit  0x0B
#define reg_shutdown    0x0C
#define reg_test        0x0F

#define DIN 11
#define CS  10
#define CLK 9
#define DEVICE_NUMBER 2

char helloString[] = "Hello, world!";
int length = strlen(helloString);

void setup() {
    // 設定 SPI 腳位
    pinMode(DIN, OUTPUT);
    pinMode(CS, OUTPUT);
    pinMode(CLK, OUTPUT);
    digitalWrite(CS, HIGH); // MAX7219 的 CS 是 active-low
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
}

void loop() {
    if (isTimerUp(100)) updateLEDs();
    static uint16_t t = 0;
    Serial.println(t++);
}

bool isTimerUp(unsigned long period) {
    static unsigned long timer = millis();
    bool timeIsUp = (millis() - timer) > period;
    if (timeIsUp) timer = millis();
    return timeIsUp;
}

void updateLEDs() {
    static char delta = DEVICE_NUMBER * 8;
    for (int i = 0; i < length; i++)
        for (int j = 0; j < 5; j++)
            drawColumn(i * 5 + j + delta,
                    font5x7[(helloString[i] - 32) * 5 + j]);
    delta = (delta < -(length * 5)) ? DEVICE_NUMBER * 8 : (delta - 1);
}

void drawColumn(byte column, byte value) {
    byte n = column / 8;
    byte c = column % 8;
    setCommand(n, c + 1, value);
}

void clearAllLEDs() {
    for (byte i = 0; i <  8; i++)
        setCommand(i + 1, 0);
}

void setCommand(byte command, byte value) {
    setCommand(255, command, value);
}

void setCommand(byte device, byte command, byte value) {
    digitalWrite(CS, LOW);
    for (byte i = 0; i < DEVICE_NUMBER; i++) {
        if (i == device || device == 255) {
            shiftOut(DIN, CLK, MSBFIRST, command);
            shiftOut(DIN, CLK, MSBFIRST, value);
        } else {
            shiftOut(DIN, CLK, MSBFIRST, reg_noop);
            shiftOut(DIN, CLK, MSBFIRST, 0);
        }
    }
    digitalWrite(CS, HIGH);
}
