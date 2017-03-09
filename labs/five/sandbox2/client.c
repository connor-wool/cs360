// The echo client client.c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>

#include <sys/socket.h>
#include <netdb.h>

#define MAX 256

// Define variables
struct hostent *hp;              
struct sockaddr_in  server_addr; 

int server_sock, r;
int SERVER_IP, SERVER_PORT; 


// clinet initialization code

char *makestring(char *s){
	char *result = (char*)malloc(sizeof(char) * strlen(s));
	strcpy(result,s);
	return result;
}

int client_init(char *argv[])
{
  printf("======= client init ==========\n");

  printf("1 : get server info\n");
  hp = gethostbyname(argv[1]);
  if (hp==0){
     printf("unknown host %s\n", argv[1]);
     exit(1);
  }

  SERVER_IP   = *(long *)hp->h_addr;
  SERVER_PORT = atoi(argv[2]);

  printf("2 : create a TCP socket\n");
  server_sock = socket(AF_INET, SOCK_STREAM, 0);
  if (server_sock<0){
     printf("socket call failed\n");
     exit(2);
  }

  printf("3 : fill server_addr with server's IP and PORT#\n");
  server_addr.sin_family = AF_INET;
  server_addr.sin_addr.s_addr = SERVER_IP;
  server_addr.sin_port = htons(SERVER_PORT);

  // Connect to server
  printf("4 : connecting to server ....\n");
  r = connect(server_sock,(struct sockaddr *)&server_addr, sizeof(server_addr));
  if (r < 0){
     printf("connect failed\n");
     exit(1);
  }

  printf("5 : connected OK to \007\n"); 
  printf("---------------------------------------------------------\n");
  printf("hostname=%s  IP=%s  PORT=%d\n", 
          hp->h_name, inet_ntoa(SERVER_IP), SERVER_PORT);
  printf("---------------------------------------------------------\n");

  printf("========= init done ==========\n");
}

main(int argc, char *argv[ ])
{
  int n;
  char line[MAX], ans[MAX];

  if (argc < 3){
     printf("Usage : client ServerName SeverPort\n");
     exit(1);
  }

  client_init(argv);
  // sock <---> server
  printf("********  processing loop  *********\n");
  while (1){
    printf("input a line : ");
    bzero(line, MAX);                // zero out line[ ]
    fgets(line, MAX, stdin);         // get a line (end with \n) from stdin

    line[strlen(line)-1] = 0;        // kill \n at end
    if (line[0]==0)                  // exit if NULL line
       exit(0);

	char *test_string = makestring(line);
	char *command_string = makestring(strtok(test_string, " "));
	char *temp_fn; // file_name_string;
	
	//if(temp_fn = strtok(0, " ")){
	//	file_name_string = makestring(temp_fn);
	//}
	char *file_name_string = makestring(strtok(0, " "));

	//if case for get
	if ((strcmp(command_string, "get") == 0) && (file_name_string != 0)) {
		
		//send get command to server
		n = write(server_sock, line, MAX);
		printf("client: wrote n=%d bytes; line=(%s)\n",n,line);
		
		//get reply of [SIZE] from server
		n = 0;
		while(n < 1){
			n = read(server_sock, ans, MAX);
		}
	
		printf("answer from server: `%s`\n", ans);	
	
		//if reply of (BAD) then retry command input
		
		if(strcmp(ans, "BAD")==0){
			continue;
		}
		int file_size = 0;
		sscanf(ans, "%d", &file_size);		

		//create count=0
		int count = 0;

		//open file with "filename"
		char file_path[256] = {0};
		getcwd(file_path, 256);
		strcat(file_path, "/");
		strcat(file_path, file_name_string);
		int fd = open(file_path, O_WRONLY | O_CREAT);		
		
		char socket_buf[256] = {0};
		//read from socket until (total read) = (count)
		while( count < file_size ){
			n = read(server_sock, socket_buf, 256);
			count += n;
			write(fd, socket_buf, 256); 
		}
		close(fd);
		//write that data into file	
		//close file with "filename"
	}
	//if case for put
        if ((strcmp(command_string, "put") == 0) && (file_name_string != 0)){
		//send put command to server
                n = write(server_sock, line, MAX);
                printf("client: wrote n=%d bytes; line=(%s)\n",n,line);

		//create file path		
		char file_path[256] = {0};
                getcwd(file_path, 256);
                strcat(file_path, "/");
                strcat(file_path, file_name_string);
                //int fd = open(file_path, O_WRONLY | O_CREAT);
		
		struct stat sb;
		int file_size = 0;
		if (stat (file_path, &sb) == 0)
			file_size = sb.st_size;
		else
			file_size = 0;

		char sock_buf[256] = {0};
		sprintf(sock_buf, "%d", file_size);
		write(server_sock, sock_buf, 256);

		int fd = open(file_path, O_RDONLY);
		while (n = read(fd, sock_buf, 256)){
			write(server_sock, sock_buf, n);
		}
		close(fd);
	}

	//if case for exit
	if(strcmp(command_string, "quit") == 0){
		char sock_buf[256] = {0};
		sprintf(sock_buf, "quit");
		n = write(server_sock, sock_buf, 256);
		exit(0);
	}    
  }
}


