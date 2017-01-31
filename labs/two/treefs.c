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

//returns either a pointer to the named node, or 0
NODE *search(char *path, char *base, NODE *p){
	
	printf("(SEARCH)+begin search for `%s` on `%s`\n",base,path);
	if(strcmp(path, "") == 0){
		debug("(SEARCH) base case");
		while(p){
			if(strcmp(base,p->name) == 0){
				return p;
			}
			p = p->p_sib;
		}
		return (NODE*)0;
	}
	
	//if we didn't meet case 1, we have more path to travel
	else{
		debug("(SEARCH) recursion case");
		char temp[128];
		char target[128];
		char newPath[128];
		strcpy(temp,path);
		//copy the name to search for into `target`
		strcpy(target,strtok(temp, "/"));
		//now that we have a target name, we can use that to
		//create the next path string
		int k = strlen(target) + 1;
		int j = 0;
		while(path[k]){
			newPath[j] = path[k];
			k++; j++;
		}
		newPath[j] = 0;

		printf("target=`%s`\n",target);
		printf("newpath=`%s`\n",newPath);	
		
		while(p){
                        if(strcmp(target, p->name) == 0){
				return search(newPath,base,p);
                        }
                        p = p->p_sib;
                }
		return (NODE*)0;
	}
	debug("(SEARCH)+end (ask:why am i seeing this?)");
}

int my_pwd(){
	
}

int my_mkdir(){
	//break up pathname into dirname and basename
	split_dir_base();
	//check if path node exists
	char temp[64];
	char cp1[64],cp2[64];
	strcpy(temp,dir_name);
	strcpy(cp1,dirname(temp));
	strcpy(temp,dir_name);
	strcpy(cp2,basename(temp));
	printf("cp1=`%s` cp2=`%s`\n",cp1,cp2);

	NODE *p = search(cp1,cp2,root);
	printf("p=[%x]\n",(u32)p);
		
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
