#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/socket.h>
#include<sys/types.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<pthread.h>
#include<string.h>
#include<stdbool.h>

#define MAX 50
#define ip "127.0.0.1"
#define PORT 8080

void main() {
	struct sockaddr_in server_addr,client_addr;
	server_addr.sin_family=AF_INET;
	server_addr.sin_addr.s_addr=inet_addr(ip);
	server_addr.sin_port=htons(PORT);
	int sockfd=socket(AF_INET,SOCK_STREAM,0);
	connect(sockfd,(struct sockaddr*)&server_addr,sizeof(struct sockaddr_in));
	printf("Enter a message: ");
	char s[MAX];
	scanf(" %[^\n]s",s);
	write(sockfd,s,sizeof(s));
	bzero(s,sizeof(s));
	read(sockfd,s,sizeof(s));
	printf("Message received from server: %s",s);
	close(sockfd);
}
