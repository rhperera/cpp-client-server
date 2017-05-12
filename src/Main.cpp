#include <stdio.h>
#include <string>
#include <cstdio>
#include <cstring>
#include <thread>
#include "../include/ChatMessage.h"
#include <iostream>
#include <vector>
/*
socket libraries
*/
#include <unistd.h>
#include <sys/time.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <netinet/in.h>

//hard coded port and buffer
#define DEFAULT_BUFLEN 512

using namespace std;

static int connFd;
static vector<int> clients;

void runServer();
void clientHandler(const int& clientId, char *recvbuff);
void broadcast(char *recvbuff);

int main(int argc, char const *argv[])
{
	int pId, portNo, listenFd;
	socklen_t len;
	bool loop = false;
	struct sockaddr_in svrAdd, clntAdd;
	struct hostent *server;

	listenFd = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

	memset(&svrAdd,0, sizeof(svrAdd));

	svrAdd.sin_family = AF_INET;

	int choice=0;
	int portNumber;

	cout << "Host (1) or client (2)?\n";
	cin >> choice;

	if(choice==1)
	{
		cout << "Enter port number:\n";
		cin >> portNumber;

		svrAdd.sin_addr.s_addr = INADDR_ANY;
    	svrAdd.sin_port = htons(portNumber);

    	bind(listenFd, (struct sockaddr *)&svrAdd, sizeof(svrAdd));

    	listen(listenFd, 0);

    	int threadCount = 0;

	    while(threadCount < 3)
	    {
	    	len = sizeof(svrAdd);
	    	connFd = accept(listenFd, (struct sockaddr *)&svrAdd, &len);
	    	if (connFd>0)
	    	{
	    		cout << "Client connected\n";
	    	}
	    	clients.push_back(connFd);

	    	//Create a new handler thread for each client
    		char *recvbuff = new char[1024]();
	    	thread clientHandlerThread(clientHandler,connFd,recvbuff);
	    	clientHandlerThread.join();
	    	threadCount ++;
	    }
	}
	else if(choice==2)
	{
		string hostName;
		cout << "\nEnter host address: ";
		cin >> hostName;
		cout << "\nEnter port number: ";
		cin >> portNumber;

		server = gethostbyname(hostName.c_str());

		if (server == NULL)
		{
			cout << "error in server";
			exit(1);
		}
		else
		{
			cout << "server connected";
		}

		//cout << &server->h_errno;


		memcpy(&svrAdd.sin_addr.s_addr,&server->h_addr,server->h_length);
    	svrAdd.sin_port = htons(portNumber);

    	connect(listenFd,(struct sockaddr*) &svrAdd,sizeof(svrAdd));
    	string b = "";
    	char recvbuff[1024];
    	recv(connFd,recvbuff,sizeof(recvbuff),0);
    	cout << recvbuff;
	}
	else
	{
		cout << "Wrong choice";
	}

	return 0;
}

void runServer()
{
	string b = "";
	while(b != "exit")
	{
		cout << "server:\n";
		getline(cin,b);
    	send(connFd,b.c_str(),b.size(),0);
	}
	exit(1);
}

void clientHandler(const int &clientId, char *recvbuff)
{
	while(1)
	{
    	recv(clientId,recvbuff,sizeof(recvbuff),0);
    	broadcast(recvbuff);
	}
}

void broadcast(char *recvbuff)
{
	for (int i = 0; i < clients.size(); ++i)
	{
		cout << recvbuff;
	}
}