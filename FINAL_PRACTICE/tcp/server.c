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
	printf("SERVER: Waiting for messages...\n");
	char s[30];
	struct sockaddr_in server_addr;
	server_addr.sin_family=AF_INET;
	server_addr.sin_port=htons(PORT);
	server_addr.sin_addr.s_addr=inet_addr(ip);
	int server_fd=socket(AF_INET,SOCK_STREAM,0);
	if(server_fd<0) {
		perror("Socket not created");
		exit(0);
	}
	bind(server_fd,(struct sockaddr*)&server_addr,sizeof(struct sockaddr_in));
	listen(server_fd,1);
	while(1) {
		int client_fd=accept(server_fd,NULL,NULL);
		bzero(s,sizeof(s));
		read(client_fd,s,sizeof(s));
		printf("Message received: %s\n",s);
		if(strcmp(s,"EXIT")==0) break;
		bzero(s,sizeof(s));
		strcpy(s,"Acknowledged...");
		write(client_fd,s,sizeof(s));
		printf("Message sent to client...\n");
		close(client_fd);
	}
	close(server_fd);
	printf("Execution Terminated\n");
}
