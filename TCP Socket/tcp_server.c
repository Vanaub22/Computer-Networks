#include "custom.h"

char* bit_stuffing(char *input) {
	char* output=(char*)malloc(1024*sizeof(char));
	int i,j=0,consecutive_ones=0;
     	for(i=0;i<strlen(input);i++) {
     		output[j++]=input[i];
         	if(input[i]=='1') {
         		consecutive_ones++;
         		if(consecutive_ones==5) {
                 	output[j++]='0';
                 	consecutive_ones=0;
             	}
         	}
         	else consecutive_ones=0;
         }
         output[j]='\0';
         return output;
}

void main() {
	char buffer[1024];
	int server_fd,client_fd;
	struct sockaddr_in server,client;
	server.sin_family=AF_INET;
	server.sin_port=htons(PORT_NO);
	server.sin_addr.s_addr=INADDR_ANY;	
	server_fd=socket(AF_INET,SOCK_STREAM,0);
	bind(server_fd,(struct sockaddr*)&server,sizeof(server));
	listen(server_fd,5);
	printf("Master Socket Created...\n");
	while(true) {
		client_fd=accept(server_fd,NULL,NULL);
		printf("Accepted client!!\n");
		memset(buffer,0,sizeof(buffer));
		read(client_fd,buffer,sizeof(buffer));
		printf("Received: %s\n",buffer);
		char ans[MSG_SIZE];
		strcpy(ans,bit_stuffing(buffer));
		printf("Result sent back to client...\n");
		write(client_fd,ans,strlen(ans));
		close(client_fd);
	}
	close(server_fd);
}
