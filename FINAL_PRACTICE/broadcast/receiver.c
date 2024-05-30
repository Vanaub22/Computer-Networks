#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/socket.h>
#include<sys/types.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<stdbool.h>
#include<string.h>

#define MAX 30
#define PORT_NO 8080
void main() {
    struct sockaddr_in b_addr,r_addr;
    int sock_fd=socket(AF_INET,SOCK_DGRAM,0),enable=1,reuse=1;
    setsockopt(sock_fd,SOL_SOCKET,SO_REUSEADDR,&reuse,sizeof(reuse));
    setsockopt(sock_fd,SOL_SOCKET,SO_BROADCAST,&enable,sizeof(enable));
    bzero(&r_addr,sizeof(r_addr));
    char buff[MAX];
    r_addr.sin_family=AF_INET;
    r_addr.sin_port=htons(PORT_NO);
    r_addr.sin_addr.s_addr=INADDR_ANY;
    bind(sock_fd,(struct sockaddr*)&r_addr,sizeof(struct sockaddr_in));
    while(true) {
        bzero(buff,sizeof(buff));
	socklen_t l=sizeof(struct sockaddr_in);
	recvfrom(sock_fd,buff,MAX,0,(struct sockaddr*)&b_addr,&l);
	printf("Broadcasted Message: %s\n",buff);
        if(!strcmp(buff,"QUIT")) break;
    }
    printf("SENDER: Broadcast terminated...\n");
    close(sock_fd);
}
