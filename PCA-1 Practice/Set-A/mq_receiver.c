#include "custom.h"

void main() {
	my_msg m;
	m.type=1;
	int msgid=msgget((key_t)1234,0666);
	msgrcv(msgid,&m,sizeof(my_msg),1,0);
	printf("PROCESS-2: The user-input roll number obtained from Process-1 is: %s\n",m.mssg);
	char roll[MAX_DIGITS];
	strcpy(roll,m.mssg);
	// Reversing the digits
	int n=strlen(roll);
	for(int i=0;i<n/2;i++) {
		char tmp=roll[i];
		roll[i]=roll[n-i-1];
		roll[n-i-1]=tmp;
	}
	printf("PROCESS-2: Output after reversal: %s\n",roll);
}
