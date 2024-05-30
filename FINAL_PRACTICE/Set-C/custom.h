#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<netinet/ip.h>
#include<arpa/inet.h>
#include<stdbool.h>
#include<string.h>

#define MAX 50
#define PORT 8080
#define ip "127.0.0.1"

typedef struct {
	char dataword[MAX],generator[MAX];
} Data;
