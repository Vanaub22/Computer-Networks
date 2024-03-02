// AIM: To perform CRC checking in C
#include<stdio.h>
#include<math.h>
#include<stdlib.h>
#include<string.h>
#include<limits.h>


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
    char dataword[50],generator[50];
    printf("Enter dataword: ");
    scanf(" %[^\n]s",dataword);
    printf("Enter generator: ");
    scanf(" %[^\n]s",generator);
    int i,n=strlen(dataword),m=strlen(generator);
    for(i=n;i<n+m-1;i++) dataword[i]='0';
    printf("Obtained Codeword: %s\n",crc(generator,dataword));
}