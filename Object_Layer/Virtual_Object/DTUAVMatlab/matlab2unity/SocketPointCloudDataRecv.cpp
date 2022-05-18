/*
	Author: Yuanlin Yang
	Location: Guangdong University of Technology
	Main implementation content:
	{
		Input parameter: Server socket(first) and Client socket(second);
		Output parameter: Receive Data ;
		content: The socket identifier of the provided server and client accepts the  Lidar information sent by the client;
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
struct pointCloud
{
	double x[1000];
	double y[1000];
	double z[1000];
	double value[1000];
};


void mexFunction(int nlhs, mxArray* plhs[], int nrhs, const mxArray* prhs[])
{
	WSADATA wsaData;
	WSAStartup(MAKEWORD(2, 2), &wsaData);
	pointCloud pointCloudData;



	SOCKET servSock = *(mxGetPr(prhs[0]));
	SOCKET clientSock = *(mxGetPr(prhs[0]) + 1);


	int i = -1;



	while (i == SOCKET_ERROR || i == 0)
	{
		if (i = recv(clientSock, (char*)(&pointCloudData), sizeof(pointCloudData), 0) == sizeof(pointCloudData))
		{
			plhs[0] = mxCreateDoubleMatrix(4, 1000, mxREAL);
			double* a;
			a = mxGetPr(plhs[0]);

			for (int i = 0; i < 1000; i++)
			{
				*(a + 4 * i) = pointCloudData.x[i];
				*(a + 4 * i + 1) = pointCloudData.y[i];
				*(a + 4 * i + 2) = pointCloudData.z[i];
				*(a + 4 * i + 3) = pointCloudData.value[i];
			}


			int M = mxGetM(prhs[0]); //获得矩阵的行数 
			int N = mxGetN(prhs[0]); //获得矩阵的列数 

				   //mexPrintf("%4.3f  ", data[j * M + i]);

		}


	}




	WSACleanup();


}
