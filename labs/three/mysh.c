#include "type.h"

int mem_wipe(){
        memset(line, 0, STR_LEN);
        for(int z = 0; z < MAX_TOK; z++){
                memset(tokens[z], 0, STR_LEN);
        }
}

int init(){
	printf("Running init process, pointing tokens to memory\n");
	for(int z = 0; z < MAX_TOK; z++){
		tokens[z] = (char*)malloc(sizeof(char) * STR_LEN);
	}
	printf("Initialize memory to 0 byte\n");
	mem_wipe();
}

int user_input(){
	char cwdtmp[STR_LEN], hosttmp[STR_LEN];
	getcwd(cwdtmp, STR_LEN);
	gethostname(hosttmp, STR_LEN);
	printf("%s:%s$ ", hosttmp, cwdtmp);
	fgets(line, STR_LEN, stdin);
	line[strlen(line)-1] = 0;		//wipe newline from input
}

int process_string(){
	
	fprintf(stderr, "starting process_string function call\n");
	
	//local variables
	char copy[STR_LEN], slice[STR_LEN];
	int tok_list_ctrl = 0;
	char *tok_ptr;	

	fprintf(stderr, "variables initialized\n");
	
	strcpy(copy, line);

	fprintf(stderr, "copied string\n");

	tok_ptr = strtok(&copy, ' ');
	
	fprintf(stderr, "Entering while loop of process statement\n");

	while(tok_ptr){
		strcpy(tokens[tok_list_ctrl], slice);
		tok_list_ctrl++;
		strcpy(slice, strtok(0, (const char * restrict)' '));
	}
	
}

int main(int argc, char *argv[], char *env[])
{
	init();
	printf("Connor's cool shell, wow!\n");
	while(active){
		mem_wipe();
		user_input();
		process_string();
		printf("input: '%s'\n", line);
	}
	return 0;
}
