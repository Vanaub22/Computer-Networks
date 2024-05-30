#include<stdio.h>
#include<stdlib.h>
#include<arpa/inet.h>
#include<netinet/in.h>
#include<sys/socket.h>
#include<sys/types.h>
#include<unistd.h>
#include<string.h>
#include<stdbool.h>

#define ip "127.0.0.1"
#define PORT 8080
#define BUFF_SIZE 30

void main() {
	struct sockaddr_in server_addr,client_addr;
	server_addr.sin_family=AF_INET;
	server_addr.sin_addr.s_addr=inet_addr(ip);
	server_addr.sin_port=htons(PORT);
	int sock_fd=socket(AF_INET,SOCK_DGRAM,0);
	bind(sock_fd,(struct sockaddr*)&server_addr,sizeof(struct sockaddr_in));
	char s[30];
	while(true) {
		socklen_t l=sizeof(struct sockaddr_in);
		bzero(s,sizeof(s));
		printf("Server: Waiting...\n");
		recvfrom(sock_fd,s,sizeof(s),0,(struct sockaddr*)&client_addr,&l);
		printf("Message Received: %s\n",s);
		if(strcmp(s,"EXIT")==0) break;
		bzero(s,sizeof(s));
		strcpy(s,"Acknowledged...\n");
		sendto(sock_fd,s,sizeof(s),0,(struct sockaddr*)&client_addr,l);
		printf("Message sent...\n");
	}
	close(sock_fd);
	printf("Execution Terminated...\n");
}
