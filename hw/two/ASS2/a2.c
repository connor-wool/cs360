#include "type.h"

void rprintbase(u32 x, int BASE)
{
	if(x == 0){ return; } 
        char temp = HEXTABLE[x % BASE];
        rprintbase(x / BASE, BASE);
        putchar(temp);
}

void printx(u32 x)
{
	if(x == 0){ putchar('0'); return; }
	rprintbase(x,16);	
}

void printo(u32 x)
{
	if(x == 0){ putchar('0'); return;}
	rprintbase(x,8);
}

void printd(int x)
{
	if(x == 0){ putchar('0'); return; }
	if(x < 0){
		putchar('-');
		rprintbase(x*-1, 10);
	}		
	else{
		rprintbase(x,10);
	}
}

void printu(u32 x)
{
	if(x == 0){ putchar('0'); return; }	
	rprintbase(x,10);
}

//use putchar(char c) to write a string-print function
void prints(char *s)
{
	while(*s){ putchar(*s++); }
}

void myprintf(char *format, ...)
{
	char *cp = format;
	int *ip = &format+1;
	while(*cp)
	{
		if(*cp == '%'){
			cp++;
			if(*cp == 'u'){
				printu(*ip++);	
			}
			else if(*cp == 'd'){
				printd(*ip++);
			}
			else if(*cp == 'c'){
				putchar(*ip++);
			}
			else if(*cp == 's'){
				prints(*ip++);
			}
			else if(*cp == 'o'){
				printo(*ip++);
			}
			else if(*cp == 'x'){
				printx(*ip++);
			}
			cp++;
		}
		else{
			putchar(*cp++);
		}
	}	
}

int enqueue(NODE **queue, NODE *p)
{
	//enter p into q by priority
	//handle edge case where queue is empty
	if(*queue == 0){
		*queue = p;
	}
	else{
		NODE *current = *queue;
		NODE *previous = *queue;
		while(current->next != 0 && p->priority >= current->priority){
			previous = current;
			current++;
		}
		p->next = current;
		previous->next = p;
	}
}

NODE *dequeue(NODE **queue)
{
	//delete first node from queue, and return node
	//with highest priority (if one exists)
	if(*queue == 0)
	{
		return (NODE*)0;
	}

	NODE *current = *queue;
	*queue = current->next;
	return current;
}

NODE *make_random_node(int idNum)
{
	srand(time(NULL));
	int r = rand() % 10;
	NODE *p = (NODE*)malloc(sizeof(NODE));
	p->next = 0;
	p->name[0] = 'n';
	p->name[1] = 'o';
	p->priority = r;
	return p;
}

void print_node(NODE *p)
{
	myprintf("printing node!\n");
	myprintf("[name: %s priority: %d] -> ",p->name,p->priority);
}

void print_queue(NODE **queue)
{
	myprintf("printing node queue!\n");
	NODE *current = *queue;
	while(current)
	{
		print_node(current);
		current = current->next;
	}
	myprintf("\n");
}

int main(int argc, char *argv[], char *env[])
{
	printCredits();
	myprintf("\n\n--------BEGIN SECTION 1--------\n");
	myprintf("--------ARGC--------\n");
	myprintf("argc: %d\n", argc);

	myprintf("--------ARGV--------\n");
	int i = 0;
	while(argv[i])
	{
		myprintf("argv%d: %s\n",i,argv[i]);
		i++;
	}
	myprintf("--------(BRACE YOURSELVES!)--------\n");
	myprintf("--------ENV--------\n");
	i = 0;
	while(env[i])
	{
		myprintf("env%d: %s\n",i,env[i]);
		i++;
	}

	myprintf("\n\n--------SECTION 1 COMPLETE--------\n");
	myprintf("--------BEGIN NODE QUEUE SECTION--------\n");
	/**************
	myprintf("making random node!\n");
	NODE *p = make_random_node(1);
	print_node(p);
	myprintf("preparing enqueue!\n");
	enqueue(&readyqueue, p);
	print_queue(&readyqueue);
	**************/

}
