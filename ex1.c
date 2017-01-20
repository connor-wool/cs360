int *FP;

main (int argc, char *argv[], char *env[])
{
	int a,b,c;
	printf("enter main\n");
	a=1; b=2; c=3;
	A(a,b);
	printf("exit main\n");
}

int A(int x, int y)
{
	int d,e,f;
	printf("enter A\n");
	d=4; e=5; f=6;
	B(d,e);
	printf("exit A\n");
}

int B(int x, int y)
{
	int y,v,w;
	printf("enter B\n");
	u=7; v=8; w=9;
	asm("mov1 %ebp, FP");
	//insert code
	
	printf("exit B\n");
}
