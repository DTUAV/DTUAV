/*
	Author: Yuanlin Yang
	Location: Guangdong University of Technology
	Main implementation content:
	{
		Input parameter: Server socket(first) and Client socket(second) and targetposition;
		Output parameter: flag 0 or 1 ;
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
struct TargetLocalPositionMsg
{
	 double position_x;
	 double position_y;
	 double position_z;
	 double rotation_x;
	 double rotation_y;
	 double rotation_z;
	 double rotation_w;
};


void mexFunction(int nlhs, mxArray* plhs[], int nrhs, const mxArray* prhs[])
{
	TargetLocalPositionMsg targetLocalPosition;
	WSADATA wsaData;
	WSAStartup(MAKEWORD(2, 2), &wsaData);
	//8*1;
	SOCKET servSock = *(mxGetPr(prhs[0]));
	SOCKET clientSock = *(mxGetPr(prhs[0]) + 1);
	targetLocalPosition.position_x = *(mxGetPr(prhs[0]) + 2);
	targetLocalPosition.position_y = *(mxGetPr(prhs[0]) + 3);
	targetLocalPosition.position_z = *(mxGetPr(prhs[0]) + 4);
	targetLocalPosition.rotation_x = *(mxGetPr(prhs[0]) + 5);
	targetLocalPosition.rotation_y = *(mxGetPr(prhs[0]) + 6);
	targetLocalPosition.rotation_z = *(mxGetPr(prhs[0]) + 7);
	targetLocalPosition.rotation_w = *(mxGetPr(prhs[0]) + 8);

	plhs[0] = mxCreateDoubleMatrix(1, 3, mxREAL);
	double* a;
	a = mxGetPr(plhs[0]);
	*a = servSock;
	*(a + 1) = clientSock;
	int i = -1;
	i = send(clientSock, (char *)&targetLocalPosition, sizeof(targetLocalPosition), NULL);
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
