#include <stdio.h>

int main(int argc, char *argv[], char *env[]){
	
	char *arglist[] = {"ls","-l",0};
	fprintf(stderr, "about to call execvp!\n");
	execvp(arglist[0],arglist);
	printf("****** ls is done!\n");
}
