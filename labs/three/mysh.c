#include "type.h"

//0's memory for tokens and line
int mem_wipe(){
        memset(line, 0, STR_LEN);
        for(int z = 0; z < MAX_TOK; z++){
                memset(tokens[z], 0, STR_LEN); }
}

int tok_paths(){
	printf("--> Tokenizing path string\n");
	char *tok_ptr, all_paths[STR_LEN];
	strcpy(all_paths, getenv("PATH"));
	
	if(DEBUGGING){ printf("--> $PATH= '%s'\n",all_paths); }

	int tok_list_ctrl = 0;

        tok_ptr = strtok((char*restrict)all_paths, (const char*restrict)":");
        while(tok_ptr){
                strcpy(path_tokens[tok_list_ctrl++], tok_ptr);
                tok_ptr = strtok(0, (const char * restrict)":"); }

	//debugging - print list of tokens
	if(DEBUGGING){
		printf("ALL PATH TOKENS:\n");
        	int z = 0;
        	while(*path_tokens[z]){
               		printf("token: '%s'\n", path_tokens[z++]); } }
}

//initialize memory spaces and zero all bytes
int init(){
	nprintc('=',50,1);
	printf("\t\tCONNOR'S COOL SHELL\n");
	nprintc('=',50,1);
	printf("--> Running init process\n--> Malloc mem for tokens\n");
	
	for(int z = 0; z < MAX_TOK; z++){
		tokens[z] = (char*)malloc(sizeof(char) * STR_LEN);
		path_tokens[z] = (char*)malloc(sizeof(char) * STR_LEN); }
	
	printf("--> Initialize all memory to byte '0'\n");
	mem_wipe(); tok_paths();
}

//get a line of input from the user
int user_input(){
	char cwdtmp[STR_LEN], hosttmp[STR_LEN];
	getcwd(cwdtmp, STR_LEN);
	gethostname(hosttmp, STR_LEN);
	printf("%s:%s$ ", hosttmp, cwdtmp);
	fgets(line, STR_LEN, stdin);
	line[strlen(line)-1] = 0; //remove \n from end of input string
}

//process a string to tokens
int process_string(){
	char copy[STR_LEN], slice[STR_LEN];
	int tok_list_ctrl = 0; char *tok_ptr;	

	strcpy(copy, line);
	tok_ptr = strtok((char * restrict)copy, (const char * restrict)" ");
	while(tok_ptr){
		strcpy(tokens[tok_list_ctrl++], tok_ptr);
		tok_ptr = strtok(0, (const char * restrict)" "); }

	if(DEBUGGING){	
		//debugging - print list of tokens
		int z = 0;
		while(*tokens[z]){
			printf("token: '%s'\n", tokens[z]);
			z++; } }
}

int check_cd(){
	if(strcmp(tokens[0], "cd") == 0){
		if(strcmp(tokens[1], "") != 0){
			chdir((const char *)tokens[1]); }
		else{
			chdir((const char *)getenv((const char*)"HOME")); }
		return 1; }
	return 0;
}

int check_exit(){
	if(DEBUGGING){ 
		printf("checking for exit case\n"); 
		printf("token[0] = `%s`\n",tokens[0]); 
		printf("strcmp(tokens[0], `exit`) == %d\n", strcmp(tokens[0], 			"exit")); }
	if(strcmp(tokens[0], "exit") == 0){
		exit(0); return 1; }
	return 0;
}

int handle_fork(char *env){

	if(DEBUGGING) { printf("Starting handle_fork()\n"); }
	
	char cmd_path[STR_LEN];
	char *arg_v_arr[MAX_TOK];
	int pid, status, exec_err;

	//make the args array
	printf("Making args array!\n");
	printf("initializing memory for all args array slots\n");
	for(int i = 0; i < MAX_TOK; i++){
		arg_v_arr[i] = (char*)malloc(sizeof(char) * STR_LEN);
	}

	int z = 0;
	while(*tokens[z]){ //copy arg tokens to new argv array
		strcpy(arg_v_arr[z], tokens[z]);
		z++;
	}


	printf("finished making args array!\n");
	if(DEBUGGING){ //print out the argv array
		z = 0;
		while(*arg_v_arr[z]){
			printf("Arg%d: `%s`\n", z, arg_v_arr[z]); 
			z++;
		}
	}

	//make fork call
	printf("PAPA %d: I FORK A CHILD!\n",getpid());
	pid = fork();	

	//check which process we are (child/parent)		
	if(pid){ //parent process
		printf("PAPA %d: I WAIT FOR CHILD TO DIE! %s\n",getpid(),sleepy);
		wait(&status); 
		printf("PAPA %d: I BURY MY CHILD'S BODY!\n", getpid());
	}
	else{
		printf("CHILD %d STARTS DOING WORK! %s\n",getpid(),work_msg);
		//create testpath 1, then run while loop
		//once the exec call actually happens, we're done
		cmd_path[0] = 0;
		strcat(cmd_path, path_tokens[0]);
		strcat(cmd_path, "/");
		strcat(cmd_path, tokens[0]);
		//retry inside a while loop
		z = 0;
		while(execl(cmd_path,arg_v_arr[0]) && *path_tokens[z]){ 
			z++;			
			printf("%d failed on: `%s`\n",z, cmd_path);
			memset(cmd_path, 0, STR_LEN);
			strcat(cmd_path, path_tokens[z]);
                	strcat(cmd_path, "/");
                	strcat(cmd_path, tokens[0]);
		}

		printf("CHILD %d: I'M DEAD! %s\n", getpid(),i_die);
		exit(0);	
	}
}

int main(int argc, char *argv[], char *env[])
{
	init();
	while(1){
		printf("Starting new shell loop!\n");
		mem_wipe();			//reset mem space
		user_input();			//get input
		process_string();		//tokenize input
		printf("input: '%s'\n", line);	//DEBUG: print input
		if(check_cd()){ continue; } //check to run cd
		if(check_exit()) { break; } //this isn't really necessary
		handle_fork(env);
	}
	return 0;
}
