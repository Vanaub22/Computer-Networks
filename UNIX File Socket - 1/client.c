#include<stdlib.h>
#include<unistd.h>
#include<stdio.h>
#include<string.h>
#include<sys/un.h>
#include<sys/socket.h>
#include<sys/types.h>
#include<stdbool.h>

#define SOCKET_PATH "/tmp/yourSocket"
#define BUFF_SIZE 30

void main() {
    struct sockaddr_un client_addr;
    char buff[BUFF_SIZE];
    int client_fd=socket(AF_UNIX,SOCK_STREAM,0);
    if(client_fd<0) {
        perror("Failed to create socket\n");
        exit(0);
    }
    printf("Socket created\n");
    memset(&client_addr,0,sizeof(struct sockaddr_un));
    client_addr.sun_family=AF_UNIX;
    strcpy(client_addr.sun_path,SOCKET_PATH);
    
    // connect
    client_addr.sun_family=AF_UNIX;
    strcpy(client_addr.sun_path,SOCKET_PATH);
    if(connect(client_fd,(struct sockaddr*)&client_addr,sizeof(struct sockaddr_un))<0) {
        perror("Connect failed\n");
        exit(0);
    }

    // Get bit stream from user
    printf("Enter bit stream: ");
    scanf("%s", buff);

    int n=write(client_fd,buff,strlen(buff));
    if(n<0) {
        perror("Write failed\n");
        exit(0);
    }

    if(read(client_fd,buff,sizeof(buff))<0) {
        perror("read failed\n");
        exit(0);

    }

    // Print result
    printf("Modified bit stream: %s\n", buff);
    //closing the sockets
    close(client_fd);
    exit(0);
}


