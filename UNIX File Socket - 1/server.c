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
    struct sockaddr_un server_addr;
    char buff[BUFF_SIZE];
    unlink(SOCKET_PATH);
    int server_fd=socket(AF_UNIX,SOCK_STREAM,0);
    if(server_fd<0) {
        perror("Failed to create socket\n");
        exit(0);
    }
    printf("Master socket created...\n");
    memset(&server_addr,0,sizeof(struct sockaddr_un));
    server_addr.sun_family=AF_UNIX;
    strcpy(server_addr.sun_path,SOCKET_PATH);
    if(bind(server_fd,(struct sockaddr*)&server_addr,sizeof(struct sockaddr_un))<0) {
        perror("Failed to bind the master socket\n");
        exit(0);
    }
    if(listen(server_fd,20)<0) {
        perror("\n");
        exit(0);
    }

    while(true) {
        int client_fd=accept(server_fd,NULL,NULL);
        if(client_fd<0) {
            perror("Accept failed\n");
            exit(0);
        }

        int n=read(client_fd,buff,sizeof(buff));
        if(n<0) {
            perror("Read Failed\n");
            exit(0);
        }

        printf("received =  %s\n",buff);

        int parity=0;
        for(int i=0;i<n;i++) {
            if(buff[i]=='1') parity++;
        }
        buff[n]=parity%2?'1':'0';

        printf("modified =  %s\n",buff);

        if(write(client_fd,buff,n+1)<0) {
            perror("Write failed\n");
            exit(0);
        }

        close(client_fd);
    }
    close(server_fd);
    unlink(SOCKET_PATH);
}


