#include "custom.h"

void main() {
	int msgid=msgget((key_t)1234,0666|IPC_CREAT);
	while(1) {
		char mssg[20];
		int rec;
		printf("Enter your receiver and the message: ");
		scanf("%d %s",&rec,mssg);
		my_msg m1;
		bzero(m1.mssg,sizeof(m1.mssg));
		strcpy(m1.mssg,mssg);
		m1.type=rec;
		printf("Received: %ld %s\n\n",m1.type,m1.mssg);
		msgsnd(msgid,&m1,sizeof(m1.mssg),0);
		printf("Message sent to Receiver-%d via Message Queue...\n",rec);
		printf("Do you want to continue (Y/N)? ");
		char resp;
		scanf(" %c",&resp);
		// getchar();
		if(resp=='N' || resp=='n') break;
	}
	printf("Execution terminated...\n");
	msgctl(msgid,IPC_RMID,NULL);
}
