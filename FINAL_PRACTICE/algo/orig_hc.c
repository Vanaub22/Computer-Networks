#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>

void main() {
	char buff[40];
	printf("Enter the dataword: ");
	scanf(" %[^\n]s",buff);
	printf("The dataword is: %s\n",buff);
	int m=strlen(buff),p=0;
		while(pow(2,p)<p+m+1) p++;
		int sz=m+p,i,buff_c=0;
		char finalMsg[sz];
		for(i=0;i<sz;i++) {
			if(ceil(log2(sz-i))==floor(log2(sz-i))) finalMsg[i]='p';
			else finalMsg[i]=buff[buff_c++];
		}
		finalMsg[sz] = '\0';
		int bitsCalc=0;
		while(bitsCalc<p){
			int posi=pow(2,bitsCalc),bitPosi=posi,ones=0;
			while(bitPosi<=sz){
				int j=0;
				while(j<posi) {
					if(finalMsg[sz-(bitPosi+j)]=='1') ones++;
					j++;
				}
				bitPosi+=2*posi;
			}
			if((ones%2)==0) finalMsg[sz-posi]='0';
			else finalMsg[sz-posi]='1';
			bitsCalc++;
		}
	printf("The codeword is: %s\n",finalMsg);
}
