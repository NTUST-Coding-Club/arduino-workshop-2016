#define reg_noop        0x00
#define reg_decode_mode 0x09
#define reg_brightness  0x0A
#define reg_scan_limit  0x0B
#define reg_shutdown    0x0C
#define reg_test        0x0F

#define DIN 10
#define CS  9
#define CLK 8
#define DEVICE_NUMBER 2

byte pic00[] = {B00001111, B00001111, B00110011, B00101011,
                B11010100, B11001100, B11110000, B11110000};
byte pic01[] = {B11110000, B11110000, B11001100, B11010100,
                B00101011, B00110011, B00001111, B00001111};
byte heart00[] = {B00011000, B00111100, B01111110, B11111100,
                B11111100, B01111110, B00111100, B00011000};
byte heart01[] = {B00000000, B00011000, B00111100, B01111000,
                B01111000, B00111100, B00011000, B00000000};
byte charA[] = {B00000000, B00000000, B01111110, B00001001,
                B00001001, B01111110, B00000000, B00000000};
byte charB[] = {B00000000, B00000000, B01111111, B01001001,
                B01001001, B00111110, B00000000, B00000000};

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
    if (Serial.available() > 0) {
        byte column = Serial.parseInt();
        byte value = Serial.parseInt();
        drawColumn(column, value);
    }
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
    digitalWrite(CS, LOW);
    for (byte i = 0; i < DEVICE_NUMBER; i++) {
        if (i == device || device == 255) {
            spiTransfer(DIN, CLK, command);
            spiTransfer(DIN, CLK, value);
        } else {
            spiTransfer(DIN, CLK, reg_noop);
            spiTransfer(DIN, CLK, 0);
        }
    }
    digitalWrite(CS, HIGH);
}

void spiTransfer(byte dataPin, byte clockPin, byte value) {
    byte reversedValue = reverseByte(value);
    for (byte i = 0; i < 8; i++) {
        digitalWrite(clockPin, LOW);
        digitalWrite(dataPin, reversedValue & (1 << i));
        // MAX7219 會在 clock pin 從 LOW 變成 HIGH 的時候接收資料
        digitalWrite(clockPin, HIGH);
    }
}

byte reverseByte(byte b) {
    b = b >> 4 | b << 4;
    b = (b & B11001100) >> 2 | (b & B00110011) << 2;
    b = (b & B10101010) >> 1 | (b & B01010101) << 1;
    return b;
}
