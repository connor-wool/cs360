#include "type.h"

/*********
COMPLETION CHECKLIST
[ ]initialize
[ ]read input from user
[ ]tokenize input
[ ]mkdir
[ ]rmdir
[ ]cd
[ ]ls
[ ]pwd
[ ]creat
[ ]rm
[ ]save
[ ]reload
[ ]quit
[ ]testing
[ ]output formatting
[ ]cleanup random debug statements
*********/

void debug(char *s){
	printf("%s\n",s);
}

//malloc, fill, and place root node '/'
int initialize(){
	debug("(INIT)+begin");
	printf("(INIT) root=[%x] cwd=[%x]\n",(u32)root,(u32)cwd);
	debug("(INIT) create and place root node");

	NODE *p = (NODE*) malloc(sizeof(NODE));
	sprintf(p->name, "/");
	p->n_type = 'D';
	p->p_child = 0;
	p->p_sib = 0;
	p->p_parent = p;
	root = p;
	cwd = root;

        printf("(INIT) root=[%x] cwd=[%x]\n",(u32)root,(u32)cwd);
	debug("(INIT)+end");
}

int get_input(){
	printf("What is my purpose?: ");
	fgets(&line, 128, stdin);
	line[strlen(line) - 1] = 0;
	printf("INPUT: %s\n",line);
	if(strcmp(line,"you pass butter") == 0){
		printf("Oh my god.......\n");
	}
}

int tokenize_input(){
	debug("(TOKENIZE)+begin");
	sscanf(line, "%s %s", &command, &pathname);
	printf("(TOKENIZE) cmd=`%s` path=`%s`\n",command,pathname);
	debug("(TOKENIZE)+end");
}

int findCmd(){
	debug("(FINDCMD)+begin");
	int i = 0;
	while(cmd[i]){
		if(strcmp(command,cmd[i]) == 0){
			debug("(FINDCMD)+end");
			return i;
		}
		i++;
	}
	return -1;
	debug("(FINDCMD)+end");
}

int my_mkdir(){
	
}

int main()
{
	initialize();
	while(1){
		//read a line of input from the user
		get_input();
		//process that line to separate the command string
		tokenize_input();
		//find the command associated with command string
		printf("Command val = %d\n",findCmd(&command));
		//call command, passing optional arguments
	}
}
