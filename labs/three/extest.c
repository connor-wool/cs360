#include <stdio.h>
#include <unistd.h>

int main(int argc, char * argv[], char *env[]){
	char *file_name = "/bin/pwd";
	char *arg_arr[] = {"pwd", 0};
	fprintf(stderr, "making call to execve!\n");
	int result = execve(file_name, arg_arr, env);
	fprintf(stderr, "shouldn't see this line!\n");
	
}
