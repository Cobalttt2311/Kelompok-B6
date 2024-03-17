#ifndef expandkey_h
#define expandkey_h

//Procedure pembangkit_kunci AES Encrypt 128 Bit
void pembangkit_kunci(unsigned char *word, int iteration);

// Implementasi procedure AES round
void aes_round(unsigned char *state, unsigned char *roundKey);

// Procedure expandkey
void expandKey(unsigned char *expandedKey, unsigned char *key, enum keySize size, size_t expandedKeySize);

#endif