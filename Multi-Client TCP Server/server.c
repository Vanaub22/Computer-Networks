#include "custom.h"

void *tcp_thread (void *args) {
	int cfd=*((int*)args);
	struct sockaddr_in sa;
	char buff[MAX],modbuff[MAX];
	int n=read(cfd,buff,MAX);
	printf("Address received from client...%s\n", buff);
	if(inet_pton(AF_INET,buff,&(sa.sin_addr))!=0) strcpy(buff, "YES");
	else strcpy(buff,"NO");
	write(cfd,buff,MAX);
	close(cfd);
}

void main() {
	struct sockaddr_in server,client;
	memset(&server,0,sizeof(struct sockaddr_in));
	int server_fd=socket(AF_INET, SOCK_STREAM, 0);
	server.sin_family=AF_INET;
	server.sin_port=PORT_NO;
	server.sin_addr.s_addr=INADDR_ANY;
	bind(server_fd,(struct sockaddr*)&server,sizeof(struct sockaddr_in));
	listen(server_fd,20);
	while(true) {
		pthread_t th;
		int l=sizeof(client),client_fd=accept(server_fd,NULL,NULL);
		printf("Client Accepted!\n");
		pthread_create(&th,NULL,(void*)tcp_thread,(void*)&client_fd);
	}
	close(server_fd);
}
