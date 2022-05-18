/*
	Author: Yuanlin Yang
	Location: Guangdong University of Technology
	Main implementation content:
	{
		Input parameter: Server socket(first) and Client socket(second);
		Output parameter: Receive Data ;
		content: The provided socket identifier on the server and client sends target velocity to the client;


	}
*/



#include <iostream>
#include "mex.h"
#include <stdio.h>
#include <winsock2.h>
#include <windows.h>

#pragma comment (lib,"ws2_32.lib")


using namespace std;

#pragma pack(1)
struct TargetVelocityMsg
{
	double linear_velocity_x;
	double linear_velocity_y;
	double linear_velocity_z;
	double anger_velocity_x;
	double anger_velocity_y;
	double anger_velocity_z;
};


void mexFunction(int nlhs, mxArray* plhs[], int nrhs, const mxArray* prhs[])
{
	TargetVelocityMsg targetVelocity;
	WSADATA wsaData;
	WSAStartup(MAKEWORD(2, 2), &wsaData);
	//8*1;
	SOCKET servSock = *(mxGetPr(prhs[0]));
	SOCKET clientSock = *(mxGetPr(prhs[0]) + 1);
	targetVelocity.linear_velocity_x = *(mxGetPr(prhs[0]) + 2);
	targetVelocity.linear_velocity_y = *(mxGetPr(prhs[0]) + 3);
	targetVelocity.linear_velocity_z = *(mxGetPr(prhs[0]) + 4);
	targetVelocity.anger_velocity_x = *(mxGetPr(prhs[0]) + 5);
	targetVelocity.anger_velocity_y = *(mxGetPr(prhs[0]) + 6);
	targetVelocity.anger_velocity_z = *(mxGetPr(prhs[0]) + 7);

	plhs[0] = mxCreateDoubleMatrix(1, 3, mxREAL);
	double* a;
	a = mxGetPr(plhs[0]);
	*a = servSock;
	*(a + 1) = clientSock;
	int i = -1;
	i = send(clientSock, (char *)&targetVelocity, sizeof(targetVelocity), NULL);
	if (i == SOCKET_ERROR)
	{
			*(a + 2) = 0;
	}
	else
	{
			*(a + 2) = 1;
	}
	WSACleanup();


}
