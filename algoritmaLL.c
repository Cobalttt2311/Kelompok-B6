#include "linkedlist.h"
#include "AES_Encryption.h"

address nodetipuan(address baru, int n) {
    baru = (address)malloc(sizeof(ElmtList));
    info(baru) = sbox[fibonaci(n)][fibonaci(n + 1)];
    next(baru) = prev(baru) = Nil;
    return baru;
}

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

//fungsi fibonaci
int fibonaci(int n) {
    if (n <= 2) {
        return 1;
    } else {
        return fibonaci(n - 2) + fibonaci(n - 1);
    }
}
