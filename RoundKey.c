#include <stdio.h>
#include <string.h>

void xor_encrypt_decrypt(char *data, const char *key, int data_len) {
    int key_len = strlen(key);
    int i;
    for (i = 0; i < data_len; i++) {
        data[i] ^= key[i % key_len];
    }
}

int main() {
    char data[100]; 
    char key[100];  
    int data_len, key_len;
	int i;
	
    printf("Enter the data to be encrypted/decrypted: ");
    scanf("%[^\n]s", data); 

    printf("Enter the key: ");
    scanf(" %[^\n]s", key); 

    data_len = strlen(data);
    key_len = strlen(key);

    printf("Original data: %s\n", data);

    xor_encrypt_decrypt(data, key, data_len);
    printf("Encrypted/Decrypted data: ");
    
    for (i = 0; i < data_len; i++) {
        printf("%02x", (unsigned char)data[i]);
    }
    printf("\n");

    // Decrypt the data back to original
    xor_encrypt_decrypt(data, key, data_len);
    printf("Decrypted data: %s\n", data);

    return 0;
}
