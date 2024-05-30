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
	unlink(PATH);
	struct sockaddr_un server_addr;
	bzero(&server_addr,sizeof(server_addr));
	strcpy(server_addr.sun_path,PATH);
	server_addr.sun_family=AF_UNIX;
	int server_fd=socket(AF_UNIX,SOCK_STREAM,0);
	bind(server_fd,(struct sockaddr*)&server_addr,sizeof(struct sockaddr_un));
	listen(server_fd,1);
	char s[BUFF_SIZE];
	while(true) {
		bzero(s,sizeof(s));
		int client_fd=accept(server_fd,NULL,NULL);
		read(client_fd,s,sizeof(s));
		printf("Message Received is: %s\n",s);
		if(strcmp(s,"EXIT")==0) break;
		bzero(s,sizeof(s));
		strcpy(s,"Acknowledged...\n");
		write(client_fd,s,sizeof(s));
		printf("Acknowledgement sent to client...\n");
		close(client_fd);
	}
	printf("Execution Terminated...\n");
	close(server_fd);
	unlink(PATH);
}
