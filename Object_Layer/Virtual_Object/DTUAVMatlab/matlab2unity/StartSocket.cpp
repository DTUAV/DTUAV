
/*
	Author: Yuanlin Yang
	Location: Guangdong University of Technology
	Main implementation content:
	{
		Input parameter: Socket port;
		Output parameter: Server socket(first) and Client socket(second);
		note: The socket ip is all Network Card addresses of this computer,only need ifconfig  Socket Port;
		content: Start a Socket Server and Connect a Socket Client by input port
	}
*/
#include <iostream>
#include "mex.h"
#include <stdio.h>
#include <winsock2.h>
#include <windows.h>

#pragma comment (lib,"ws2_32.lib")
using namespace std;
void mexFunction(int nlhs, mxArray* plhs[], int nrhs, const mxArray* prhs[])
{
	WSADATA wsaData;
	WSAStartup(MAKEWORD(2, 2), &wsaData);
	int isConnected = false;
	double* input;
	input = mxGetPr(prhs[0]);

	int port = *input;

	SOCKET servSock = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);
	sockaddr_in sockAddr;
	memset(&sockAddr, 0, sizeof(sockAddr));
	sockAddr.sin_family = PF_INET;
	sockAddr.sin_addr.s_addr = htonl(INADDR_ANY);
	sockAddr.sin_port = htons(port);
	
	u_long is_non_block = 1;
	int ret = ioctlsocket(servSock, FIONBIO, &is_non_block);
	if (ret != 0)
	{
		perror("set non block failed");
		plhs[0] = mxCreateDoubleMatrix(1, 2, mxREAL);
		double* a;
		a = mxGetPr(plhs[0]);
		*a = 0;
		*(a + 1) = 0;
	}
	else
	{
		bind(servSock, (SOCKADDR*)&sockAddr, sizeof(SOCKADDR));
		listen(servSock, 30);
		SOCKADDR clntAddr;
		int nSize = sizeof(SOCKADDR);
		SOCKET clntSock = accept(servSock, (SOCKADDR*)&clntAddr, &nSize);
		if (clntSock != INVALID_SOCKET)
		{
			isConnected = true;
		}
		while (!isConnected)
		{
			clntSock = accept(servSock, (SOCKADDR*)&clntAddr, &nSize);
			if (clntSock != INVALID_SOCKET)
			{
				isConnected = true;
			}
		}

		plhs[0] = mxCreateDoubleMatrix(1, 2, mxREAL);
		double* a;
		a = mxGetPr(plhs[0]);
		*a = servSock;
		*(a + 1) = clntSock;
		WSACleanup();
	}

	

}
