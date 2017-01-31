#include <libgen.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*************
WRITTEN BY CONNOR WOOL FOR KC WANG'S CS 360 COURSE
JANUARY 28, 2017 (god, that's gonna be funny to look back at someday)
SIMULATES A FILESYSTEM BY USING A BINARY TREE STRUCTURE
SIMULATES SIMPLE UNIX FILE COMMANDS ON SAID FILESYSTEM
*************/

//GLOBAL DEFINITIONS

typedef unsigned int u32;

typedef struct node{
	char name[64];
	char n_type;
	struct node *p_child, *p_sib, *p_parent;
}NODE;

char *cmd[] = {"mkdir","rmdir","ls","cd","pwd","creat","rm","quit","help","?","menu","reload","save",0};

//GLOBAL VARIABLES

NODE *root, *cwd;
char line[128];				//holds user input line
char command[64], pathname[64];		//holds cleaned user inputs
char dir_name[64], base_name[64];		//hold important strings

//HELPER FUNCTIONS

//pass string containing command, returns index of command in an array
/*********
int findCmd(char *command)
{
	int i = 0;
	while(cmd[i]){
		if(strcmp(command,cmd[i]) == 0){
			return i;
		}
		i++;
	}
	return -1;
}
*********/
