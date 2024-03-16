#ifnedef expandkey_h
#define expandkey_h

//Procedure pembangkit_kunci AES Encrypt 128 Bit
void pembangkit_kunci(char *word, int iteration);

// Implementasi procedure AES round
void aes_round(char *state, char *roundKey);

#endif