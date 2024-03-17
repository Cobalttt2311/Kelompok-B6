#ifnedef AESENCRYPT_H
#define AESENCRYPT_H

//Punya Nalendra

// Implementasi : encrypt
char aes_encrypt(unsigned char *input, unsigned char *output, unsigned char *key, enum keySize size);

#endif
