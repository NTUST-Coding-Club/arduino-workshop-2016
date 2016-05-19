// import the LedControl library
#include "LedControl.h"
// import the fonts
#include "fonts.h"

// define device number
#define MatrixNumber 2

// create a instance of LedControl
LedControl ledControler = LedControl(12, 10, 11, MatrixNumber);

// declare and initialze strength of light
byte intensity = 0;
byte buffers[MatrixNumber * 8] = {0};
char msg[] = "NTUST Coding Club!     abcdefghijklmnopqrstuvwxyz";
int msgSize = strlen(msg);

unsigned char reverseByte(unsigned char b) {
    b = (b & 0xF0) >> 4 | (b & 0x0F) << 4;
    b = (b & 0xCC) >> 2 | (b & 0x33) << 2;
    b = (b & 0xAA) >> 1 | (b & 0x55) << 1;
    return b;
}

void scroll(byte chr) {
    for (byte i = 0; i < 8; i++) {
        buffers[MatrixNumber * 8 - 1] = reverseByte(font_8x8[chr - 32][i]);
        for (byte j = 0; j < (MatrixNumber * 8 - 1); j++) {
            buffers[j] = buffers[j + 1];
            ledControler.setRow(j / 8, j % 8, buffers[j]);
        }
        ledControler.setRow(MatrixNumber - 1, 7, buffers[MatrixNumber * 8 - 1]);
        delay(100);
    }
}

void setup() {
    // turn off power-saving mode of MAX7219
    ledControler.shutdown(0, false);
    ledControler.shutdown(1, false);
    // initialize brightness of LED Matrix
    ledControler.setIntensity(0, intensity);
    ledControler.setIntensity(1, intensity);
}

void loop() {
    static int index = 0;
    //scroll(msg[index++ % msgSize]);
    for (byte i = 0; i < 95; i++) {
        scroll(i + 32);
    }
}
