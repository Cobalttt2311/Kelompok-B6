#include <stdio.h>

typedef unsigned char byte;

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
