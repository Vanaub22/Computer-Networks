#include "custom.h"

char* crc(char* dw, char* gen) {
	char rem[MAX],*res;
	int i,j,m=strlen(gen),n=strlen(dw);
	for(i=n;i<n+m-1;i++) dw[i]='0';
	n=strlen(dw);
	res=(char*)malloc(n*sizeof(char));
	for(i=0;i<m;i++) rem[i]=dw[i];
	for(i=m;i<=n;i++) {
		if(rem[0]=='1') for(j=1;j<m;j++) rem[j]=rem[j]==gen[j]?'0':'1';
		for(j=0;j<m-1;j++) rem[j]=rem[j+1];
		rem[j]=dw[i];
	}
	rem[i]='\0';
	j=0;
	for(i=0;i<n;i++) {
		if(i<=n-m) res[i]=dw[i];
		else res[i]=rem[j++];
	}
	res[i]='\0';
	return res;
}

void main() {
	struct sockaddr_in server_addr;
	bzero(&server_addr,sizeof(server_addr));
	server_addr.sin_family=AF_INET;
	server_addr.sin_port=htons(PORT);
	server_addr.sin_addr.s_addr=inet_addr(ip);
	int sockfd=socket(AF_INET,SOCK_STREAM,0);
	bind(sockfd,(struct sockaddr*)&server_addr,sizeof(struct sockaddr_in));
	listen(sockfd,1);
	printf("Server running...\n");
	int cfd=accept(sockfd,NULL,NULL);	
	Data d;
	while(true) {
		bzero(&d,sizeof(d));
		read(cfd,&d,sizeof(Data));
		if(!strcmp(d.dataword,"stop") || !strcmp(d.generator,"stop")) break;
		char dw[MAX],gen[MAX],cw[MAX];
		bzero(dw,sizeof(dw));
		bzero(gen,sizeof(gen));
		bzero(cw,sizeof(cw));
		strcpy(dw,d.dataword);
		strcpy(gen,d.generator);
		strcpy(cw,crc(dw,gen));
		printf("Generated codeword: %s\nSending to client...\n",cw);
		write(cfd,cw,sizeof(cw));
	}
	close(sockfd);
	printf("Server Execution terminated...\n");
}
