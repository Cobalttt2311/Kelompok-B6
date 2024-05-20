#include <stdio.h>  // for printf
#include <stdlib.h> // for malloc, free
#include "AES_Encryption.h"
#include "AES_Decryption.h"
#include "addroundkey.h"
#include "aesencrypt.h"
#include "aesmain.h"
#include "expandkey.h"
#include "mixcolumn.h"
#include "shiftrows.h"
#include "subbytes.h"
#include "invExpandedkey.h"
#include "invMixColumn.h"
#include "invShiftRows.h"
#include "invaesmain.h"
#include "invSubByte.h"

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

int main()
{

    address first;
    address firstDec;
    int choice;
    char filename[100];
    int width, height, channels;
    unsigned char* image_data;
    char masukan;
    int totalfib;
    int i;
    int var;
    char temp[50];
    first = Nil;
    firstDec = Nil;
    totalfib = 1;
	
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

    while(1) 
    { // Loop indefinitely until user chooses to exit
    	printf("=============================================================\n");
        printf("|                      AES & LSB Kelompok 6                 |\n");
        printf("=============================================================\n");
        printf("|                           MENU                            |\n");
        printf("|-----------------------------------------------------------|\n");
        printf("| 1. Enkripsi                                               |\n");
        printf("| 2. Dekripsi                                               |\n");
        printf("| 3. Sisipkan Pesan ke Gambar                               |\n");
        printf("| 4. Ekstrak Pesan dari Gambar                              |\n");
        printf("| 5. Exit                                                   |\n");
        printf("=============================================================\n");

        printf("\n Masukkan Pilihan (1)/(2)/(3)/(4)/(5) : ");

        if (scanf("%d", &var) != 1 || var < 1 || var > 5)
        {
            printf("\nInvalid input. Tolong masukkan angka antara 1 sampai 5.\n");
            fflush(stdin); // Clear the input buffer for the next iteration
            printf("\nTekan Enter untuk melanjutkan...");
            getchar();
            system("cls");
            continue;
    }
            
    printf("=============================================================\n");
    switch (var) {
        case 1:
            printf("\nMasukkan Cipher Key (16 karakter):\n");
    	    fflush(stdin);
    	    for (i = 0; i < 16; i++)
    	    {
        	scanf("%c", &key[i]);
    	    }

    	    printf("\nMasukkan Plain Text (16 karakter):\n");
    	    fflush(stdin);
    	    for (i = 0; i < 16; i++)
    	    {
            	scanf("%c", &plaintext[i]);
            }
    
	    aes_encrypt(plaintext, ciphertext, key, SIZE_16);
	
	    printf("\nCipher Key (Format HEX):\n");
    	    for (i = 0; i < 16; i++)
            {
            	printf("%2.2x%c", key[i], ((i + 1) % 16) ? ' ' : '\n');
   	    }
	
	    printf("\nPlain Text (Format HEX):\n");
            for (i = 0; i < 16; i++)
            {
            	printf("%2.2x%c", plaintext[i], ((i + 1) % 16) ? ' ' : '\n');
            }
    
    	    //Key Expansion
            expandKey(expandedKey, key, size, expandedKeySize);
            
//			  Jikalau mau print expandkey dari round awal hingga akhir
//            printf("\nExpanded Key (Format HEX):\n");
//            for (i = 0; i < expandedKeySize; i++)
//            {
//        	printf("%2.2x%c", expandedKey[i], ((i + 1) % 16) ? ' ' : '\n');
//    	    }
    
    	    printf("\nCipher Text (Format HEX):\n");
            for (i = 0; i < 16; i++)
            {
        	printf("%2.2x%c", ciphertext[i], ((i + 1) % 16) ? ' ' : '\n');
            }
              
   	    printf("\nCipher Text (Format Text):\n");
            for (i = 0; i < 16; i++)
            {
	    	printf("%c", ciphertext[i]);
            }
            printf("\n\n");
   			system("pause");
   			system("cls");
 	    break;
 	case 2:
//	 		// Meminta pengguna untuk memasukkan kunci dan ciphertext
//	 	printf("\nSegera Hadir dalam waktu dekat");
//	 	printf("\nTekan Enter untuk melanjutkan...");
//        getchar();
//        system("pause");
//        system("cls");
	    printf("\nMasukkan Cipher Key (16 karakter dalam format HEX):\n");
		fflush(stdin);
		for (i = 0; i < 16; i++)
		{
	    	scanf("%2x", &key[i]); // Menggunakan %2x untuk membaca input sebagai nilai HEX
		}
	
	    printf("\nMasukkan Cipher Text (16 karakter dalam format HEX):\n");
	    fflush(stdin);
	    for (i = 0; i < 16; i++)
	    {
	        scanf("%2x", &ciphertext[i]); // Menggunakan %2x untuk membaca input sebagai nilai HEX
	    }
	
	    // Melakukan dekripsi
	    aes_decrypt(ciphertext, decryptedtext, key, SIZE_16);
	  
		printf("\nDecrypted text:\n");
	    for (i = 0; i < 16; i++)
	    {
	        printf("%c", decryptedtext[i]);
	    }
	    printf("\n");
	    // Menampilkan hasil dekripsi
	    printf("\nDecrypted text (HEX format):\n");
	    for (i = 0; i < 16; i++)
	    {
	        printf("%2.2x%c", decryptedtext[i], ((i + 1) % 16) ? ' ' : '\n');
	    }
	    break;
	case 3:
        	return SUCCESS;
    	}
    }
    return 0;
}
