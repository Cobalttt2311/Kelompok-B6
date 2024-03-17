#ifndef EXPANDKEY_H
#define EXPANDKEY_H

// aes_round
void aes_round(unsigned char state[4][4], unsigned char roundKey[4][4]); 

// Procedure expandkey
void expandKey(unsigned char *expandedKey, unsigned char *key, enum keySize size, size_t expandedKeySize);

#endif