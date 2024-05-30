#include "custom.h"

void main() {
	int msgid=msgget((key_t)1234,0666);
	my_msg m;
	printf("This is Receiver-1. I am waiting for messages...\n");
	while(1) {
		bzero(m.mssg,sizeof(m.mssg));
		msgrcv(msgid,&m,sizeof(m.mssg),1,0);
		printf("The message received is: %s\n",m.mssg);
		if(strcmp(m.mssg,"Terminate")==0) break;
	}
	printf("Receiver-1 Terminated...\n");
}
