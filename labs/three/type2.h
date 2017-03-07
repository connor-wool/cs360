#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>


#define STR_LEN 256
#define MAX_TOK 64
#define DEBUG 0 

char *path_tokens[MAX_TOK];	//hold tokens with paths
//char line[STR_LEN];		//hold user input line
//char *tokens[MAX_TOK];		//hold user input tokens (made from line)
char *sleepy = " (-.-) Zzz...";
char *work_msg = "ᕦ(ò_óˇ)ᕤ";
char *i_die = "\\(X_X)/";

typedef struct token_box {
	int n_tokens;
	char *tokens[MAX_TOK];
} TOKBOX;

void nprintc(char c, int n, int newline){
	for(int i = 0; i < n; i++){
		printf("%c",c); }
	if(newline){
		printf("\n"); }
}

char * makestring(char *s){
	int l = strlen(s);
	char *strtmp = (char*) malloc( l*sizeof(char) + 1);
	strcpy(strtmp, s);
	return strtmp;
}

void remove_from_tokbox(TOKBOX *tb, int index){
        int n = tb->n_tokens;
        if(index < n){
                free(tb->tokens[index]);
        }
        int i = index;
        while(i < n){
                tb->tokens[i] = makestring(tb->tokens[i+1]);
                i++;
        }
        tb->tokens[i] = 0;
        tb->n_tokens -= 1;
}



