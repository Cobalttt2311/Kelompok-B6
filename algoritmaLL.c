#include "linkedlist.h"
#include "AES_Encryption.h"

address nodesebelumpalsu(int fibo, address first) {
    address cari = first;
    int j;
    for (j = 0; j < fibo; j++) {
        cari = next(cari);
    }
    return cari;
}

void printLL(address first) {
    address head = first;
    printf("\nPrint Berdasarkan Linked List : \n");
    while (head != Nil) {
        printf("%c", info(head));
        head = next(head);
    }
    printf("\n");
}

//doubly linked list circular
void acak(address first) {
    int j;
    address kiri, kanan;

    kiri = first;
    for (j = 0; j <= 21; j++) {
        if (j % 2 != 0) {
            kanan = next(kiri);
        
            if (kanan != NULL) {
                infotype temp = info(kiri);
                info(kiri) = info(kanan);
                info(kanan) = temp;
            }
        }
        kiri = next(kiri);
    }
}
