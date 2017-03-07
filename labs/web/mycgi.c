#include <dirent.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

#define MAX 10000
typedef struct {
    char *name;
    char *value;
} ENTRY;

ENTRY entry[MAX];

char *makestring(char *s){
	char *tmp = (char *) malloc(sizeof(char)*strlen(s));
	strcpy(tmp, s);
	return tmp;
}

void html_ls(DIR *dirp){
	struct dirent *ent_p = readdir(dirp);
	struct stat mystat, *sp;
	char *t1 = "xrwxrwxrw-------";
	char *t2 = "----------------";
	char ftime[64];
	char full_path[256];
	char cwd[256];
	int i,r;
	sp = &mystat;
	getcwd(&cwd, 256);

	while(ent_p){
		//do stuff
		//printf("<p> found entry: %s\n",ent_p->d_name);
		
		//create a path string to file
		full_path[0] = 0;
		strcat(full_path, cwd);
		strcat(full_path, "/");
		strcat(full_path, ent_p->d_name);
		
		if( (r = lstat(&full_path, &mystat)) < 0){
			printf("<p> couldn't stat file %s\n",full_path);
		}
		
		printf("<p>");

		//print file type
		if((sp->st_mode & 0xF000) == 0x8000)
			printf("%c",'-');
		if((sp->st_mode & 0xF000) == 0x4000)
			printf("%c",'d');
		if((sp->st_mode & 0xF000) == 0xA000)
			printf("%c",'l');
		
		//prints permission bits
		for (i=8; i>=0; i--){
			if (sp->st_mode & (1 << i))
				printf("%c",t1[i]);
			else
				printf("%c",t2[i]);
		}

		//print links, groupid, userid, and byte size
		printf("%4d ", sp->st_nlink);
		printf("%4d ", sp->st_gid);
		printf("%4d ", sp->st_uid);
		printf("%8d ", sp->st_size);

		//print the time
		strcpy(ftime, ctime(&sp->st_ctime));
		ftime[strlen(ftime)-1] = 0;
		printf("%s ", ftime);

		//print the name
		printf("%s<p>\n", ent_p->d_name);

		//do this last to set up for new loop
		ent_p = readdir(dirp);
	}
}

main(int argc, char *argv[]) 
{
  int i, m, r;
  char cwd[128];

  chdir("/home/wool/public_html/cgi-bin/sandbox");
  m = getinputs();    // get user inputs name=value into entry[ ]
  getcwd(cwd, 128);   // get CWD pathname

  printf("Content-type: text/html\n\n");
  printf("<font face=\"Lucida Console,arial,helvetica\">");
  printf("<p>pid=%d uid=%d cwd=%s\n", getpid(), getuid(), cwd);

  printf("<H1>Echo Your Inputs</H1>");
  printf("You submitted the following name/value pairs:<p>");
 
  for(i=0; i <= m; i++)
     printf("%s = %s<p>", entry[i].name, entry[i].value);
  printf("<p>");


  /*****************************************************************
   Write YOUR C code here to processs the command
         mkdir dirname
         rmdir dirname
         rm    filename
         cat   filename
         cp    file1 file2
         ls    [dirname] <== ls CWD if no dirname
  *****************************************************************/
char *arg_arr[10];
  
ENTRY *ep = entry;
while(ep && (strcmp(ep->value, "") != 0)){
	printf("<p>name:`%s` \tvalue:`%s`\n",ep->name, ep->value);
	ep++;
}

//case of the mkdir command
if(strcmp(entry[0].value, "mkdir") == 0){
	if(strcmp(entry[1].value, "") != 0){
		char buf[1024];
		buf[0] = 0;
		strcat(buf, cwd);
		strcat(buf, "/");
		strcat(buf, entry[1].value);
		int status = mkdir(&buf, 0x777);
		if(status == -1){
			printf("<p>--> error occurred, dir not made\n");
		}
		else{
			printf("<p>--> dir created successfully\n");
		}
	}
}

//rmdir command
if(strcmp(entry[0].value, "rmdir") == 0){
	if(strcmp(entry[1].value, "") != 0){
		char buf[1024];
		buf[0] = 0;
		strcat(buf, cwd);
		strcat(buf, "/");
		strcat(buf, entry[1].value);
		int status = rmdir(&buf);
		if(status == -1){
			printf("<p>--> error occurred, dir not removed!\n");	
		}
		else{
			printf("<p>--> dir removed successfully!\n");
		}
	}
}

//rm command
if(strcmp(entry[0].value, "rm") == 0){

}

//cat
if(strcmp(entry[0].value, "cat") ==0){
	if(strcmp(entry[1].value, "") != 0){
		//run cat comand on pathname from entry[1]
		//make full file pathname i
		char path[256] = {0};
		getcwd(&path, 256);
		strcat(path, "/");
		strcat(path, entry[1].value);
		//open file with pathname for reading
		printf("<p>Open file: `%s`</p>",path);
		int fd = open(&path, O_RDONLY);
		//print chars from file to output
		char buf[4100] = {0};
		int status = read(fd, &buf, 4096);
		printf("<p>-----CAT OUTPUT-----</p>");
		printf("<p>");
		int i = 0;
		while(status > 0 && (int)buf[i] > 0){
			if(buf[i] == '\n')
				printf("</p><p>");
			else
				printf("%c",buf[i]);
			i++;
			if(buf[i] == 0)
				status = read(fd, &buf, 4096);
		}
		printf("</p>");
	}
}
//cp
if(strcmp(entry[0].value, "cp") == 0){
	if((strcmp(entry[1].value, "") != 0) && (strcmp(entry[2].value, "") != 0)){
		//run the cp command
		//get directories for both files
		//
		/*
		char cwd[256], file1[256], file2[256];
		cwd[0] = 0; file1[0] = 0; file2[0] = 0;
		getcwd(&cwd, 256);
		strcat(file1, cwd); strcat(file2, cwd);
		strcat(file1, "/"); strcat(file2, "/");
		strcat(file1, entry[1].value); strcat(file2, entry[2].value);
		//open file 1 for reading
		*/
		/*
		int source = open(&file1, O_RDONLY);
		//open file 2 for writing (create if necessary)
		int dest = open(&file2, O_WRONLY|O_CREAT);
		//read buffer from file 1
		//write buffer to file 2
		char buf[4100] = {0};
		int status = read(source, &buf, 4096);
		while(status > 0 && buf[0] > 0){
			write(dest, &buf, 4096);
			status = read(source, &buf, 4096);
		}
		*/
	}
}

//ls
if(strcmp(entry[0].value, "ls") == 0){
	DIR *to_list = opendir(&cwd);
	html_ls(to_list);
}

printf("</p>\n");

  // create a FORM webpage for user to submit again 
  printf("</title>");
  printf("</head>");
  printf("<body bgcolor=\"#8a00b5\" link=\"#330033\" leftmargin=8 topmargin=8");
  printf("<p>------------------ DO IT AGAIN ----------------\n");
  
  printf("<FORM METHOD=\"POST\" ACTION=\"http://cs360.eecs.wsu.edu/~wool/cgi-bin/mycgi\">");

  //------ NOTE : CHANGE ACTION to YOUR login name ----------------------------
  //printf("<FORM METHOD=\"POST\" ACTION=\"http://cs360.eecs.wsu.edu/~YOURNAME/cgi-bin/mycgi\">");
  
  printf("Enter command : <INPUT NAME=\"command\"> <P>");
  printf("Enter filename1: <INPUT NAME=\"filename1\"> <P>");
  printf("Enter filename2: <INPUT NAME=\"filename2\"> <P>");
  printf("Submit command: <INPUT TYPE=\"submit\" VALUE=\"Click to Submit\"><P>");
  printf("</form>");
  printf("------------------------------------------------<p>");

  printf("</body>");
  printf("</html>");
}


