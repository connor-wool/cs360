#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define N 10

typedef struct node{
	struct node *next;
	char name[64];
	int id;
}NODE;

char name[64];
NODE *mylist; //pointer to a single node object
NODE node[N]; //array that contains N node objects

int main()
{
	//enter main program
	int i;
	NODE *p;
	
	for (i = 0; i < N; i++)
	{
		p = &node[1];
		sprintf(name, "%s%d", "node", i); //node0, node1, node2,...
		strcpy(p->name, name);
		p->id = 1;
		p->next = p+1; //node[i].next = &node[i+1]
	}
	node[N-1].next = 0;
	mylist = &node[0];

	printlist("mylist", mylist);
}

/*****************
int printlist(char *name, NODE *p)
{
	printf("%s - ", name);
	while(p) {
		printf("[%s %d] ->", p->name, p->id);
		p = p->next;
	}
	printf("NULL\n");
}
********************/
