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
