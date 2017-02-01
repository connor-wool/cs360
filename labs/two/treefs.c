#include "type.h"

/*********
COMPLETION CHECKLIST
[x]initialize
[x]read input from user
[x]tokenize input
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
	sscanf(line, "%s %s", &command, &pathname);
	printf("(TOKENIZE) cmd=`%s` path=`%s`\n",command,pathname);
}

int findCmd(){
	int i = 0;
	while(cmd[i]){
		if(strcmp(command,cmd[i]) == 0){
			return i;
		}
		i++;
	}
	return -1;
}

int drawline()
{
	int number = 30;
	for(int i = 0; i < number; i++){
		printf("=");
	} 
	printf("\n");
}

//assumes that "pathname" is non-empty and current
//after execution, dir_name and base_name should be set properly
int split_dir_base(){
	debug("(SPLIT)+begin");
	char temp[64];
	strcpy(temp,pathname);
	strcpy(dir_name,dirname(temp));
	strcpy(temp,pathname);
	strcpy(base_name,basename(temp));
	printf("(SPLIT) base=`%s` path=`%s`\n",base_name,dir_name);
	debug("(SPLIT)+end");
}

int menu(){
	drawline();
	printf("::ALLOWED COMMANDS::\n");
	drawline();
	printf("mkdir  dirname\n");
	printf("rmdir  dirname\n");
	printf("ls    [dirname]\n");
	printf("cd    [dirname]\n");
	printf("pwd\n");
	printf("creat [dirname]\n");
	printf("rm     dirname\n");
	printf("quit / help / ? / menu\n");
	printf("reload / save\n");
	drawline();
}

int makeNode(NODE *parent, char *name, char file_type){
	
}

//searches for a named file in a directory. Returns a pointer
//to the node if found, returns 0 otherwise.
NODE *search_in_dir(NODE *start, char *target_name){
	NODE *n = start->p_child;
	while(n){
		if(strcmp(n->name,target_name) == 0){
			return n;
		}
		n = n->p_sib;
	}
	return (NODE*)0;
}

/* Recursively search through directories for a specific filename*/
NODE *rsearch(char *path, NODE *current){
	char test[128], target[64];
	NODE *np = 0;
	strcpy(test,path);
	
	/*if this first case is true, we can treat `path` as just the name
 	of the node that we're searching for.*/
	if(strcmp(dirname(test),".") == 0){
		np = current->p_child;
		while(np){
			if(strcmp(np->name,path) == 0){
                        	return np;
                	}
                	np = np->p_sib;
		}
		return (NODE*)0; //return 0 if not found, no existo el nodo
	}

	/* This is the case where we still have one or more directories
	to search down through. Set target to be the name of next file
	to look for, increment path to point after first `/` */	
	else{
		strcpy(test,path);
		strcpy(target,strtok(test,"/"));
		printf("path before mod `%s`\n",path);
		path += strlen(target) + 1;	
		printf("path after mod `%s`\n",path);

		//search for the next node in the path
		np = current->p_child;
                while(np){
                        if(strcmp(np->name,path) == 0){
                                return rsearch(path, np);
                        }
                        np = np->p_sib;
                }
                return (NODE*)0; //return 0 if not found, no existo el nodo

	}
}

NODE *search(char *path){
	NODE *start = 0;
	if(strcmp(path,"/") == 0){
		return root;
	}
	if(path[0] == '/'){
		start = root;
		path++;
	}
	else{
		start = cwd;
	}
	return rsearch(path, start);

}

int my_pwd(){
	
}

int my_mkdir(){
	//break up pathname into dirname and basename
	split_dir_base();
	
	//check if path node exists
	NODE *p = search(dir_name);
	printf("p=[%x]\n",(u32)p);
	if(p == 0){
		printf("ERROR! DIRNAME %s DOES NOT EXIST!\n",dir_name);
		return;
	}
	else if (p->n_type == 'F'){
		printf("ERROR! DIRNAME %s EXISTS, BUT IS REG FILE (NOT DIR)\n",dir_name);
		return;
	}

	//keep a reference to that parent before moving on
	NODE *dir_node = p;	

	//check if base node already exists
	p = search(pathname);
	if(p != 0){
		printf("ERROR! FILE AT %s ALREADY EXISTS!\n",pathname);
		return;
	}
	
	
	

	return;		
}

int main()
{
	int run = 1;
	initialize();
	while(run){
		//read a line of input from the user
		get_input();
		//process that line to separate the command string
		tokenize_input();
		//find the command associated with command string
		//call command, passing optional argumentsi
		int cmdID = findCmd(&command);
		switch(cmdID){
			case 0: my_mkdir();	break;
			case 7: run = 0;	break;
			case 8: menu();		break;
			case 9: menu();		break;
			case 10: menu();	break;
			default: printf("found nothing\n"); break;
		}
	}
}
