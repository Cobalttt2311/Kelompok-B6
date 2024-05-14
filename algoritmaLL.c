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
    address kiri, kanan, tengah, lastNode;
    
    lastNode = first;
    while (next(lastNode) != NULL) {
        lastNode = next(lastNode);
    }
    next(lastNode) = first;
    prev(first) = lastNode;

    tengah = first;
    for (j = 1; j <= 21; j++) {
        if (j % 2 != 0) {
            kiri = prev(tengah);
            kanan = next(tengah);

            if (kiri != NULL && kanan != NULL) {
                infotype temp = info(tengah);
                info(tengah) = info(kanan);
                info(kanan) = temp;
            }
        }
        tengah = next(tengah);
    }
}
