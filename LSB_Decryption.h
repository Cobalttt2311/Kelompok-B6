#ifndef LSB_DECRYPTION_H
#define LSB_DECRYPTION_H

// Fungsi untuk mendekripsi pesan yang disembunyikan dalam gambar menggunakan metode LSB
void decrypt_message(const unsigned char* image_data, int image_size, int message_size, char* decrypted_message);

#endif
