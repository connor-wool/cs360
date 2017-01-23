#include <stdio.h>

int *FP;
int *main_frame_ptr;

int A(int x, int y);
int B(int x, int y);

int main (int argc, char *argv[], char *env[])
{
	asm("movl %ebp, main_frame_ptr");
	int a,b,c;
	printf("enter main\n");
	a=1; b=2; c=3;
	printf("&a=%x &b=%x &c=%x\n",&a,&b,&c);
	printf("&FP=%x\n", &FP);
	A(a,b);
	printf("exit main\n");
}

int A(int x, int y)
{
	int d,e,f;
	printf("enter A!\n");	
	printf("&d=%x &e=%x &f=%x\n",&d,&e,&f);
	d=4; e=5; f=6;
	B(d,e);
	printf("exit A\n");
}

int B(int x, int y)
{
	int u,v,w;
	printf("enter B!\n");	
	printf("&u=%x &v=%x &w=%x\n",&u,&v,&w);
	u=7; v=8; w=9;
	
	//this asm call loads stack pointer into global "FP"
	asm("movl %ebp, FP");

	/*****
	"By convention, the CPU's FP = 0 when crt0.o is entered
		from the OS kernel. So the stack frame link
		list ends with a 0. When a function returns,
		its stack frame is deallocated and the stack
		shrinks back" - MTX Design, pg. 27
	*****/	
	
	//write code to print the stack frame linked list here:
	printf("\nprint the stack frame linked list:\n");
	while(FP != 0)
	{
		printf("%x -> ", FP);
		FP = *FP;
	}	
	printf("\n");	

	//print in HEX the address and contents of the stack from
	//FP to the stack frame of main()
	
	//reset the value of stack frame pointer to FP	
	asm("movl %esp, FP");

	printf("\nprint stack address and contents:\n");
	while(FP < main_frame_ptr)
	{
		printf("addr: %x\tcont: %x\n",FP,*FP);
		FP += 1;
	}

	printf("exit B\n");
}
