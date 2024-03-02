#include "custom.h"

void main() {
    int client_fd=socket(AF_UNIX,SOCK_STREAM,0);
    struct sockaddr_un client_addr;
    memset(&client_addr,0,sizeof(struct sockaddr_un));
    client_addr.sun_family=AF_UNIX;
	strcpy(client_addr.sun_path,SOCKET_PATH);
    connect(client_fd,(struct sockaddr*)&client_addr,sizeof(struct sockaddr_un));
    printf("Enter the IPv4 address that you wish to validate: ");
    char in[MAX];
    scanf(" %[^\n]s",in);
    in[strlen(in)]='\0';
    write(client_fd,in,strlen(in)+1);
    int res;
    read(client_fd,&res,sizeof(res));
    printf("the result: %d\n",res);
    close(client_fd);
}