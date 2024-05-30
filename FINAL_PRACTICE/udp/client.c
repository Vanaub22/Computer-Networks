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
	struct sockaddr_in server_addr;
	server_addr.sin_addr.s_addr=inet_addr(ip);
	server_addr.sin_family=AF_INET;
	server_addr.sin_port=htons(PORT);
	int sock_fd=socket(AF_INET,SOCK_DGRAM,0);
	printf("Enter a message: ");
	char s[BUFF_SIZE];
	bzero(s,sizeof(s));
	scanf(" %[^\n]s",s);
	printf("Message to be sent: %s\n",s);
	socklen_t l=sizeof(struct sockaddr_in);
	sendto(sock_fd,s,sizeof(s),0,(struct sockaddr*)&server_addr,l);
	printf("Message sent to server...\n");
	recvfrom(sock_fd,s,sizeof(s),0,(struct sockaddr*)&server_addr,&l);
	close(sock_fd);
}
