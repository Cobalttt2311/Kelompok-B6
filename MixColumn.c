#include <stdio.h>

typedef unsigned char byte;

int tabelSubByte[16][16] = {
    {99, 124, 119, 123, 242, 107, 111, 197, 48, 1, 103, 43, 254, 215, 171, 118},
    {202, 130, 201, 125, 250, 89, 71, 240, 173, 212, 162, 175, 156, 164, 114, 192},
    {183, 253, 147, 38, 54, 63, 247, 204, 52, 165, 229, 241, 113, 216, 49, 21},
    {4, 199, 35, 195, 24, 150, 5, 154, 7, 18, 128, 226, 235, 39, 178, 117},
    {9, 131, 44, 26, 27, 110, 90, 160, 82, 59, 214, 179, 41, 227, 47, 132},
    {83, 209, 0, 237, 32, 252, 177, 91, 106, 203, 190, 57, 74, 76, 88, 207},
    {208, 239, 170, 251, 67, 77, 51, 133, 69, 249, 2, 127, 80, 60, 159, 168},
    {81, 163, 64, 143, 146, 157, 56, 245, 188, 182, 218, 33, 16, 255, 243, 210},
    {205, 12, 19, 236, 95, 151, 68, 23, 196, 167, 126, 61, 100, 93, 25, 115},
    {96, 129, 79, 220, 34, 42, 144, 136, 70, 238, 184, 20, 222, 94, 11, 219},
    {224, 50, 58, 10, 73, 6, 36, 92, 194, 211, 172, 98, 145, 149, 228, 121},
    {231, 200, 55, 109, 141, 213, 78, 169, 108, 86, 244, 234, 101, 122, 174, 8},
    {186, 120, 37, 46, 28, 166, 180, 198, 232, 221, 116, 31, 75, 189, 139, 138},
    {112, 62, 181, 102, 72, 3, 246, 14, 97, 53, 87, 185, 134, 193, 29, 158},
    {225, 248, 152, 17, 105, 217, 142, 148, 155, 30, 135, 233, 206, 85, 40, 223},
    {140, 161, 137, 13, 191, 230, 66, 104, 65, 153, 45, 15, 176, 84, 187, 22}
};

void mixColumns(byte state[][4]) {
    byte temp[4];

    for (int i = 0; i < 4; ++i) {
        temp[0] = state[0][i] ^ state[1][i] ^ state[2][i] ^ state[3][i];
        byte x = state[0][i] ^ state[1][i];
        byte xtime = x << 1;
        if (state[0][i] & 0x80)
            xtime ^= 0x1B; // XOR with irreducible polynomial x^8 + x^4 + x^3 + x + 1
        temp[1] = xtime ^ state[1][i] ^ state[2][i] ^ state[3][i];
        x = state[1][i] ^ state[2][i];
        xtime = x << 1;
        if (state[1][i] & 0x80)
            xtime ^= 0x1B;
        temp[2] = xtime ^ state[2][i] ^ state[3][i] ^ state[0][i];
        x = state[2][i] ^ state[3][i];
        xtime = x << 1;
        if (state[2][i] & 0x80)
            xtime ^= 0x1B;
        temp[3] = xtime ^ state[3][i] ^ state[0][i] ^ state[1][i];

        // Copy the values back to the state
        for (int j = 0; j < 4; ++j) {
            state[j][i] = temp[j];
        }
    }
}

void printState(byte state[][4]) {
    for (int i = 0; i < 4; ++i) {
        for (int j = 0; j < 4; ++j) {
            printf("%02x ", state[i][j]);
        }
        printf("\n");
    }
}

int main() {
    byte state[4][4];

    printf("Enter the state matrix (4x4 in hexadecimal):\n");
    for (int i = 0; i < 4; ++i) {
        for (int j = 0; j < 4; ++j) {
            scanf("%hhx", &state[i][j]);
        }
    }

    printf("\nState matrix before MixColumns:\n");
    printState(state);

    mixColumns(state);

    printf("\nState matrix after MixColumns:\n");
    printState(state);

    return 0;
}
