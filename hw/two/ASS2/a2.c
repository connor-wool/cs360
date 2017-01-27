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

NODE *makenode(int index)
{
	NODE *p = (NODE*)malloc(sizeof(NODE));
	p->next = 0;
	p->priority = rand() % MAX_PRIORITY;	
	sprintf(p->name,"node%d",index);
	return p;
}

void enqueue(NODE **queue, NODE *p)
{
	//enter p into *q by priority
	myprintf("(ENQUEUE)+begin enqueue\n");
	if(*queue == 0) //the queue is currently empty
	{
		myprintf("(ENQUEUE) empty queue branch\n");
		*queue = p;
		myprintf("(ENQUEUE) front of queue [%x]\n",*queue);
		myprintf("(ENQUEUE) back of p [%x]\n",p->next);
	}
	else //readyqueue is not empty, traverse based on priority
	{
		myprintf("(ENQUEUE) insert into exitsting queue\n");

		NODE *current = *queue;
		NODE *prev = current;
		myprintf("(ENQUEUE) current[%x] previous[%x]\n",current,prev);
	
		if(p->priority > current->priority)
		{
			myprintf("(ENQUEUE) edge case: needs to be node 1\n");
			*queue = p;
			p->next = current;
			myprintf("(ENQUEUE) new front [%x]\n",*queue);
			myprintf("(ENQUEUE) new node 2 [%x]\n",current);
		}
		else{	
			while(current != 0 && p->priority <= current->priority)
			{
				prev = current;
				current = current->next;
			}
			//now we're either at back of node to enqueue to
			prev->next = p;
			myprintf("(ENQUEUE) prev->next now [%x]\n",prev->next);
			if(current != 0)
			{
				p->next = current;
			}
			else
			{
				p->next = 0;
			}
			myprintf("(ENQUEUE) p->next now [%x]\n",p->next);
		}
	}
	myprintf("(ENQUEUE)+finish enqueue\n\n");
}

void printqueue(NODE *queue)
{
	NODE *p = queue;
	myprintf("\n(PQ) Start queue print\n");
	myprintf("(PQ)  Start  address [%x]\n",p);
	while(p != 0)
	{
		myprintf("(PQ) Current address [%x] -- ",p);
		myprintf("[name:%s\tpri:%d] nxt(%x)->\n",p->name,p->priority,p->next);
		p = p->next;
	}
	myprintf("(PQ) Finish queue print\n\n");
}

int main(int argc, char *argv[], char *env[])
{
	printCredits();
	
	if(0){
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
	}
	if(1){
		myprintf("--------BEGIN NODE QUEUE SECTION--------\n");
		int z = 0;
		while(1){
			enqueue(&readyqueue, makenode(z));	
			printqueue(readyqueue);
			z++;
		}
	}
}
