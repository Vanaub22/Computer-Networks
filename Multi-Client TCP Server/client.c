#include "custom.h"

void main() {
	char buffer[1024];
	struct sockaddr_in server,client;
	server.sin_family=AF_INET;
	server.sin_port=htons(PORT_NO);
	server.sin_addr.s_addr=inet_addr("127.0.0.1");	
	int client_fd=socket(AF_INET,SOCK_STREAM,0);
	connect(client_fd,(struct sockaddr*)&server,sizeof(server));
	memset(buffer,0,sizeof(buffer));
	printf("Enter the IPV4 address: ");
	scanf(" %[^\n]s",buffer);
	write(client_fd,buffer,sizeof(buffer));
	read(client_fd,buffer,sizeof(buffer));
	printf("Result: %s\n",buffer);
	close(client_fd);
}
