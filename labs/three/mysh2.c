#include "type2.h"

//tokenize all paths
int tok_paths(){
	printf("--> Tokenize path string\n");

	//set up variables, copy path string from ENV
	char *tok_p, path_string[STR_LEN];
	int tok_itr = 0;
	strcpy(path_string, getenv("PATH"));

	if(DEBUG) { printf("--> $PATH=%s\n",path_string); }

	//pass string to tokenize, make first call
	tok_p = strtok((char*) path_string, (const char*) ":");

	//runs loop while token is not null
	while(tok_p){
		path_tokens[tok_itr++] = makestring(tok_p);
		tok_p = strtok(0, (const char*) ":");
	}
	//zero out the last array position
	path_tokens[tok_itr] = 0;
}

//run initialization commands
int init(){
	//print opening section
	nprintc('=',50,1);
	printf("\t\tCONNOR'S COOL SHELL V.2\n");
	nprintc('=',50,1);
	printf("--> Running init process...\n");
	
	//place init functions here
	tok_paths();
	
	printf("--> Init process finished.\n");
}

//get a line of input from user, allocate space, return pointer
char* get_input(){
	char cwdtmp[STR_LEN], hosttmp[STR_LEN], input_line[STR_LEN];
	getcwd(cwdtmp, STR_LEN);
	gethostname(hosttmp, STR_LEN);
	printf("%s:%s$ ", hosttmp, cwdtmp);
	fgets(input_line, STR_LEN, stdin);
	input_line[strlen(input_line) -1] = 0; //remove newline
	return makestring(input_line);	
}

//process a string by whitespace into tokens in a box
TOKBOX *process_string(char *s){
	//make new tokenbox in heap, and make copy of string
	TOKBOX *tbox_p = (TOKBOX*)malloc(sizeof(TOKBOX));
	char *copystring = makestring(s);

	int tok_num = 0; tbox_p->n_tokens = 0;
	char *tok_p = strtok((char *)copystring, (const char*) " ");
	while(tok_p){ //run loop as long as tokens are not null
		tbox_p->tokens[tok_num] = makestring(tok_p);
		tok_p = strtok(0, (const char*) " ");
		tok_num++;
		tbox_p->n_tokens = tok_num;
	}
	tbox_p->tokens[tok_num] = 0; //terminate array with 0
	return tbox_p;
}

//check for cd command
int check_cd(TOKBOX *tb){
	if(strcmp(tb->tokens[0], "cd") == 0){
		if(tb->n_tokens > 1){
			chdir((const char*) tb->tokens[1]);
		}
		else{
			chdir((const char*) getenv((const char*)"HOME"));
		}
		return 1;
	}
	return 0;
}

//check for exit command
int check_exit(TOKBOX *tb){
	if(strcmp(tb->tokens[0], "exit") == 0){
		exit(0); return 1;
	}
	return 0;
}

//check and redirect IO if needed
int redirect_io(TOKBOX *tb){
	int infile_index = 0;
	int outfile_index = 0;
	int i = 0;
	while(i < tb->n_tokens){
		if(strcmp(tb->tokens[i], "<") == 0){
			infile_index = i;
		}
		if(strcmp(tb->tokens[i], ">") == 0){
			outfile_index = i;
		}
		if(strcmp(tb->tokens[i], ">>") == 0){
			outfile_index = i;
		}
		i++;
	}
	
	if(infile_index > 0){
		close(0);
		fopen(tb->tokens[infile_index+1], "r");
	}
	if(outfile_index > 0){
		close(1);
		if(strcmp(tb->tokens[outfile_index],">")==0){
			fopen(tb->tokens[outfile_index+1],"w");
		}
		else{
			fopen(tb->tokens[outfile_index+1],"a");
		}
	}

}

int handle_fork(TOKBOX *tb){
	int pid, status, i;
	char cmd_path[STR_LEN];

	if(DEBUG){
		printf("Parent(%x) forks a child\n", getpid());
	}

	pid = fork();

	//check what process we are
	if(pid){
		if(DEBUG){
		printf("Parent(%x) waits for child to die\n",getpid());
		}

		wait(&status);
		
		if(DEBUG){
		printf("Parent(%x) wakes! status: %x\n",getpid(),status);
		}
	}	
	else{ //we are the child now
		
		if(DEBUG){
		printf("Child(%x) starts work %s\n",getpid(),work_msg);
		}

		redirect_io(tb);
	
		cmd_path[0] = 0;

		strcat(cmd_path, path_tokens[0]);
		if(cmd_path[strlen(cmd_path)-1] != '/'){
			strcat(cmd_path, "/");
		}
		strcat(cmd_path, tb->tokens[0]);
		
		i = 0;
		while(execve(cmd_path,tb->tokens,0) && *path_tokens[i]){
			i++;
			memset(cmd_path, 0, STR_LEN);
			strcat(cmd_path, path_tokens[i]);
			if(cmd_path[strlen(cmd_path)-1] != '/'){
				strcat(cmd_path, "/");
			}
			strcat(cmd_path, tb->tokens[0]);
		}
		fprintf(stderr,"no command `%s` found\n",tb->tokens[0]);
		exit(0);
	}
}

int main(int argc, char *argv[], char *env[]){
	init();
	while(1){
		char *input = get_input();
		TOKBOX *tb = process_string(input);
		if(check_cd(tb)) { continue; }
		if(check_exit(tb)) { break; }
		handle_fork(tb);	
	}
}
