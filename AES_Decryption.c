#include <stdio.h>  
#include <stdlib.h> 
#define BLOCK_SIZE 16

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
        // Number of cyclic shifts for this row (based on row index)
        int shift = i;

        // Perform cyclic shift to the right by `shift` positions
        for (j = 0; j < shift; j++) {
            tmp = state[i][3];  // Store the last element
            for ( k = 2; k >= 0; k--) {  // Shift elements to the right
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
