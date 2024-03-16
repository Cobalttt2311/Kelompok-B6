#ifndef AESMAIN_H
#define AESMAIN_H

// aes_main,  enkripsi AES pada state menggunakan kunci yang diperluas untuk putaran yang ditentukan
void aes_main(unsigned char *state, unsigned char *expandedKey, int nbrRounds);

#endif 
