#include "custom.h"

void main() {
	char r[MAX_DIGITS];
	printf("PROCESS-1: Enter your University Roll Number: ");
	scanf("%[^\n]s",r);
	my_msg m;
	m.type=1;
	strcpy(m.mssg,r);
	int msgid=msgget((key_t)1234,0666|IPC_CREAT);
	msgsnd(msgid,&m,sizeof(my_msg),0);
	printf("PROCESS-1: Data sent to Message Queue from Process-1...\n");
}
