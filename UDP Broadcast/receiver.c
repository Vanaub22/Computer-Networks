#include "custom.h"
void main() {
    struct sockaddr_in r_addr,b_addr;
    int sock_fd=socket(AF_INET,SOCK_DGRAM,0),enable=1,reuse;
    setsockopt(sock_fd,SOL_SOCKET,SO_BROADCAST,&enable,sizeof(enable));
    setsockopt (sock_fd,SOL_SOCKET,SO_REUSEADDR,&reuse,sizeof(reuse));
    char buff[MAX];
    bzero(&r_addr,sizeof(r_addr));
    r_addr.sin_family=AF_INET;
    r_addr.sin_port=htons(PORT_NO);
    r_addr.sin_addr.s_addr=INADDR_ANY;
    bind(sock_fd,(struct sockaddr*)&r_addr,sizeof(r_addr));
    while(true) {
        bzero(buff,sizeof(buff));
        recvfrom(sock_fd,buff,MAX,0,NULL,NULL);
        printf("Broadcasted Message: %s\n",buff);
        if(!strcmp(buff,"QUIT")) break;
    }
    printf("RECEIVER: Broadcasting terminated by sender...\n");
    close(sock_fd);
}