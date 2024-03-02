#include "custom.h"

void main() {
    Word m;
    char res[BUFF_SIZE];
    struct sockaddr_un client_addr;
    int client_fd=socket(AF_UNIX,SOCK_STREAM,0);
    memset(&client_addr,0,sizeof(client_addr));
    client_addr.sun_family=AF_UNIX;
    strcpy(client_addr.sun_path,SOCKET_PATH);
    connect(client_fd,(struct sockaddr*)&client_addr,sizeof(struct sockaddr_un));
    printf("Enter the generator: ");
    scanf(" %[^\n]s",m.gen);
    printf("Enter the dataword: ");
    scanf(" %[^\n]s",m.dw);
    write(client_fd,&m,sizeof(Word));
    read(client_fd,res,sizeof(res));
    printf("Codeword Obtained from server: %s",res);
    close(client_fd);
}