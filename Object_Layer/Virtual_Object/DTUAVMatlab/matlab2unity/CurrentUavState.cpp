/*
	Author: Yuanlin Yang
	Location: Guangdong University of Technology
	Main implementation content:
	{
		Input parameter: Server socket(first) and Client socket(second);
		Output parameter: Receive Data ;
		
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
struct CurrentUavStateMsg
{
 double position_x;
 double position_y;
 double position_z;

 double roll;
 double yaw;
 double pitch;

 double rotation_x;
 double rotation_y;
 double rotation_z;
 double rotation_w;

 double linear_velocity_x;
 double linear_velocity_y;
 double linear_velocity_z;
 double speed;

 double angular_velocity_x;
 double angular_velocity_y;
 double angular_velocity_z;

 double linear_acceleration_x;
 double linear_acceleration_y;
 double linear_acceleration_z;

 double angular_acceleration_x;
 double angular_acceleration_y;
 double angular_acceleration_z;
};


void mexFunction(int nlhs, mxArray* plhs[], int nrhs, const mxArray* prhs[])
{
	WSADATA wsaData;
	WSAStartup(MAKEWORD(2, 2), &wsaData);
	CurrentUavStateMsg uavstate;

	SOCKET servSock = *(mxGetPr(prhs[0]));
	SOCKET clientSock = *(mxGetPr(prhs[0]) + 1);

	int i = -1;
	plhs[0] = mxCreateDoubleMatrix(23, 1, mxREAL);
	double* a;
	a = mxGetPr(plhs[0]);
	bool isGet = false;
	while (i == SOCKET_ERROR || i == 0)
	{
		if (i = recv(clientSock, (char*)(&uavstate), sizeof(uavstate), 0) == sizeof(uavstate))
		{
			*(a) = uavstate.position_x;
			*(a + 1) = uavstate.position_y;
			*(a + 2) = uavstate.position_z;
			*(a + 3) = uavstate.roll;
			*(a + 4) = uavstate.yaw;
			*(a + 5) = uavstate.pitch;
			*(a + 6) = uavstate.rotation_x;
			*(a + 7) = uavstate.rotation_y;
			*(a + 8) = uavstate.rotation_z;
			*(a + 9) = uavstate.rotation_w;
			*(a + 10) = uavstate.linear_velocity_x;
			*(a + 11) = uavstate.linear_velocity_y;
			*(a + 12) = uavstate.linear_velocity_z;
			*(a + 13) = uavstate.speed;
			*(a + 14) = uavstate.angular_velocity_x;
			*(a + 15) = uavstate.angular_velocity_y;
			*(a + 16) = uavstate.angular_velocity_z;
			*(a + 17) = uavstate.linear_acceleration_x;
			*(a + 18) = uavstate.linear_acceleration_y;
			*(a + 19) = uavstate.linear_acceleration_z;
			*(a + 20) = uavstate.angular_acceleration_x;
			*(a + 21) = uavstate.angular_acceleration_y;
			*(a + 22) = uavstate.angular_acceleration_z;
			i = 0;
			isGet = true;
			//int M = mxGetM(prhs[0]); //Get the number of rows of the matrix 
			//int N = mxGetN(prhs[0]); //Get the number of columns of the matrix
				   //mexPrintf("%4.3f  ", data[j * M + i]);
		}
		else
		{
			i = 1;
			if (!isGet)
			{
				*(a) = 1;
				*(a + 1) = 1;
				*(a + 2) = 1;
				*(a + 3) = 1;
				*(a + 4) = 1;
				*(a + 5) = 1;
				*(a + 6) = 1;
				*(a + 7) = 1;
				*(a + 8) = 1;
				*(a + 9) = 1;
				*(a + 10) = 1;
				*(a + 11) = 1;
				*(a + 12) = 1;
				*(a + 13) = 1;
				*(a + 14) = 1;
				*(a + 15) = 1;
				*(a + 16) = 1;
				*(a + 17) = 1;
				*(a + 18) = 1;
				*(a + 19) = 1;
				*(a + 20) = 1;
				*(a + 21) = 1;
				*(a + 22) = 1;
			}

		}
	}




	WSACleanup();


}
