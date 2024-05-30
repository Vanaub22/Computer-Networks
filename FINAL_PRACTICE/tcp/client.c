#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<arpa/inet.h>
#include<netinet/in.h>
#include<string.h>

#define ip "127.0.0.1"
#define PORT 8009

void main() {
	char s[30];
	struct sockaddr_in client_addr;
	client_addr.sin_family=AF_INET;
	client_addr.sin_port=htons(PORT);
	client_addr.sin_addr.s_addr=inet_addr(ip);
	int client_fd=socket(AF_INET,SOCK_STREAM,0);
	if(client_fd<0) {
		perror("Socket not created");
		exit(0);
	}
	int n=connect(client_fd,(struct sockaddr*)&client_addr,sizeof(struct sockaddr_in));
	if(n<0) {
		perror("Connection refused");
		exit(0);
	}
	printf("Enter the message: ");
	scanf(" %[^\n]s",s);
	write(client_fd,s,sizeof(s));
	bzero(s,sizeof(s));
	printf("Message sent...\n");
	read(client_fd,s,sizeof(s));
	printf("Message received: %s\n",s);
	close(client_fd);
	printf("Execution Terminated\n");
}
