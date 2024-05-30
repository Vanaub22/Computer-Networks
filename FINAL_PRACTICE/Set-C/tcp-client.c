#include "custom.h"

void main() {
	struct sockaddr_in server_addr;
	server_addr.sin_addr.s_addr=inet_addr(ip);
	server_addr.sin_port=htons(PORT);
	server_addr.sin_family=AF_INET;
	int sockfd=socket(AF_INET,SOCK_STREAM,0);
	connect(sockfd,(struct sockaddr*)&server_addr,sizeof(struct sockaddr_in));
	while(true) {
		printf("Enter dataword: ");
		// fflush(stdout);
		Data d;
		bzero(&d,sizeof(Data));
		char cw[MAX];
		bzero(cw,sizeof(cw));
		scanf(" %[^\n]s",d.dataword);
		printf("Enter the generator: ");
		scanf(" %[^\n]s",d.generator);
		write(sockfd,&d,sizeof(Data));
		if(!strcmp(d.generator,"stop") || !strcmp(d.dataword,"stop")) break;
		read(sockfd,cw,sizeof(cw));
		printf("Valid codeword received: %s\n",cw);
	}
	printf("Client Execution terminated...\n");
	close(sockfd);		
}
