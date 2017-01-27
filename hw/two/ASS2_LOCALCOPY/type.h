#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX_PRIORITY 10
typedef unsigned int u32;

typedef struct node{
	struct node *next;
	char name[64];
	int priority;
}NODE;

NODE *readyqueue;

char *HEXTABLE = "0123456789BCDEF";

void printCredits()
{
	myprintf("\n\nAUTHOR:CONNOR WOOL | ID# 11253438\n");
}


