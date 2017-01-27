#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef unsigned int u32;

typedef struct node{
	struct node *next;
	char name[64];
	int priority;
}NODE;

NODE *readyqueue = 0;

char *HEXTABLE = "0123456789ABCDEF";

void printCredits()
{
	myprintf("\n\nAUTHOR: CONNOR WOOL | ID# 11253438\n");	
}

