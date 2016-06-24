byte reverseByte(byte b) {
    b = b >> 4 | b << 4;
    b = (b & B11001100) >> 2 | (b & B00110011) << 2;
    b = (b & B10101010) >> 1 | (b & B01010101) << 1;
    return b;
}
