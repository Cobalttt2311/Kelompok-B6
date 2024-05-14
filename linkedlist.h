#ifndef LINKEDLIST_H
#define LINKEDLIST_H
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#define info(P) (P)->info
#define next(P) (P)->next
#define prev(P) (P)->prev
#define Nil NULL

typedef char infotype;
typedef struct tElmtlist *address;
typedef struct tElmtlist {
	address prev;
    infotype info;
    address next;
} ElmtList;

#endif
