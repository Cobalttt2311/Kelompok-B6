#ifndef DECRYPTION_H
#define DECRYPTION_H

void aes_invRound(unsigned char state[4][4], unsigned char roundKey[4][4]); //inverse tahapan  di round
char aes_decrypt(unsigned char *input, unsigned char *output, unsigned char *key, enum keySize size); //proses decrypt 

#endif
