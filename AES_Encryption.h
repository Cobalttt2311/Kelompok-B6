// Dekripsi AES

void invSubBytes(unsigned char * state);
// implementasi: Inverse SubBytes
// Membalikkan operasi SubBytes yang dilakukan selama enkripsi.

void invShiftRows(unsigned char * state);
// Implementasi: Inverse ShiftRows
// Membalikkan operasi ShiftRows yang dilakukan selama enkripsi.

void invShiftRow(unsigned char * state, unsigned char nbr);
// Implementasi: Inverse ShiftRow
// Membalikkan pergeseran satu baris yang dilakukan selama enkripsi.

void invMixColumns(unsigned char * state);
// Implementasi: Inverse MixColumns
// Membalikkan operasi MixColumns yang dilakukan selama enkripsi.

void invMixColumn(unsigned char * kolom);
// Implementasi: Kebalikan dari MixColumn
// Membalikkan pencampuran kolom tunggal yang dilakukan selama enkripsi.

void aes_invRound(unsigned char * state, unsigned char * roundKey);
// Implementasi: Invers Round AED (Putaran Terbalik AES)
// Mengeksekusi satu putaran dekripsi AES.

void aes_invMain(unsigned char * state, unsigned char * expandedKey, int nbrRounds);
// Implementasi: AES Inverse Main
// Mengeksekusi proses dekripsi utama untuk AES.	

unsigned char getSBoxInvert(unsigned char num);
// Mengambil nilai invers dari tabel S-Box.

Translated with DeepL.com (free version)
