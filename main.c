#include <stdio.h>  // for printf
#include <stdlib.h> // for malloc, free
#include "AES_Encryption.h"

//enum KeySize, digunakan untuk merepresentasikan ukuran kunci
enum keySize
{
    SIZE_16 = 16 // Ukuran kunci 128 bit
};
//enum errorCode, untuk penanda kesalahan
enum errorCode
{
    SUCCESS = 0,                  // Kode sukses
    ERROR_AES_UNKNOWN_KEYSIZE,    // Kode kesalahan untuk ukuran kunci tidak dikenal
    ERROR_MEMORY_ALLOCATION_FAILED // Kode kesalahan untuk kegagalan alokasi memori
};

int main(int argc, char *argv[])
{
    // the expanded keySize
    int expandedKeySize = 176;

    // the expanded key
    unsigned char expandedKey[expandedKeySize];
	
    // the cipher key
    unsigned char key[16];

    // the cipher key size
    enum keySize size = SIZE_16;

    // the plaintext
    unsigned char plaintext[16]; 
    // the ciphertext
    unsigned char ciphertext[16];

    // the decrypted text
    unsigned char decryptedtext[16];

    int i;
	int var;

    printf("\n");
    printf("*   Basic implementation of AES algorithm in C   *\n");
    printf("\n");
	
	while(1) { // Loop indefinitely until user chooses to exit
        printf("Masukkan Pilihan : \n");
        printf("1. Enkripsi\n");
        printf("2. Dekripsi\n");
        printf("3. Keluar\n");
        scanf("%d", &var);
        system("cls");
    
    switch (var) {
        case 1:
            printf("Enter Cipher Key (16 characters):\n");
    fflush(stdin);
    for (i = 0; i < 16; i++)
    {
        scanf("%c", &key[i]);
    }

    printf("\nEnter Plaintext (16 characters):\n");
    fflush(stdin);
    for (i = 0; i < 16; i++)
    {
        scanf("%c", &plaintext[i]);
    }
    
	aes_encrypt(plaintext, ciphertext, key, SIZE_16);
	
	printf("\nCipher Key (HEX format):\n");
    for (i = 0; i < 16; i++)
    {
        printf("%2.2x%c", key[i], ((i + 1) % 16) ? ' ' : '\n');
    }
	
	printf("\nPlaintext (HEX format):\n");
    for (i = 0; i < 16; i++)
    {
        printf("%2.2x%c", plaintext[i], ((i + 1) % 16) ? ' ' : '\n');
    }
    
    // Test the Key Expansion
    expandKey(expandedKey, key, size, expandedKeySize);

    printf("\nExpanded Key (HEX format):\n");
    for (i = 0; i < expandedKeySize; i++)
    {
        printf("%2.2x%c", expandedKey[i], ((i + 1) % 16) ? ' ' : '\n');
    }
    
    printf("\nCiphertext (HEX format):\n");
    for (i = 0; i < 16; i++)
    {
        printf("%2.2x%c", ciphertext[i], ((i + 1) % 16) ? ' ' : '\n');
    }
              
    printf("\nCiphertext (Text format):\n");
                for (i = 0; i < 16; i++)
                {
                    printf("%c", ciphertext[i]);
                }
                printf("\n\n");
                break;
    	}
    }
    return 0;
}
