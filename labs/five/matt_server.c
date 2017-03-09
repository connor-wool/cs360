// This is the echo SERVER server.c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <sys/socket.h>
#include <netdb.h>
#include <fcntl.h>

#define  MAX 256

char** parseInput(char* input);


 // Create array of strings from input string
char** parseInput(char* input)
{
    int count = 0;
    char *str = NULL;
    char *tmpStr = NULL;
    // Allocate char* inputArr[20]
    char** inputArr = (char**)malloc(sizeof(char*)*20);
    str = strtok(input, " ");
    while(str)
    {
        tmpStr = (char *)malloc(sizeof(char)*strlen(str));
        strcpy(tmpStr, str);
        inputArr[count] = tmpStr;
        count++;
        str = strtok(NULL, " ");
    }
    inputArr[count] = NULL;
    return inputArr;
}




// Define variables:
struct sockaddr_in  server_addr, client_addr, name_addr;
struct hostent *hp;

int  mysock, client_sock;              // socket descriptors
int  serverPort;                     // server port number
int  r, length, n;                   // help variables


struct stat sb;
int size, fd, n, count;
char buf[MAX] = {0};


// Server initialization code:

int server_init(char *name)
{
   printf("==================== server init ======================\n");   
   // get DOT name and IP address of this host

   printf("1 : get and show server host info\n");
   hp = gethostbyname(name);
   if (hp == 0){
      printf("unknown host\n");
      exit(1);
   }
   printf("    hostname=%s  IP=%s\n",
               hp->h_name,  inet_ntoa(*(long *)hp->h_addr));
  
   //  create a TCP socket by socket() syscall
   printf("2 : create a socket\n");
   mysock = socket(AF_INET, SOCK_STREAM, 0);
   if (mysock < 0){
      printf("socket call failed\n");
      exit(2);
   }

   printf("3 : fill server_addr with host IP and PORT# info\n");
   // initialize the server_addr structure
   server_addr.sin_family = AF_INET;                  // for TCP/IP
   server_addr.sin_addr.s_addr = htonl(INADDR_ANY);   // THIS HOST IP address  
   server_addr.sin_port = 0;   // let kernel assign port

   printf("4 : bind socket to host info\n");
   // bind syscall: bind the socket to server_addr info
   r = bind(mysock,(struct sockaddr *)&server_addr, sizeof(server_addr));
   if (r < 0){
       printf("bind failed\n");
       exit(3);
   }

   printf("5 : find out Kernel assigned PORT# and show it\n");
   // find out socket port number (assigned by kernel)
   length = sizeof(name_addr);
   r = getsockname(mysock, (struct sockaddr *)&name_addr, &length);
   if (r < 0){
      printf("get socketname error\n");
      exit(4);
   }

   // show port number
   serverPort = ntohs(name_addr.sin_port);   // convert to host ushort
   printf("    Port=%d\n", serverPort);

   // listen at port with a max. queue of 5 (waiting clients) 
   printf("5 : server is listening ....\n");
   listen(mysock, 5);
   printf("===================== init done =======================\n");
}


main(int argc, char *argv[])
{
   char *hostname;
   char line[MAX];
   char **input;


   if (argc < 2)
      hostname = "localhost";
   else
      hostname = argv[1];
 
   server_init(hostname); 

   // Try to accept a client request
   while(1){
     printf("server: accepting new connection ....\n"); 

     // Try to accept a client connection as descriptor newsock
     length = sizeof(client_addr);
     client_sock = accept(mysock, (struct sockaddr *)&client_addr, &length);
     if (client_sock < 0){
        printf("server: accept error\n");
        exit(1);
     }
     printf("server: accepted a client connection from\n");
     printf("-----------------------------------------------\n");
     printf("        IP=%s  port=%d\n", inet_ntoa(client_addr.sin_addr.s_addr),
                                        ntohs(client_addr.sin_port));
     printf("-----------------------------------------------\n");

     // Processing loop: newsock <----> client
     while(1){
       n = read(client_sock, line, MAX);
       if (n==0){
           printf("server: client died, server loops\n");
           close(client_sock);
           break;
	}
	    char* cmd = NULL;
            char* filename = NULL;
            char* result = NULL;

            // Get commmand and filename from input
	    input = parseInput(line);
            cmd = input[0];
            filename = input[1];

	    if (strcmp(cmd, "quit") == 0) //quit
	    {
		//exit here
		exit(1);
	    }

            else if(strcmp(cmd, "put") == 0) // put
            {

/*
Pseudo-code:
similar to get but switch the information flow arrows...

            Server                             Client
   -------------------------------    -------------------------------
       do nothing 	       <====  send request (put filename) 

       get size/type           <====  stat filename (type/size)

  ====================================================================
  count = 0;                         
  open filename for WRITE             open filename for READ
  while(count < SIZE){                while(n=read(fd, buf, MAX)){
     n = read(socket,buf,MAX); <=====   send n bytes from buf
     count += n;
     write n bytes to file;
  }                                   }      
  close file;                         close file;
*/

		printf("1");
    		// Get size of the transfer from sender 
    		read(client_sock, buf, MAX);
		printf("2");
    		sscanf(buf, "%d", &size);


		printf("3");
    		// Write data from sender into specified file
    		count = 0;
    		fd = open(filename, O_WRONLY | O_CREAT, 0664);
    		while(count < size)
    		{
			printf("4");
        		n = read(client_sock, buf, MAX);
        		write(fd, buf, n);
        		count += n;
    		}
    		close(fd);
		printf("5");
            }

            else if(strcmp(cmd, "get") == 0) // Get
            {
    		// Check that file exists
    		if (stat(filename, &sb) == 0)
        		size = sb.st_size;
    		else
        		size = 0;

    		// Tell client how many bytes to expect during transfer
		if (size == 0)
		{
			sprintf(buf, "%s", "BAD");
    			write(client_sock, buf, MAX);
			//next command, do not open file
		}
		else
		{
    			sprintf(buf, "%d", size);
    			write(client_sock, buf, MAX);

    			// open and read from file, send to reciever
    			fd = open(filename, O_RDONLY);
    			while(n = read(fd, buf, MAX))
        			write(client_sock, buf, n);

    			close(fd);
		}
            }
            printf("server: ready for next request\n");

	}
    }
 }


