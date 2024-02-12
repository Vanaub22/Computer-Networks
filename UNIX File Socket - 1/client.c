#include "custom.h"

void main() {
    struct sockaddr_un client_addr;
    char buff[BUFF_SIZE];
    int client_fd=socket(AF_UNIX,SOCK_STREAM,0);
    if(client_fd<0) {
        perror("CLIENT: Failed to create socket\n");
        exit(0);
    }
    printf("CLIENT: Socket created\n");
    memset(&client_addr,0,sizeof(struct sockaddr_un));
    client_addr.sun_family=AF_UNIX;
    strcpy(client_addr.sun_path,SOCKET_PATH);
    
    // Connecting
    if(connect(client_fd,(struct sockaddr*)&client_addr,sizeof(struct sockaddr_un))<0) {
        perror("CLIENT: Connect failed\n");
        exit(0);
    }

    // Get bit stream from user
    printf("CLIENT: Enter bit stream: ");
    scanf("%s", buff);

    int n=write(client_fd,buff,strlen(buff));
    if(n<0) {
        perror("CLIENT: Write failed\n");
        exit(0);
    }

    if(read(client_fd,buff,sizeof(buff))<0) {
        perror("CLIENT: Read failed\n");
        exit(0);
    }

    printf("CLIENT: Modified bit stream: %s\n", buff);
    // Closing the sockets
    close(client_fd);
    exit(0);
}
