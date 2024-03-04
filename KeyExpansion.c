void keyExpansion(const char *key, unsigned char roundKeys[176]) {
    int i, j;
    unsigned char temp[4];

    for (i = 0; i < 16; i++) {
        roundKeys[i] = key[i];
    }

    for (i = 16; i < 176; i += 4) {
        for (j = 0; j < 4; j++) {
            temp[j] = roundKeys[i - 4 + j];
        }

        if (i % 16 == 0) {
            unsigned char tempByte = temp[0];
            for (j = 0; j < 3; j++) {
                temp[j] = temp[j + 1];
            }
            temp[3] = tempByte;

            for (j = 0; j < 4; j++) {
                temp[j] = (temp[j] >> 4) ^ (temp[j] & 0x0F);
            }

            temp[0] ^= rcon[i / 16 - 1][0];
            temp[1] ^= rcon[i / 16 - 1][1];
            temp[2] ^= rcon[i / 16 - 1][2];
            temp[3] ^= rcon[i / 16 - 1][3];

            for (j = 0; j < 4; j++) {
                roundKeys[i + j] = roundKeys[i - 16 + j] ^ temp[j];
            }
        } else {
            for (j = 0; j < 4; j++) {
                roundKeys[i + j] = roundKeys[i - 16 + j] ^ temp[j];
            }
        }
    }
}