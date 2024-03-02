#include "custom.h"

char* crc(char* generator, char* dataword) {
    int i,j,m=strlen(generator),n=strlen(dataword);
    char remainder[50];
    for(i=0;i<m;i++) remainder[i]=dataword[i];
    for(i=m;i<=n;i++) {
        if(remainder[0]=='1') {
            for(j=1;j<m;j++) {
                remainder[j]=remainder[j]==generator[j]?'0':'1';
            }
        }
        for(j=0;j<m-1;j++) remainder[j]=remainder[j+1];
        remainder[j]=dataword[i];
    }
    remainder[m]='\0';
    char* res=(char*)malloc(50*sizeof(char));
    j=0;
    for(i=0;i<n;i++) {
        if(i<=n-m) res[i]=dataword[i];
        else res[i]=remainder[j++];
    }
    res[i]='\0';
    return res;
}

void main() {
    struct sockaddr_un server_addr;
    int server_fd=socket(AF_UNIX,SOCK_STREAM,0);
    printf("Master Socket Created...\n");
    memset(&server_addr,0,sizeof(struct sockaddr_un));
    server_addr.sun_family=AF_UNIX;
    unlink(SOCKET_PATH);
    Word buff;
    strcpy(server_addr.sun_path,SOCKET_PATH);
    bind(server_fd,(struct sockaddr*)&server_addr,sizeof(struct sockaddr_un));
    listen(server_fd,20);
    while(true) {
        int client_fd=accept(server_fd,NULL,NULL);
        read(client_fd,&buff,sizeof(Word));
        char res[BUFF_SIZE];
        int i,n=strlen(buff.dw),m=strlen(buff.gen);
        for(i=n;i<n+m-1;i++) buff.dw[i]='0';
        strcpy(res,crc(buff.gen,buff.dw));
        write(client_fd,res,sizeof(res));
        close(client_fd);
    }
    close(server_fd);
    unlink(SOCKET_PATH);
}