#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<stdbool.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<unistd.h>
#include<sys/un.h>

#define PATH "/tmp/mysock"
#define BUFF_SIZE 30

void main() {
	struct sockaddr_un client_addr;
	bzero(&client_addr,sizeof(client_addr));
	strcpy(client_addr.sun_path,PATH);
	client_addr.sun_family=AF_UNIX;
	int client_fd=socket(AF_UNIX,SOCK_STREAM,0);
	connect(client_fd,(struct sockaddr*)&client_addr,sizeof(struct sockaddr_un));
	char s[BUFF_SIZE];
	printf("Enter message: ");
	scanf(" %[^\n]s",s);
	printf("Message to be sent: %s\n",s);
	write(client_fd,s,sizeof(s));
	bzero(s,sizeof(s));
	read(client_fd,s,sizeof(s));
	printf("Server: %s\n",s);
	close(client_fd);
}
