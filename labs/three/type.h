#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define STR_LEN 256
#define MAX_TOK 64
#define DEBUGGING 1 

char *path_tokens[MAX_TOK];	//hold tokens with paths
char line[STR_LEN];		//hold user input line
char *tokens[MAX_TOK];		//hold user input tokens (made from line)

void nprintc(char c, int n, int newline){
	for(int i = 0; i < n; i++){
		printf("%c",c); }
	if(newline){
		printf("\n"); }
}




