#include <stdio.h>
#include <string.h>

void rotateToLeft(char a[], int n);
void shiftRows(char input[][4], char output_shiftRows[][4]);

int main() {
    // Matriks input 4x4
    char input[4][4];

    // Meminta pengguna untuk memasukkan nilai matriks
    printf("Masukkan nilai matriks 4x4:\n");
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            scanf(" %c", &input[i][j]);
        }
    }

    // Menampilkan matriks sebelum Shift Rows
    printf("Matriks sebelum Shift Rows:\n");
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            printf("%c ", input[i][j]);
        }
        printf("\n");
    }

    // Array untuk menyimpan hasil Shift Rows
    char output_shiftRows[4][4];

    // Memanggil fungsi shiftRows
    shiftRows(input, output_shiftRows);

    // Menampilkan matriks setelah Shift Rows
    printf("\nMatriks setelah Shift Rows:\n");
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            printf("%c ", output_shiftRows[i][j]);
        }
        printf("\n");
    }

    return 0;
}

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

void shiftRows(char input[][4], char output_shiftRows[][4]) {
    char row1[4], row2[4], row3[4], row4[4];

    // Meng-copy baris-baris dari input ke row1, row2, row3, dan row4
    memcpy(output_shiftRows, input, sizeof(char) * 4 * 4);
    memcpy(row1, input[0], sizeof(char) * 4);
    memcpy(row2, input[1], sizeof(char) * 4);
    memcpy(row3, input[2], sizeof(char) * 4);
    memcpy(row4, input[3], sizeof(char) * 4);

    // Melakukan rotasi ke kiri pada setiap baris sesuai aturan Shift Rows
    rotateToLeft(row2, 1);
    rotateToLeft(row3, 2);
    rotateToLeft(row4, 3);

    // Meng-copy kembali row1, row2, row3, dan row4 yang telah di-shift ke output_shiftRows
    memcpy(output_shiftRows[0], row1, sizeof(char) * 4);
    memcpy(output_shiftRows[1], row2, sizeof(char) * 4);
    memcpy(output_shiftRows[2], row3, sizeof(char) * 4);
    memcpy(output_shiftRows[3], row4, sizeof(char) * 4);
}
