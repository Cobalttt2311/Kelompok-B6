#include <stdio.h>
#include <string.h>

// Deklarasi fungsi-fungsi yang diperlukan
void rotateToLeft(char a[], int n);
void shiftRows(char input[][3], char output_shiftRows[][3]);

int main() {
    // Contoh input
    char input[16][3] = {
        "00", "01", "02", "03",
        "10", "11", "12", "13",
        "20", "21", "22", "23",
        "30", "31", "32", "33"
    };
    // Array untuk menyimpan hasil Shift Rows
    char output_shiftRows[16][3];

    // Memanggil fungsi shiftRows
    shiftRows(input, output_shiftRows);

    // Menampilkan hasil Shift Rows
    printf("Hasil Shift Rows:\n");
    for (int i = 0; i < 16; i++) {
        printf("%s%s", output_shiftRows[i], (i != 15) ? ", " : "\n");
    }

    return 0;
}

// Fungsi untuk melakukan rotasi ke kiri sebanyak n kali pada array a
void rotateToLeft(char a[], int n) {
    char temp;
    while (n-- > 0) {
        temp = a[0];
        for (int i = 0; i < 3; i++) {
            a[i] = a[i + 1];
        }
        a[3] = temp;
    }
}

// Fungsi untuk Shift Rows
void shiftRows(char input[][3], char output_shiftRows[][3]) {
    char row1[4], row2[4], row3[4];
    
    // Meng-copy baris-baris dari input ke row1, row2, dan row3
    memcpy(output_shiftRows, input, sizeof(char) * 16 * 3);
    memcpy(row1, input[0], sizeof(char) * 3 * 4);
    memcpy(row2, input[4], sizeof(char) * 3 * 4);
    memcpy(row3, input[8], sizeof(char) * 3 * 4);

    // Melakukan rotasi ke kiri pada setiap baris sesuai aturan Shift Rows
    rotateToLeft(row1, 1);
    rotateToLeft(row2, 2);
    rotateToLeft(row3, 3);

    // Meng-copy kembali row1, row2, dan row3 yang telah di-shift ke output_shiftRows
    memcpy(output_shiftRows[0], row1, sizeof(char) * 3 * 4);
    memcpy(output_shiftRows[4], row2, sizeof(char) * 3 * 4);
    memcpy(output_shiftRows[8], row3, sizeof(char) * 3 * 4);
}
