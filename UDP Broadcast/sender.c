#include "custom.h"
void main() {
    struct sockaddr_in b_addr;
    int sock_fd=socket(AF_INET,SOCK_DGRAM,0),enable=1,reuse;
    setsockopt(sock_fd,SOL_SOCKET,SO_REUSEADDR,&reuse,sizeof(reuse));
    setsockopt(sock_fd,SOL_SOCKET,SO_BROADCAST,&enable,sizeof(enable));
    bzero(&b_addr,sizeof(b_addr));
    char buff[MAX];
    b_addr.sin_family=AF_INET;
    b_addr.sin_port=htons(PORT_NO);
    b_addr.sin_addr.s_addr=INADDR_BROADCAST;
    while(true) {
        bzero(buff,sizeof(buff));
        printf("Enter the message to be broadcasted or type QUIT to exit: ");
        scanf(" %[^\n]s",buff);
        sendto(sock_fd,buff,strlen(buff),0,(struct sockaddr*)&b_addr,sizeof(b_addr));
        if(!strcmp(buff,"QUIT")) break;
    }
    printf("SENDER: Broadcast terminated...\n");
    close(sock_fd);
}