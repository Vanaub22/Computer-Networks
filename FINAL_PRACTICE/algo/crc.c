#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<stdbool.h>

#define MAX 50

void main(int argc, char** argv) {
	char dw[MAX],gen[MAX],rem[MAX],cw[MAX];
	strcpy(dw,argv[1]);
	strcpy(gen,argv[2]);
	int i,j,m=strlen(gen),n=strlen(dw);
	for(i=n;i<n+m-1;i++) dw[i]='0';
	dw[i]='\0';
	n=strlen(dw);
	for(i=0;i<m;i++) rem[i]=dw[i];
	for(i=m;i<=n;i++) {
		if(rem[0]=='1') for(j=1;j<m;j++) rem[j]=rem[j]==gen[j]?'0':'1';
		for(j=0;j<m-1;j++) rem[j]=rem[j+1];
		rem[j]=dw[i];
	}
	printf("The remainder to be appended to the payload: %s\n",rem);
	j=0;
	for(i=0;i<n;i++) {
		if(i<=n-m) cw[i]=dw[i];
		else cw[i]=rem[j++];
	}
	cw[i]='\0';
	printf("The generated valid CRC codeword: %s\n",cw);	
}
