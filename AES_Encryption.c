
#include <stdio.h>
#include <stdlib.h>

// enum KeySize, digunakan untuk merepresentasikan ukuran kunci
enum keySize
{
    SIZE_16 = 16 // Ukuran kunci 128 bit
};
//enum errorCode, untuk penanda kesalahan
enum errorCode
{
    SUCCESS = 0,                  // Kode sukses
    ERROR_AES_UNKNOWN_KEYSIZE,    // Kode kesalahan untuk ukuran kunci tidak dikenal
    ERROR_MEMORY_ALLOCATION_FAILED // Kode kesalahan untuk kegagalan alokasi memori
};

// S-Box, Mendefinisikan array sbox yang berisi tabel substitusi S-box untuk enkripsi AES.
char sbox[16][16] = {
    {0x63, 0x7c, 0x77, 0x7b, 0xf2, 0x6b, 0x6f, 0xc5, 0x30, 0x01, 0x67, 0x2b, 0xfe, 0xd7, 0xab, 0x76}, // 0
    {0xca, 0x82, 0xc9, 0x7d, 0xfa, 0x59, 0x47, 0xf0, 0xad, 0xd4, 0xa2, 0xaf, 0x9c, 0xa4, 0x72, 0xc0}, // 1
    {0xb7, 0xfd, 0x93, 0x26, 0x36, 0x3f, 0xf7, 0xcc, 0x34, 0xa5, 0xe5, 0xf1, 0x71, 0xd8, 0x31, 0x15}, // 2
    {0x04, 0xc7, 0x23, 0xc3, 0x18, 0x96, 0x05, 0x9a, 0x07, 0x12, 0x80, 0xe2, 0xeb, 0x27, 0xb2, 0x75}, // 3
    {0x09, 0x83, 0x2c, 0x1a, 0x1b, 0x6e, 0x5a, 0xa0, 0x52, 0x3b, 0xd6, 0xb3, 0x29, 0xe3, 0x2f, 0x84}, // 4
    {0x53, 0xd1, 0x00, 0xed, 0x20, 0xfc, 0xb1, 0x5b, 0x6a, 0xcb, 0xbe, 0x39, 0x4a, 0x4c, 0x58, 0xcf}, // 5
    {0xd0, 0xef, 0xaa, 0xfb, 0x43, 0x4d, 0x33, 0x85, 0x45, 0xf9, 0x02, 0x7f, 0x50, 0x3c, 0x9f, 0xa8}, // 6
    {0x51, 0xa3, 0x40, 0x8f, 0x92, 0x9d, 0x38, 0xf5, 0xbc, 0xb6, 0xda, 0x21, 0x10, 0xff, 0xf3, 0xd2}, // 7
    {0xcd, 0x0c, 0x13, 0xec, 0x5f, 0x97, 0x44, 0x17, 0xc4, 0xa7, 0x7e, 0x3d, 0x64, 0x5d, 0x19, 0x73}, // 8
    {0x60, 0x81, 0x4f, 0xdc, 0x22, 0x2a, 0x90, 0x88, 0x46, 0xee, 0xb8, 0x14, 0xde, 0x5e, 0x0b, 0xdb}, // 9
    {0xe0, 0x32, 0x3a, 0x0a, 0x49, 0x06, 0x24, 0x5c, 0xc2, 0xd3, 0xac, 0x62, 0x91, 0x95, 0xe4, 0x79}, // A
    {0xe7, 0xc8, 0x37, 0x6d, 0x8d, 0xd5, 0x4e, 0xa9, 0x6c, 0x56, 0xf4, 0xea, 0x65, 0x7a, 0xae, 0x08}, // B
    {0xba, 0x78, 0x25, 0x2e, 0x1c, 0xa6, 0xb4, 0xc6, 0xe8, 0xdd, 0x74, 0x1f, 0x4b, 0xbd, 0x8b, 0x8a}, // C
    {0x70, 0x3e, 0xb5, 0x66, 0x48, 0x03, 0xf6, 0x0e, 0x61, 0x35, 0x57, 0xb9, 0x86, 0xc1, 0x1d, 0x9e}, // D
    {0xe1, 0xf8, 0x98, 0x11, 0x69, 0xd9, 0x8e, 0x94, 0x9b, 0x1e, 0x87, 0xe9, 0xce, 0x55, 0x28, 0xdf}, // E
    {0x8c, 0xa1, 0x89, 0x0d, 0xbf, 0xe6, 0x42, 0x68, 0x41, 0x99, 0x2d, 0x0f, 0xb0, 0x54, 0xbb, 0x16}  // F
};


// Rcon, Mendefinisikan array konstanta putaran yang digunakan untuk pembangkitan kunci
unsigned char Rcon[11] = {
    0x8d, 0x01, 0x02, 0x04, 0x08, 0x10, 0x20, 0x40, 0x80, 0x1b, 0x36};

// subBytes, Terapkan transformasi SubBytes pada state
void subBytes(int baris, int kolom, unsigned char state[baris][kolom]) {
  int i, j, row, col;
  for (i = 0; i < baris; i++) {
    for (j = 0; j < kolom; j++) {
	row = (state[i][j] >> 4) & 0x0F;
	col = state[i][j] & 0x0F;
	state[i][j] = sbox[row][col];
    }
  }
}

// shiftRows, Terapkan transformasi ShiftRows pada state
void shiftRows(unsigned char state[4][4]) {
 int i, j;
 unsigned char tmp;
 for (i = 0; i < 4; i++) {
  for (j = 0; j < i; j++) {
   tmp = state[i][0];
   state[i][0] = state[i][1];
   state[i][1] = state[i][2];
   state[i][2] = state[i][3];
   state[i][3] = tmp;
  }
 }
}


// addRoundKey, Terapkan AddRoundKey pada state
void addRoundKey(unsigned char state[4][4], unsigned char roundKey[4][4]) {
  int i, j;
  for (i = 0; i < 4; i++) {
    for (j = 0; j < 4; j++) {
      state[i][j] = state[i][j] ^ roundKey[i][j];
    }
  }
}

// galois_multiplication, Melakukan perkalian Galois untuk keperluan mix columns
unsigned char galois_multiplication(unsigned char a, unsigned char b)
{
    unsigned char p = 0;
    unsigned char counter;
    unsigned char hi_bit_set;
    for (counter = 0; counter < 8; counter++)
    {
        if ((b & 1) == 1)
            p ^= a;
        hi_bit_set = (a & 0x80);
        a <<= 1;
        if (hi_bit_set == 0x80)
            a ^= 0x1b;
        b >>= 1;
    }
    return p;
}

// mixColumns, Terapkan transformasi MixColumns pada state
void mixColumns(unsigned char state[4][4])
{
    int i, j;
    unsigned char column[4]; 


    unsigned char mixMatrix[4][4] = {
        {0x02, 0x03, 0x01, 0x01},
        {0x01, 0x02, 0x03, 0x01},
        {0x01, 0x01, 0x02, 0x03},
        {0x03, 0x01, 0x01, 0x02}
    };

    unsigned char result[4]; 

    for (i = 0; i < 4; i++)
    {
        for (j = 0; j < 4; j++)
            column[j] = state[j][i]; 


        for (j = 0; j < 4; j++)
        {
            result[j] = galois_multiplication(mixMatrix[j][0], column[0]) ^
                        galois_multiplication(mixMatrix[j][1], column[1]) ^
                        galois_multiplication(mixMatrix[j][2], column[2]) ^
                        galois_multiplication(mixMatrix[j][3], column[3]);
        }

        for (j = 0; j < 4; j++)
            state[j][i] = result[j];
    }
}

// createRoundKey, Buat kunci putaran untuk iterasi tertentu dari kunci yang diperluas
void createRoundKey(unsigned char expandedKey[4][4], unsigned char roundKey[4][4]) {
  int i, j;
  // Iterasi baris
  for (i = 0; i < 4; i++) {
    // Iterasi kolom
    for (j = 0; j < 4; j++) {
      roundKey[j][i] = expandedKey[i][j];
    }
  }
}

// aes_round, Lakukan satu putaran enkripsi AES pada state dengan kunci putaran yang diberikan
void aes_round(unsigned char state[4][4], unsigned char roundKey[4][4]) {
  subBytes(4,4,state);
  shiftRows(state);
  mixColumns(state);
  addRoundKey(state, roundKey);
}

//expandKey, Mendefinisikan fungsi expandKey untuk memperluas kunci utama menjadi kunci yang diperluas sesuai dengan algoritma AES.
void expandKey(unsigned char *expandedKey, unsigned char *key, enum keySize size, size_t expandedKeySize) {
  int currentSize = 0;
  int rconIteration = 1;
  int i;
  unsigned char t[4] = {0}; // t digunakan untuk menyimpan nilai sementara

  // Salin kunci awal ke dalam kunci yang diperluas
  for (i = 0; i < size; i++) {
    expandedKey[i] = key[i];
  }
  currentSize += size;

  // Loop sampai kunci yang diperluas mencapai ukuran yang diinginkan
  while (currentSize < expandedKeySize) {
    // Ambil 4 byte terakhir sebagai nilai sementara
    for (i = 0; i < 4; i++) {
      t[i] = expandedKey[(currentSize - 4) + i];
    }

    // pembangkit kunci, melakukan Rotword, Subword, dan XOR
    if (currentSize % size == 0) {
    	
      // Operasi Rotasi (ROTWORD)
      unsigned char temp = t[0];
      for (i = 0; i < 3; i++) // Loop untuk melakukan rotasi ke kiri pada karakter
	  {
        t[i] = t[i + 1]; // Pindahkan karakter ke kiri
      }
      t[3] = temp; // Tempatkan karakter pertama yang disimpan di akhir

      // Substitusi S-Box pada keempat bagian dari word (SubWord)
      for (i = 0; i < 4; ++i) {
        t[i] = sbox[t[i] / 16] [t[i] % 16];
      }

      // XOR dengan Rcon
      t[0] = t[0] ^ Rcon[rconIteration++];
    }

    // XOR nilai sementara dengan blok sebelumnya dan tambahkan ke kunci yang diperluas
    for (i = 0; i < 4; i++) {
      expandedKey[currentSize] = expandedKey[currentSize - size] ^ t[i];
      currentSize++;
    }
  }
}


// aes_main, Lakukan enkripsi AES pada state menggunakan kunci yang diperluas untuk putaran yang ditentukan
void aes_main(unsigned char state[4][4], unsigned char *expandedKey, int nbrRounds) {
  int i = 0;
  unsigned char roundKey[4][4];

  
  // Buat intialround
	createRoundKey((unsigned char (*)[4])expandedKey, (unsigned char (*)[4])roundKey);


  // tambahkan roundkey pertama ke dalam state
  	addRoundKey(state, roundKey);

  // Iterate for all rounds except the last
  	for (i = 1; i < nbrRounds; i++) {

    // buat roundkey selanjutnya.
	createRoundKey((unsigned char (*)[4])(expandedKey + (i * 16)), (unsigned char (*)[4])roundKey);


    // Melakukan proses enkripsi aes sesuai state
    aes_round(state, roundKey);
  }

  // Buat last round key 
  createRoundKey((unsigned char (*)[4])(expandedKey + (nbrRounds * 16)), (unsigned char (*)[4])roundKey);


  subBytes(4,4,state);
  shiftRows(state);
  addRoundKey(state, roundKey);
}

//aes_encrypt, Mendefinisikan fungsi aes_encrypt yang merupakan antarmuka untuk melakukan enkripsi AES dengan input berupa teks biasa, kunci.
char aes_encrypt(unsigned char *input, unsigned char *output, unsigned char *key, enum keySize size) {
  // Ukuran kunci yang diperluas
  int expandedKeySize;
  // Jumlah putaran AES
  int nbrRounds;
  // Kunci yang telah diperluas
  unsigned char *expandedKey;
  // Blok 128 bit untuk dienkripsi
  unsigned char block[4][4];
  // Variabel loop
  int i, j;
  // Tetapkan jumlah putaran berdasarkan ukuran kunci
  switch (size) {
  case SIZE_16:
    nbrRounds = 10; // Kunci 128-bit memiliki 10 putaran
    break;
  default:
    return ERROR_AES_UNKNOWN_KEYSIZE;
    break;
  }

  expandedKeySize = (16 * (nbrRounds + 1)); // Hitung ukuran kunci yang diperluas 176

  // Alokasi memori untuk expandedKey
  expandedKey = (unsigned char *)malloc(expandedKeySize * sizeof(unsigned char));

  if (expandedKey == NULL) {
    return ERROR_MEMORY_ALLOCATION_FAILED; // Kembalikan kesalahan jika alokasi memori gagal
  } else {

    // Iterasi untuk kolom
	for (i = 0; i < 4; i++) {
		//iterasi untuk baris
	  for (j = 0; j < 4; j++) {
	    block[j][i] = input[(i * 4) + j];
	  }
	}

    // Perluas kunci menjadi kunci 176 byte
    expandKey(expandedKey, key, size, expandedKeySize);

    // Enkripsi blok menggunakan expandedKey
    aes_main(block, expandedKey, nbrRounds);

    // Kembalikan blok lagi ke output
    for (i = 0; i < 4; i++) {
      // Iterasi untuk baris
      for (j = 0; j < 4; j++) {
        output[(i * 4) + j] = block[j][i];
      }
    }

    // Bebaskan memori untuk expandedKey
    free(expandedKey);
    expandedKey = NULL;
  }

  return SUCCESS; // Kembalikan kode sukses
}

