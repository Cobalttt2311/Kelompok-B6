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
            // Handle input untuk Cipher Key
	    while (1) {
	        printf("\nMasukkan Cipher Key (maksimal 16 karakter): ");
	        fflush(stdin);
	        if (fgets(temp, sizeof(temp), stdin) != NULL) {
	            temp[strcspn(temp, "\n")] = '\0'; // Menghapus karakter newline
	            if (strlen(temp) <= MAX_LEN && strlen(temp) > 0) {
	                strncpy(key, temp, MAX_LEN); // Salin ke buffer dengan panjang yang sesuai
	                key[MAX_LEN] = '\0'; // Pastikan null-terminated
	                break;
	            } else {
	                printf("Input terlalu panjang. Maksimal %d karakter. Silakan coba lagi.\n", MAX_LEN);
	            }
	        } 
	    }

    	    // Handle input untuk Plain Text
	    while (1) {
	        printf("\nMasukkan Plain Text (maksimal 16 karakter): ");
	        fflush(stdin);
	        if (fgets(temp, sizeof(temp), stdin) != NULL) {
	            temp[strcspn(temp, "\n")] = '\0'; // Menghapus karakter newline
	            if (strlen(temp) <= MAX_LEN && strlen(temp) > 0) {
	                strncpy(plaintext, temp, MAX_LEN); // Salin ke buffer dengan panjang yang sesuai
	                plaintext[MAX_LEN] = '\0'; // Pastikan null-terminated
	                break;
	            } else {
	                printf("Input terlalu panjang. Maksimal %d karakter. Silakan coba lagi.\n", MAX_LEN);
	            }
	        } 
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
		
            for (i = 0; i < 16; i++)
            {
                insert(&first, ciphertext[i]);
            }
            sisipkantipuan(first);
            printLL(first);
            acak(first);
            putar(&first, 6, true);
            for (i = 0; i < 22; i++)
            {
                ciphertext[i] = pindahkearray(&first);
            }
            printf("\n");
            printf("Cipher text setelah dimodifikasi (Format HEX):");
            for (i = 0; i < 22; i++)
            {
                printf("%2.2x%c", ciphertext[i], ((i + 1) % 16) ? ' ' : '\n');
            }
            //   Jikalau mau print expandkey dari round awal hingga akhir
            //   printf("\nExpanded Key (Format HEX):\n");
            //   for (i = 0; i < expandedKeySize; i++){
            //   printf("%2.2x%c", expandedKey[i], ((i + 1) % 16) ? ' ' : '\n');
            //   }

            printf("\n\n");
            system("pause");
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
