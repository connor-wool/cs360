#include <stdio.h>
#include <stdlib.h>

/******************
creates the linked list from heap memory for the nodes
******************/

#define N 10

typedef struct node{
	struct node *next;
	char name[64];
	int id;
}NODE;

int main(int argc, char *argv[]){
	NODE *node = malloc(N*sizeof(NODE));
	

}
