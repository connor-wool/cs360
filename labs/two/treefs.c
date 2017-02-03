#include "type.h"

/*********
COMPLETION CHECKLIST
[x]initialize
[x]read input from user
[x]tokenize input
[x]mkdir
[x]rmdir
[x]cd
[/]ls
[x]pwd
[x]creat
[x]rm
[x]save
[!]reload
[x]quit
[x]menu
[!]testing
[!]output formatting
[!]cleanup random debug statements
*********/

void debug(char *s){
	printf("%s\n",s);
}

//malloc, fill, and place root node '/'
int initialize(){
	printf("Initializing root node... ");
	NODE *p = (NODE*) malloc(sizeof(NODE));
	sprintf(p->name, "/");
	p->n_type = 'D';
	p->p_child = 0;
	p->p_sib = 0;
	p->p_parent = p;
	root = p;
	cwd = root;
	printf("done.\n");
}

int get_input(){
	printf(">>> CMD: ");
	fgets(&line, 128, stdin);
	line[strlen(line) - 1] = 0;
}

int tokenize_input(){
	sscanf(line, "%s %s", &command, &pathname);
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
	int number = 40;
	for(int i = 0; i < number; i++){
		printf("=");
	} 
	printf("\n");
}

//assumes that "pathname" is non-empty and current
//after execution, dir_name and base_name should be set properly
int split_dir_base(){
	char temp[64];
	strcpy(temp,pathname);
	strcpy(dir_name,dirname(temp));
	strcpy(temp,pathname);
	strcpy(base_name,basename(temp));
	printf("(SPLIT) base=`%s` path=`%s`\n",base_name,dir_name);
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
	
	//create the new baby node
	NODE *baby = (NODE*) malloc(sizeof(NODE));
	sprintf(baby->name,"%s",name);
	baby->p_parent = parent;
	baby->p_child = 0;
	baby->p_sib = 0;
	baby->n_type = file_type;

	printf("new node: ['%s' %c]\n",baby->name,baby->n_type);
	
	if(parent->p_child == 0){
		parent->p_child = baby;
	}
	else{
		NODE *temp = parent->p_child;
		while(temp->p_sib){
			temp = temp->p_sib;
		}
		temp->p_sib = baby;
	}
}

/*
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
*/

/* Recursively search through directories for a specific filename*/
NODE *rsearch(char *path, NODE *current){
	printf("(RSEARCH)+begin for `%s`\n",path);
	char test[128], target[64];
	NODE *np = 0;
	strcpy(test,path);
	
	/*if this first case is true, we can treat `path` as just the name
 	of the node that we're searching for.*/
	if(strcmp(dirname(test),".") == 0){
		if(strcmp(path,".") == 0){
			printf("(RSEARCH) return because `.`\n");
			return current;
		}
		if(strcmp(path,"..") == 0){
			printf("(RSEARCH) return because `..`\n");
			return current->p_parent;
		}
		np = current->p_child;
		while(np){
			if(strcmp(np->name,path) == 0){
				printf("(RSEARCH) return because match\n");
                        	return np;
                	}
                	np = np->p_sib;
		}
		printf("(RSEARCH) return because NO match\n");
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
		printf("(RSEARCH) return because NO match at mid-level\n");
                printf("(RSEARCH) search was trying to match `%s`\n",target);
		return (NODE*)0; //return 0 if not found, no existo el nodo

	}
}

NODE *search(char *path){
	
	printf("(SEARCH DRIVER)+begin for `%s`\n", path);

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

int my_cd(){
	NODE *newloc = search(pathname);
	if(newloc == 0){
		printf("ERROR: path not found!\n");
	}
	else{
		cwd = newloc;
	}
}

int pwd_recursive(NODE *p){
	if(p->p_parent == p){ // we're at root
		printf("/");
	}
	else{
		pwd_recursive(p->p_parent);
		printf("%s/",p->name);
	}
}

int my_pwd(){
	pwd_recursive(cwd);
	printf("\n");
}
	
int my_ls(){
	drawline();
	printf("\t\tLS\n");
	NODE *current = cwd;
	NODE *working = cwd->p_child;
	printf("type\tpath\n");
	drawline();
	while(working){
		printf("%c\t%s\n",working->n_type,working->name);
		working = working->p_sib;
	}
	drawline();
	return 0;
}

int my_mkdir(){
	printf("\t\tMKDIR\n");
	drawline();
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
	
	makeNode(dir_node, base_name, 'D');
	drawline();
	return 0;		
}

int deleteNode(NODE *del){
	
	//talk to the deletee's parent
	NODE *parent = del->p_parent;
	
	//if first child of parent, remove and shift pointers
	if(parent->p_child == del){
		parent->p_child = del->p_sib;
		return 0;
	}

	//otherwise search siblings for reference
	NODE *current = parent->p_child;
	while(current->p_sib != del){
		current = current->p_sib;
	}
	
	//now the current's sibling pointer is del
	current->p_sib = del->p_sib;
	
	//let del be free!
	free(del);
}

int my_rmdir(){
	drawline();
	printf("\t\tRMDIR\n");
	
	//check if dir exists
	NODE *p = search(pathname);
	printf("p=[%x]\n",(u32)p);
	if(p == 0){
		printf("Error: specified directory does not exist\n");
		return 0;
	}

	//check if node is a directory
	if(p->n_type == 'F'){
		printf("Error: speficied path is not a directory\n");
		return 0;
	}	
	deleteNode(p);
	drawline();
	return 0;
}

int my_rm(){
	drawline();
	printf("\t\tRM\n");
	
	//check if a file exists
	NODE *del = search(pathname);
	printf("p=[%x]\n",(u32)del);
	if(del == 0){
		printf("Error: specified file does not exist\n");
		return 0;
	}

	//check if node is a file
	if(del->n_type == 'D'){
		printf("Error: specified node is a directory\n");
		return 0;
	}
	deleteNode(del);
	drawline();
	return 0;
}

int my_creat(){
	//break up pathname into dirname and basename
        drawline();
	printf("\t\tCREAT\n");

	split_dir_base();

        //check if path node exists
        NODE *p = search(dir_name);
        printf("p=[%x]\n",(u32)p);
        if(p == 0){
                printf("ERROR! DIRNAME %s DOES NOT EXIST!\n",dir_name);
                return 1;
        }
        else if (p->n_type == 'F'){
                printf("ERROR! DIRNAME %s EXISTS, BUT IS REG FILE (NOT DIR)\n",dir_name);
                return 1;
        }

        //keep a reference to that parent before moving on
        NODE *dir_node = p;

        //check if base node already exists
        p = search(pathname);
        if(p != 0){
                printf("ERROR! FILE AT %s ALREADY EXISTS!\n",pathname);
                return 1;
        }

        makeNode(dir_node, base_name, 'F');
        drawline();
	return 0 ;

}

void rsavehelper(NODE *current, char *buf, char *loc, FILE *fp){
	if(current == 0){
		return;
	}

	//push a copy of own name onto buf (basically a stack)
	strcpy(loc,current->name);
	
	//now print the current buf
	fprintf(fp, "%c %s\n", current->n_type, buf);
	printf("node: `%s`\tbuf: `%s`\n", current->name, buf);

	//now go to children while own name on stack
	if(current == root){
		rsavehelper(current->p_child, buf, loc+strlen(current->name),fp);
	}
	else{
		strcpy(loc+strlen(current->name), "/");
		rsavehelper(current->p_child, buf, loc + strlen(current->name)+1, fp);
	}

	//remove own name before moving to siblings
	*loc = 0;

	//now print siblings
	rsavehelper(current->p_sib, buf, loc, fp);
}

void save(){
	drawline();
	printf("\t\tSAVE FS\n");
	FILE *fp = fopen("savefile1","w+");
	char printbuf[1000];
	rsavehelper(root, &printbuf, &printbuf, fp);
	fclose(fp);
	drawline();
}

void reload(){
	drawline();
	printf("\t\tRELOAD FS FROM FILE\n");
	
	//read in file
	//if starts with F, use 'creat' and pathname
	//if starts iwht D, use 'mkdir' and pathname
	//go until file is empty
	
	drawline();
}

int main()
{
	printf("PROGRAM: CS 360, LAB 2, (File System Simulator)\n");
	printf("AUTHOR: Connor Wool (Feb 2, 2017)\n");
	printf("--------> PROGRAM RUN -------->\n\n");
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
			case 1: my_rmdir();	break;
			case 2: my_ls();	break;
			case 3: my_cd();	break;
			case 4: my_pwd();	break;
			case 5: my_creat();	break;
			case 6: my_rm();	break;
			case 7: run = 0;	break;
			case 8: menu();		break;
			case 9: menu();		break;
			case 10: menu();	break;
			case 11: reload();	break;
			case 12: save();	break;
			default: printf("found nothing\n"); break;
		}
	}
}
