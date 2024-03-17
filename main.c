#include <stdio.h>  
#include <stdlib.h> 

enum keySize
{
    SIZE_16 = 16
};	

enum errorCode
{
    SUCCESS = 0,
    ERROR_AES_UNKNOWN_KEYSIZE,
    ERROR_MEMORY_ALLOCATION_FAILED,
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

    int i;
    int var;

    printf("\n");
    printf("+-+-+-+-+-+-+-+-+-+-+\n");
    printf("|         AES       |\n");
    printf("+-+-+-+-+-+-+-+-+-+-+\n\n");
	
	while(1) { // Loop sampe user exit
        printf("+-------------------+\n");
        printf("| Masukkan Pilihan: |\n");
        printf("+-------------------+\n");
        printf("| 1. Enkripsi       |\n");
        printf("| 2. Dekripsi/Soon  |\n");
        printf("| 3. Keluar         |\n");
        printf("+-------------------+\n");
        printf("Pilihan Anda: ");
        scanf("%d", &var);
        system("cls"); // Hapus layar sebelum mencetak menu yang diperbarui
    
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
    
    	    //Key Expansion
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
	case 3:
        	return SUCCESS;
    	}
    }
    return 0;
}
