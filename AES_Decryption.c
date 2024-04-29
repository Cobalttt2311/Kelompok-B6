
#include <stdio.h>  
#include <stdlib.h> 
#define BLOCK_SIZE 16

enum errorCode
{
    SUCCESS = 0,
    ERROR_AES_UNKNOWN_KEYSIZE,
    ERROR_MEMORY_ALLOCATION_FAILED,
};

enum keySize
{
    SIZE_16 = 16
};

char inverseSbox[16][16] = {
    {0x52, 0x09, 0x6a, 0xd5, 0x30, 0x36, 0xa5, 0x38, 0xbf, 0x40, 0xa3, 0x9e, 0x81, 0xf3, 0xd7, 0xfb}, // 0
    {0x7c, 0xe3, 0x39, 0x82, 0x9b, 0x2f, 0xff, 0x87, 0x34, 0x8e, 0x43, 0x44, 0xc4, 0xde, 0xe9, 0xcb}, // 1
    {0x54, 0x7b, 0x94, 0x32, 0xa6, 0xc2, 0x23, 0x3d, 0xee, 0x4c, 0x95, 0x0b, 0x42, 0xfa, 0xc3, 0x4e}, // 2
    {0x08, 0x2e, 0xa1, 0x66, 0x28, 0xd9, 0x24, 0xb2, 0x76, 0x5b, 0xa2, 0x49, 0x6d, 0x8b, 0xd1, 0x25}, // 3
    {0x72, 0xf8, 0xf6, 0x64, 0x86, 0x68, 0x98, 0x16, 0xd4, 0xa4, 0x5c, 0xcc, 0x5d, 0x65, 0xb6, 0x92}, // 4
    {0x6c, 0x70, 0x48, 0x50, 0xfd, 0xed, 0xb9, 0xda, 0x5e, 0x15, 0x46, 0x57, 0xa7, 0x8d, 0x9d, 0x84}, // 5
    {0x90, 0xd8, 0xab, 0x00, 0x8c, 0xbc, 0xd3, 0x0a, 0xf7, 0xe4, 0x58, 0x05, 0xb8, 0xb3, 0x45, 0x06}, // 6
    {0xd0, 0x2c, 0x1e, 0x8f, 0xca, 0x3f, 0x0f, 0x02, 0xc1, 0xaf, 0xbd, 0x03, 0x01, 0x13, 0x8a, 0x6b}, // 7
    {0x3a, 0x91, 0x11, 0x41, 0x4f, 0x67, 0xdc, 0xea, 0x97, 0xf2, 0xcf, 0xce, 0xf0, 0xb4, 0xe6, 0x73}, // 8
    {0x96, 0xac, 0x74, 0x22, 0xe7, 0xad, 0x35, 0x85, 0xe2, 0xf9, 0x37, 0xe8, 0x1c, 0x75, 0xdf, 0x6e}, // 9
    {0x47, 0xf1, 0x1a, 0x71, 0x1d, 0x29, 0xc5, 0x89, 0x6f, 0xb7, 0x62, 0x0e, 0xaa, 0x18, 0xbe, 0x1b}, // A
    {0xfc, 0x56, 0x3e, 0x4b, 0xc6, 0xd2, 0x79, 0x20, 0x9a, 0xdb, 0xc0, 0xfe, 0x78, 0xcd, 0x5a, 0xf4}, // B
    {0x1f, 0xdd, 0xa8, 0x33, 0x88, 0x07, 0xc7, 0x31, 0xb1, 0x12, 0x10, 0x59, 0x27, 0x80, 0xec, 0x5f}, // C
    {0x60, 0x51, 0x7f, 0xa9, 0x19, 0xb5, 0x4a, 0x0d, 0x2d, 0xe5, 0x7a, 0x9f, 0x93, 0xc9, 0x9c, 0xef}, // D
    {0xa0, 0xe0, 0x3b, 0x4d, 0xae, 0x2a, 0xf5, 0xb0, 0xc8, 0xeb, 0xbb, 0x3c, 0x83, 0x53, 0x99, 0x61}, // E
    {0x17, 0x2b, 0x04, 0x7e, 0xba, 0x77, 0xd6, 0x26, 0xe1, 0x69, 0x14, 0x63, 0x55, 0x21, 0x0c, 0x7d}  // F
};

void invsubBytes(int ukuran, unsigned char state[ukuran][ukuran]) {
  int i, j;
  for (i = 0; i < ukuran; i++) {
    for (j = 0; j < ukuran; j++) {
      int row = (state[i][j] >> 4) & 0x0F;
      int col = state[i][j] & 0x0F;
      state[i][j] = inverseSbox[row][col];
    }
  }

void aes_invRound(unsigned char state[4][4], unsigned char roundKey[4][4])
{
  invShiftRows(state);
  invSubBytes(state);
  addRoundKey(state, roundKey);
  invMixColumns(state);
}

char aes_decrypt(unsigned char *input, unsigned char *output, unsigned char *key, enum keySize size)
{
  // the number of rounds
  int nbrRounds;

  // the expanded key
  unsigned char expandedKey[16][16]; // 15 rounds maximum

  // the 128 bit block to decode
  unsigned char block[BLOCK_SIZE];

  int i, j;

  // set the number of rounds
  switch (size)
  {
  case SIZE_16:
    nbrRounds = 10;
    break;
  default:
    return ERROR_AES_UNKNOWN_KEYSIZE;
    break;
  }

  // Set the block values
  for (i = 0; i < 4; i++)
  {
    for (j = 0; j < 4; j++)
      block[(i + (j * 4))] = input[(i * 4) + j];
  }

  // Expand the key into a 176 bytes key
  expandKey(expandedKey[0], key, size, 16 * (nbrRounds + 1));

  // Decrypt the block using the expandedKey
  // Pass the address of block (which acts as 2D array)
  aes_invMain(block, expandedKey[0], nbrRounds); 

  // Unmap the block again into the output
  for (i = 0; i < 4; i++)
  {
    for (j = 0; j < 4; j++)
      output[(i * 4) + j] = block[(i + (j * 4))];
  }

  return SUCCESS;
}

void invShiftRows(unsigned char state[4][4]) {
    int i, j, k;
    unsigned char tmp;

    for (i = 0; i < 4; i++) {
        // Jumlah pergesseran dengan berdasarkan indeks baris
        int shift = i;

        // pergeseran ke kanan dengan berdasarkan posisi shift
        for (j = 0; j < shift; j++) {
            tmp = state[i][3];  // melakukan penyimpanan untuk elemen terakhir
            for ( k = 2; k >= 0; k--) {  // melakukan pergeseran elemen ke kanan
                state[i][k + 1] = state[i][k];
            }
            state[i][0] = tmp;  // Move the stored element to the beginning
        }
    }
}

char aes_decrypt(unsigned char *input, unsigned char *output, unsigned char *key, enum keySize size)
{
  // deklarasi variabel number of rounds
  int nbrRounds;

  // the expanded key
  unsigned char expandedKey[16][16]; // 15 rounds maximum

  // blok 128 bit untuk decode
  unsigned char block[BLOCK_SIZE];

  int i, j;

  // mengatur nomor putaran(rounds)
  switch (size)
  {
  case SIZE_16:
    nbrRounds = 10;
    break;
  default:
    return ERROR_AES_UNKNOWN_KEYSIZE;
    break;
  }

  // Set the block values
  for (i = 0; i < 4; i++)
  {
    for (j = 0; j < 4; j++)
      block[(i + (j * 4))] = input[(i * 4) + j];
  }

  // Expand key menjadi 176 bytes key
  expandKey(expandedKey[0], key, size, 16 * (nbrRounds + 1));

  // Decrypt the block using the expandedKey
  // Pass the address of block (which acts as 2D array)
  aes_invMain(block, expandedKey[0], nbrRounds); 

  // Unmap the block again into the output
  for (i = 0; i < 4; i++)
  {
    for (j = 0; j < 4; j++)
      output[(i * 4) + j] = block[(i + (j * 4))];
  }

void invMixColumns(unsigned char state[4][4]) {
    // Define the inverse mix matrix
    unsigned char invMixMatrix[4][4] = {
        {0x0e, 0x0b, 0x0d, 0x09},
        {0x09, 0x0e, 0x0b, 0x0d},
        {0x0d, 0x09, 0x0e, 0x0b},
        {0x0b, 0x0d, 0x09, 0x0e}
    };

    int i, j;
    unsigned char column[4];
    unsigned char result[4];

    for (i = 0; i < 4; i++) {
        for (j = 0; j < 4; j++) {
            column[j] = state[j][i];
        }

        for (j = 0; j < 4; j++) {
            result[j] = galois_multiplication(invMixMatrix[j][0], column[0]) ^
                        galois_multiplication(invMixMatrix[j][1], column[1]) ^
                        galois_multiplication(invMixMatrix[j][2], column[2]) ^
                        galois_multiplication(invMixMatrix[j][3], column[3]);
        }

        for (j = 0; j < 4; j++) {
            state[j][i] = result[j];
        }
    }
}
