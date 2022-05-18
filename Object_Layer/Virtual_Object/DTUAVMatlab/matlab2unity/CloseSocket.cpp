/*
	Author: Yuanlin Yang
	Location: Guangdong University of Technology
	Main implementation content:
	{
		Input parameter: Server socket(first) and Client socket(second);
		Output parameter: NULL ;
		content: Close a Socket Server and Connect a Socket Client by input Server socket and Client socket;
		这个函数主要实现：
		(1)由提供的服务端和客户端的socket标识符关闭一个Socket 通信
		
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

	SOCKET servSock = *(mxGetPr(prhs[0]));
	SOCKET clientSock = *(mxGetPr(prhs[0]) + 1);

	plhs[0] = mxCreateDoubleMatrix(1, 2, mxREAL);
	double* a;
	a = mxGetPr(plhs[0]);
	*a = servSock;
	*(a + 1) = clientSock;
	
	closesocket(clientSock);
	closesocket(servSock);

	WSACleanup();


}