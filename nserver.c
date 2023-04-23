#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>

#define PORT 8080
#define MAXLINE 1024

int main()
{
    int sockfd, connfd;
    struct sockaddr_in servaddr, cliaddr;
    char buffer[MAXLINE];
    char *welcome_msg = "Welcome to the server!\n";

    // Create socket
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd == -1) {
        perror("socket creation failed");
        exit(EXIT_FAILURE);
    }

    memset(&servaddr, 0, sizeof(servaddr));

    // Assign IP, PORT
    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
    servaddr.sin_port = htons(PORT);

    // Bind socket with the server address
    if (bind(sockfd, (const struct sockaddr *)&servaddr, sizeof(servaddr)) != 0) {
        perror("bind failed");
        exit(EXIT_FAILURE);
    }

    // Listen for incoming connections
    if (listen(sockfd, 5) != 0) {
        perror("listen failed");
        exit(EXIT_FAILURE);
    }

    while (1) {
        // Accept incoming connection
        socklen_t len = sizeof(cliaddr);
        connfd = accept(sockfd, (struct sockaddr *)&cliaddr, &len);
        if (connfd < 0) {
            perror("accept failed");
            exit(EXIT_FAILURE);
        }
		
        // Send welcome message to client
        send(connfd, welcome_msg, strlen(welcome_msg), 0);

        while (1) {
            // Receive message from client
            memset(buffer, 0, MAXLINE);
            int n = recv(connfd, buffer, MAXLINE, 0);
            if (n <= 0) {
                break;
            }
            printf("Received message from client: %s", buffer);
        }

        // Close the connection
        close(connfd);
    }

    return 0;
}
