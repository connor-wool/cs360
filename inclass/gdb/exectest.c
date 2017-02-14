#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>



main(int argc, char *argv[], char *env[]){

	int pid, status;

	char *argv_arr[] = {"/bin/pwd"};	

	pid = fork();
	if(pid){
		printf("wait for child to die\n");
		wait(&status);
	}
	else{
		int err_code = execve(argv_arr[0], argv_arr, 0);
		printf("child fucked up! : %d\n", err_code);
	}
}	
