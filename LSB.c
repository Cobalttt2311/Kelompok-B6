// Fungsi untuk meneyembunyikan pesan dalam gambar metode LSB
void hide_message(unsigned char* image_data, int image_size, const unsigned char* message, int message_length) { 
    int i;
    for (i = 0; i < image_size; ++i) {
        int bit_position = i % 8;
        //jika posisi bit sama dengan 0, berari sudah ke karakter terbaru, karena ada 8 bit, direpresentasikan dalam rang 0 - 7
        if (bit_position == 0) {
        	// jika panjang pesan lebih dari 0, maksudnya masih ada pesan tersisa yang ingin disisipkan maka:
            if (message_length > 0) {
            	// panjang pesan dikurangi dengan satu, karena satu karakter telah disisipkan, sisanya maka akan diproses kembali hingga seluruh pesan habis disisipkan
                message_length--;
            }
        }
        // jika panjang pesan lebih dari 0, maksudnya masih ada pesan yang ingin disisipkan, maka :
        if (message_length > 0) {
        	// Sisipkan LSB dari pesan yang ingin disisipkan ke dalam LSB bagian pixel gambar
            image_data[i] = (image_data[i] & ~1) | ((message[message_length - 1] >> (7 - bit_position)) & 1);
        }
    }
}



void decrypt_message(const unsigned char* image_data, int image_size, int message_size, char* decrypted_message) {
    int i = 0, j, k;
    int count = 0;

    for ( j = 0; j < message_size; ++j) {
        unsigned char byte = 0;
        for (k = 0; k < 8; ++k) {
            int bit = read_lsb(image_data[i]);
            byte |= (bit << (7 - k));
            ++i;
            if (++count >= message_size * 8) {
                break;
            }
        }
        decrypted_message[j] = byte;
        if (count >= message_size * 8) {
            break;
        }
    }
    decrypted_message[message_size - 1] = '\0'; // Pastikan string terakhir diakhiri dengan null terminator
}
