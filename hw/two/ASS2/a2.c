#include "type.h"
//written by connor wool
//January 27, 2017

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

//could this be done in 2 lines with printu?
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
	if(*queue == 0) //the queue is currently empty
	{
		*queue = p;
	}
	else //readyqueue is not empty, traverse based on priority
	{
		NODE *current = *queue;
		NODE *prev = current;
		if(p->priority > current->priority)
		{
			*queue = p;
			p->next = current;
		}
		else{	
			while(current != 0 && p->priority <= current->priority)
			{
				prev = current;
				current = current->next;
			}
			//now we're either at back of node to enqueue to
			prev->next = p;
			if(current != 0)
			{
				p->next = current;
			}
			else
			{
				p->next = 0;
			}
		}
	}
}

NODE *dequeue(NODE **queue)
{
	NODE *result = *queue;
	if(*queue){
		*queue = result->next;
	}
	return result;
}

void printqueue(NODE *queue)
{
	NODE *p = queue;
	myprintf("\n(PQ) Start queue print\n");
	myprintf("(PQ)  Start  address [%x]\n",p);
	while(p != 0)
	{
		myprintf("(PQ) Current address [%x] --\t",p);
		myprintf("[name: %s\tpri:%d] nxt(%x)->\n",p->name,p->priority,p->next);
		p = p->next;
	}
	myprintf("(PQ) Finish queue print\n\n");
}

int main(int argc, char *argv[], char *env[])
{
	printCredits();
	
	if(1){
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
		myprintf("----Max priority value set to %d----\n",MAX_PRIORITY);
		int z = 0;
		while(1){
			enqueue(&readyqueue, makenode(z));	
			printqueue(readyqueue);
			z++;
			myprintf("Press any key to generate next node!\n");
			myprintf("Press ^C to exit.\n");
			char c = getchar();
		}
	}
}
