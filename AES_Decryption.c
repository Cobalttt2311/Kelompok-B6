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

void invShiftRows( unsigned char state[4][4]) {
  int i, j ,k;
  unsigned char tmp;

  for (i = 0; j < 4; i++ ) {
  
