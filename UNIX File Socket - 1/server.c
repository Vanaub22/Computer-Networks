#include "custom.h"

void main() {
    struct sockaddr_un server_addr;
    char buff[BUFF_SIZE];
    unlink(SOCKET_PATH);
    int server_fd=socket(AF_UNIX,SOCK_STREAM,0);
    if(server_fd<0) {
        perror("SERVER: Failed to create socket\n");
        exit(0);
    }
    printf("SERVER: Master socket created\n");
    memset(&server_addr,0,sizeof(struct sockaddr_un));
    server_addr.sun_family=AF_UNIX;
    strcpy(server_addr.sun_path,SOCKET_PATH);
    if(bind(server_fd,(struct sockaddr*)&server_addr,sizeof(struct sockaddr_un))<0) {
        perror("SERVER: Bind failed\n");
        exit(0);
    }
    if(listen(server_fd,20)<0) {
        perror("Listen failed\n");
        exit(0);
    }

    while(true) {
        int client_fd=accept(server_fd,NULL,NULL);
        if(client_fd<0) {
            perror("SERVER: Accept failed\n");
            exit(0);
        }

        int n=read(client_fd,buff,sizeof(buff));
        if(n<0) {
            perror("SERVER: Read Failed\n");
            exit(0);
        }
	
        printf("SERVER: Received bit stream: %s\n",buff);

        int i,parity=0;
        for(i=0;i<n;i++) {
            if(buff[i]=='1') parity++;
        }
        buff[n]=parity%2?'1':'0';

        printf("SERVER: Modified bit stream: %s\n",buff);

        if(write(client_fd,buff,n+1)<0) {
            perror("SERVER: Write failed\n");
            exit(0);
        }
        
        memset(buff,0,sizeof(buff));

        close(client_fd);
    }
    close(server_fd);
    unlink(SOCKET_PATH);
}
