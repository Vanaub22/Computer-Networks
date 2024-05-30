#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>
#include<math.h>
#include<stdbool.h>

#define MAX 40

char* hammingcode(char* dw) {
	int m=strlen(dw),p=0;
	while(pow(2,p)<m+p+1) p++;
	int i,j=0,sz=m+p;
	char* finalMsg=(char*)malloc(sz*sizeof(char));
	for(i=0;i<sz;i++) {
		if(ceil(log2(sz-i))==floor(log2(sz-i))) finalMsg[i]='p';
		else finalMsg[i]=dw[j++];
	}
	i=0;
	while(i<p) {
		int posi=pow(2,i),bp=posi,ones=0;
		while(bp<=sz) {
			j=0;
			while(j<posi) {
				if(finalMsg[sz-(bp+j)]=='1') ones++;
				j++;
			}
			bp+=2*posi;
		}
		finalMsg[sz-posi]='0'+ones%2;
		i++;
	}
	return finalMsg;
}

void main() {
	char dw[MAX];
	printf("Enter the dataword: ");
	scanf("%s",dw);
	printf("Dataword: %s | Codeword: %s\n",dw,hammingcode(dw));
}
