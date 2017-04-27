#include<stdio.h>
#include "../include/chatmessage.h"

/*
socket libraries
*/
#include <unistd.h>
#include <sys/time.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netdb.h>
#include <arpa/inet.h>

//hard coded port and buffer
#define PORT "5000"
#define DEFAULT_BUFLEN 512

int main(int argc, char const *argv[])
{
	printf("Hello\n");
	return 0;
}