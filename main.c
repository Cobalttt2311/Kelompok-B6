#define STB_IMAGE_IMPLEMENTATION
#define STB_IMAGE_WRITE_IMPLEMENTATION
#define MAX_LEN 16
#include <stdio.h> 
#include <stdlib.h> 
#include <string.h>
#include <ctype.h>
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
#include "stb_image.h"
#include "stb_image_write.h"
#include "LSB_Encryption.h"
#include "LSB_Decryption.h"
#include "ReadLSB.h"
#include "ReverseString.h"
#include "linkedlist.h"
#include "alanna.h"
#include "daffa.h"
#include "erina.h"
#include "nalen.h"
#include "radja.h"

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

void clear_list(address *first) {
    address current = *first;
    address next;
    
    while (current != Nil) {
        next = current->next;
        free(current);
        current = next;
    }
    
    *first = Nil;
}

void clearScreen() {
    system(CLEAR_SCREEN);
}

void remove_spaces(char *input) {
    char *i = input, *j = input;
    while (*j != 0) {
        *i = *j++;
        if (*i != ' ') {
            i++;
        }
    }
    *i = 0;
}

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
	
    //expanded keySize
    int expandedKeySize = 176;

    //expanded key
    unsigned char expandedKey[expandedKeySize];
	
    //cipher key
    unsigned char key[17];

    //cipher key size
    enum keySize size = SIZE_16;

    //plaintext
    unsigned char plaintext[17]; 
    //ciphertext
    unsigned char ciphertext[16];

    //decrypted text
    unsigned char decryptedtext[16];

    clear_list(&first);

    while(1) 
    { 
	clearScreen();
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
            fflush(stdin); // Clear the input buffer
            printf("\nTekan Enter untuk melanjutkan...");
            getchar();
            system("cls");
            continue;
    }
            
    printf("=============================================================\n");
    switch (var) {
        case 1:
            clearScreen();
    		printf("=============================================================\n");
       		printf("|                      AES & LSB Kelompok 6                 |\n");
        	printf("=============================================================\n");
        	printf("|                         ENKRIPSI                          |\n");
        	printf("-------------------------------------------------------------\n");
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
	                printf("Input Tidak Tepat. Maksimal %d karakter. Minimal 1 karakter. Silakan coba lagi.\n", MAX_LEN);
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
	                printf("Input Tidak Tepat. Maksimal %d karakter. Minimal 1 karakter. Silakan coba lagi.\n", MAX_LEN);
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
		
            printf("\n===============================================================\n\n");
	    for (i = 0; i < 16; i++) {
                insert(&first, ciphertext[i]);
            }
                
            sisipkantipuan(first);
            acak(first);
            putar(&first, 6, true);
            printf("\n================= HASIL PENERAPAN LINKED LIST =================\n");
            printf("  Setelah dilakukan Penambahan Node Tipuan, Acak dan Pemutaran \n");
            printLL(first);
            for (i = 0; i < 22; i++)
            {
                ciphertext[i] = pindahkearray(&first);
            }
            printf("\n");
            printf("Cipher text setelah dimodifikasi (Format HEX):\n");
            for (i = 0; i < 22; i++)
            {
                printf("%2.2x ", ciphertext[i]);
            }
            //   Jikalau mau print expandkey dari round awal hingga akhir
            //   printf("\nExpanded Key (Format HEX):\n");
            //   for (i = 0; i < expandedKeySize; i++){
            //   printf("%2.2x%c", expandedKey[i], ((i + 1) % 16) ? ' ' : '\n');
            //   }

            printf("\n\n");
            system("pause");
	    while (1)
            {
            	//Handle input untuk melanjutkan ke metode LSB
                printf("\nApakah anda mau menyisipkan pesan rahasia ke gambar menggunakan metode LSB? Masukkan Y atau N: ");
                scanf(" %c", &masukan);
                masukan = toupper(masukan); // Ubah huruf ke uppercase
                if (masukan == 'N')
                {
                    printf("Anda memilih untuk tidak menyisipkan pesan ke gambar.\n");
                    break; // Keluar dari switch
                }
                else if (masukan == 'Y')
                {
                	clearScreen();
                    	printf("=============================================================\n");
			printf("|                      AES & LSB Kelompok 6                 |\n");
			printf("=============================================================\n");
		    	printf("|      SISIPKAN PESAN KE GAMBAR MENGGUNAKAN METODE LSB      |\n");
			printf("-------------------------------------------------------------\n");
                        printf("Masukkan nama file gambar PNG: ");
                    	scanf("%s", filename);

                    image_data = stbi_load(filename, &width, &height, &channels, 0);

                    if (!image_data)
                    {
                        printf("Gagal membuka file gambar.\n");
                        system("pause");
                        break;
                    }

                    {
                        char message[45]; // Ukuran pesan adalah 16 karakter, ditambah satu untuk karakter null
                        for (i = 0; i < 22; i++)
                        {
                            sprintf(message + i * 2, "%02X", ciphertext[i]);
                        }
                        message[44] = '\0'; // Menambahkan null terminator pada akhir pesan

                        // Menghitung ukuran pesan
                        int message_size = strlen(message) + 1; // Menambahkan 1 untuk karakter nul akhir

                        // Menyembunyikan pesan ke dalam gambar
                        hide_message(image_data, width * height * channels, (unsigned char *)message, message_size);
                        // Simpan gambar yang telah dimodifikasi
                        char output_filename[100];
                        printf("Masukkan nama file untuk menyimpan gambar yang dimodifikasi: ");
                        scanf("%s", output_filename);
                        if (!strstr(output_filename, "."))
                        {
                            strcat(output_filename, ".png"); // Tambahkan ekstensi .png jika belum ada
                        }
                        printf("Nama file output: %s\n", output_filename);

                        if (!stbi_write_png(output_filename, width, height, channels, image_data, width * channels))
                        {
                            printf("Gagal menyimpan gambar.\n");
                            return 1;
                        }

                        printf("Pesan telah disisipkan ke dalam gambar.\n");
                    }

                    // Membebaskan memori yang dialokasikan untuk gambar
                    stbi_image_free(image_data);
                    break;
                }
                else
                {
                    printf("Input tidak valid. Harap masukkan Y atau N.\n");
                }
            }
 	    break;
 	case 2:
		clearScreen();
                clear_list(&firstDec);
		printf("=============================================================\n");
		printf("|                      AES & LSB Kelompok 6                 |\n");
		printf("=============================================================\n");
		printf("|                         DEKRIPSI                          |\n");
		printf("-------------------------------------------------------------\n");
		
                while (1) {
			 printf("\nMasukkan Cipher Key (maksimal 16 karakter dalam format HEX): \n");
			 fflush(stdin);
			 if (fgets(temp, sizeof(temp), stdin) != NULL) {
			        temp[strcspn(temp, "\n")] = '\0'; // Menghapus karakter newline
			        remove_spaces(temp); // Menghapus spasi
			
			        if (strlen(temp) == 32) { // 16 karakter HEX (32 digit tanpa spasi)
			        for (i = 0; i < MAX_LEN; i++) {
			        sscanf(&temp[i * 2], "%2hhx", &key[i]);
			         }
			        break;
				} else {
				printf("Error: Cipher Key harus tepat 16 karakter HEX.\n");
				}
			}
		 }
		
	    	// Loop untuk validasi Cipher Text
		 while (1) {
			printf("\nMasukkan Cipher Text (maksimal 22 karakter dalam format HEX): \n");
			fflush(stdin);
			if (fgets(temp, sizeof(temp), stdin) != NULL) {
			        temp[strcspn(temp, "\n")] = '\0'; // Menghapus karakter newline
			        remove_spaces(temp); // Menghapus spasi
			
			        if (strlen(temp) == 44) { // 22 karakter HEX (44 digit tanpa spasi)
			        for (i = 0; i < 44; i++) {
			        sscanf(&temp[i * 2], "%2hhx", &ciphertext[i]);
			        }
			        break;
			        } else {
			        printf("Error: Cipher Text harus tepat 22 karakter HEX.\n");
			        }
			}
		}

	            for (i = 0; i < 22; i++)
	            {
	                insert(&firstDec, ciphertext[i]);
	            }
	            printLL(firstDec);
	            putar(&firstDec, 6, false);
	            acak(firstDec);
	            hapustipuan(firstDec);
	            for (i = 0; i < 16; i++)
	            {
	                ciphertext[i] = pindahkearray(&firstDec);
	            }
		
	            printf("\n======================= HASIL DEKRIPSI =======================\n");
	            printf("\nCipher Text (Format Text):\n");
	            for (i = 0; i < 16; i++)
	            {
	                printf("%c", ciphertext[i]);
	            }
	
	            aes_decrypt(ciphertext, decryptedtext, key, SIZE_16);
	            printf("\nDecrypted text:\n");
	            for (i = 0; i < 16; i++)
	            {
	                printf("%c", decryptedtext[i]);
	            }
	            printf("\n");
	            printf("\nDecrypted text (HEX format):\n");
	            for (i = 0; i < 16; i++)
	            {
	                printf("%2.2x%c", decryptedtext[i], ((i + 1) % 16) ? ' ' : '\n');
	            }
	            system("pause");
	            break;	
	
	case 3:
		clearScreen();
        	// Enkripsi pesan
                printf("Masukkan nama file gambar PNG: ");
                scanf("%s", filename);

                image_data = stbi_load(filename, &width, &height, &channels, 0);

                if (!image_data) {
                    printf("Gagal membuka file gambar.\n");
                    break;
                }

                {
                    char message[51];
                    printf("Masukkan pesan yang akan disisipkan: ");
                    getchar(); // membersihkan newline yang tersisa dalam input buffer
                    fgets(message, sizeof(message), stdin);
                    message[strcspn(message, "\n")] = '\0'; // menghapus newline yang ditambahkan oleh fgets

                    int message_size = strlen(message) + 1; // Menambahkan 1 untuk karakter nul akhir

                    // Menyembunyikan pesan ke dalam gambar
                    hide_message(image_data, width * height * channels, (unsigned char*)message, message_size);
                    // Simpan gambar yang telah dimodifikasi
                    char output_filename[100];
                    printf("Masukkan nama file untuk menyimpan gambar yang dimodifikasi: ");
                    scanf("%s", output_filename);
                    if (!strstr(output_filename, ".")) {
                        strcat(output_filename, ".png"); // Tambahkan ekstensi .png jika belum ada
                    }
                    printf("Nama file output: %s\n", output_filename);

                    if (!stbi_write_png(output_filename, width, height, channels, image_data, width * channels)) {
                        printf("Gagal menyimpan gambar.\n");
                        return 1;
                    }

                    printf("Pesan telah disisipkan ke dalam gambar.\n");
                    system("pause");
                }

                // Membebaskan memori yang dialokasikan untuk gambar
                stbi_image_free(image_data);

                break;
	    case 4:
		    clearScreen();
            // Dekripsi pesan
            printf("Masukkan nama file gambar PNG: ");
            scanf("%s", filename);

            image_data = stbi_load(filename, &width, &height, &channels, 0);

            if (!image_data)
            {
                printf("Gagal membuka file gambar.\n");
		system("pause");
                break;
            }

            {
                // Membaca pesan tersembunyi dari gambar yang dimodifikasi
                char *decrypted_message = (char *)malloc(45);
                int ukuran = width * height * channels;
                decrypt_message(image_data, ukuran, 45, decrypted_message);

                // Membalikkan string yang telah didekripsi
                reverse_string(decrypted_message);

                // Menampilkan pesan tersembunyi yang telah dibalik
                printf("Pesan tersembunyi: %s\n", decrypted_message);

                // Membebaskan memori yang dialokasikan untuk pesan terdekripsi
                free(decrypted_message);
            }

            // Membebaskan memori yang dialokasikan untuk gambar
            stbi_image_free(image_data);
	    system("pause");
            break;
        case 5:
        	printf("\nTerimakasih");
        	return 0;
    	}
    }
}
