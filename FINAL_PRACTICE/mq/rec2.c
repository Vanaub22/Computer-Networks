#include "custom.h"

void main() {
	printf("This is Receiver-2. I am waiting for messages...\n");
	int msgid=msgget((key_t)1234,0666);
	my_msg m;
	while(1) {
		bzero(m.mssg,sizeof(m.mssg));
		msgrcv(msgid,&m,sizeof(m.mssg),2,0);
		printf("The message received: %s\n",m.mssg);
		if(strcmp(m.mssg,"Terminate")==0) break;
	}
	printf("Receiver-2 Terminated...\n");
}
