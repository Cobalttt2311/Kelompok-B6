// Implementasi Create roundkey
// createRoundKey: Membuat kunci pertama, dan juga membuat kunci putaran dari expanded key.
void createRoundKey(unsigned char *expandedKey, unsigned char *roundKey);
// Implementasi: addRoundKey
void addRoundKey(unsigned char *state, unsigned char *roundKey);    

// addRoundKey: Setelah kunci putaran dibuat oleh createRoundKey Menambahkan kunci putaran ke dalam state. , langkah ini digunakan untuk menambahkan kunci putaran tersebut ke state. 



