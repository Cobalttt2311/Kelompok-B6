// Fungsi untuk melakukan operasi ShiftRows
void shiftRows(unsigned char state[NB][NB]) {
    shiftRow2(state);
    shiftRow3(state);
    shiftRow4(state);
}

// Fungsi untuk melakukan pergeseran baris pada baris kedua
void shiftRow2(unsigned char state[NB][NB]) {
    unsigned char temp;
    temp = state[1][0];
    state[1][0] = state[1][1];
    state[1][1] = state[1][2];
    state[1][2] = state[1][3];
    state[1][3] = temp;
}

// Fungsi untuk melakukan pergeseran baris pada baris ketiga
void shiftRow3(unsigned char state[NB][NB]) {
    unsigned char temp;
    temp = state[2][0];
    state[2][0] = state[2][2];
    state[2][2] = temp;
    temp = state[2][1];
    state[2][1] = state[2][3];
    state[2][3] = temp;
}

// Fungsi untuk melakukan pergeseran baris pada baris keempat
void shiftRow4(unsigned char state[NB][NB]) {
    unsigned char temp;
    temp = state[3][0];
    state[3][0] = state[3][1];
    state[3][1] = state[3][2];
    state[3][2] = state[3][3];
    state[3][3] = temp;
}