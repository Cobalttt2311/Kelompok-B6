#include "linkedlist.h"
#include "AES_Encryption.h"


void sisipkantipuan(address first) {
    int j;
    address temp;
    address tipuan;
    for (j = 6; j >= 1; j--) {
        temp = nodesebelumpalsu(fibonaci(j), first);
        tipuan = nodetipuan(tipuan, j);
        next(tipuan) = next(temp);
        prev(tipuan) = temp;
        if (next(tipuan) != Nil) {
            prev(next(tipuan)) = tipuan;
        }
        next(temp) = tipuan;
    }
}


void hapustipuan(address first) {
    int j;
    address kiri;
    address tipuan;
    for (j = 1; j <= 6; j++) {
        kiri = nodesebelumpalsu(fibonaci(j), first);
        tipuan = next(kiri);
        next(kiri) = next(next(kiri));
        if (next(kiri) != Nil) {
            prev(next(kiri)) = kiri;
        }
        free(tipuan);
    }
}

void putar(address *first,char key,bool reverse){
	int putaran,i;
	if(reverse){
		for(i = 0 ; i < key ; i++){
			*first = prev(*first);
		}
	}else{
		for(i = 0 ; i < key ; i++){
			*first = next(*first);
		}	
	}

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

void insert(address *first, infotype isi) {
    address baru = (address)malloc(sizeof(ElmtList));
    if (baru == Nil) {
        printf("Alokasi gagal");
    } else {
        info(baru) = isi;
        next(baru) = Nil;
        prev(baru) = Nil;
        if (*first == Nil) {
            *first = baru;
            next(baru) = baru;
            prev(baru) = baru;
        } else {
            address temp = *first;
            while (next(temp) != *first) {
                temp = next(temp);
            }
            next(temp) = baru;
            prev(baru) = temp;
            next(baru) = *first;
            prev(*first) = baru;
        }
    }
}

infotype pindahkearray(address *first) {
    address hapus = *first;
    *first = next(*first);
    next(hapus) = Nil;
	prev(hapus) = Nil;
    return info(hapus);
	free(hapus);
}
