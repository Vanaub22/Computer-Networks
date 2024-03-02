#include "custom.h"

void main() {
	struct sockaddr_un server_addr;
	char in[MAX];
	struct in_addr addr;
	int server_fd=socket(AF_UNIX,SOCK_STREAM,0);
	if(server_fd<0) {
		perror("Failed to create Master Socket");
		exit(0);
	}
	printf("Master Socket created...\n");
	memset(&server_addr,0,sizeof(struct sockaddr_un));
	server_addr.sun_family=AF_UNIX;
	strcpy(server_addr.sun_path,SOCKET_PATH);
	bind(server_fd,(struct sockaddr*)&server_addr,sizeof(struct sockaddr_un));
	listen(server_fd,20);
	while(true) {
		int client_fd=accept(server_fd,NULL,NULL);
		read(client_fd,in,sizeof(in));
		int res=inet_pton(AF_INET,in,&addr);
		write(client_fd,&res,sizeof(res));
		close(client_fd);
	}
	close(server_fd);
}
