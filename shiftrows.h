// shiftRows, Terapkan transformasi ShiftRows pada state
void shiftRows(unsigned char *state) {
    int i, j;
    unsigned char tmp;

    for (i = 0; i < 4; i++) {
        // Menggeser baris ke kiri sesuai dengan nomor barisnya
        for (j = 0; j < i; j++) {
            tmp = state[i * 4]; // Simpan byte pertama
            state[i * 4] = state[i * 4 + 1]; // Geser byte ke-2 ke byte pertama
            state[i * 4 + 1] = state[i * 4 + 2]; // Geser byte ke-3 ke byte ke-2
            state[i * 4 + 2] = state[i * 4 + 3]; // Geser byte ke-4 ke byte ke-3
            state[i * 4 + 3] = tmp; // Pindahkan byte pertama ke byte ke-4
        }
    }
}