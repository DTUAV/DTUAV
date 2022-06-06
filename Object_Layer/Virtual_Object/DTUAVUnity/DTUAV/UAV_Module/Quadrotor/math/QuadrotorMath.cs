/*
© Guangdong University of Technology,
© The Laboratory of Intelligent Decision and Cooperative Control,
© 2021-2022,
© Author: Yuanlin Yang (yongwang0808@163.com)

Licensed under the Apache License, Version 2.0 (the "License");
you may not use this file except in compliance with the License.
You may obtain a copy of the License at
<http://www.apache.org/licenses/LICENSE-2.0>.
Unless required by applicable law or agreed to in writing, software
distributed under the License is distributed on an "AS IS" BASIS,
WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
See the License for the specific language governing permissions and
limitations under the License.
*/
using System;
using System.Collections;
using System.Collections.Generic;
using System.Runtime.InteropServices;
using Unity.VisualScripting;
using UnityEngine;

namespace DTUAV.Quadrotor.QuadrotorMath.TF
{
    public class QuadrotorTF
    {
        public static QuadrotorVector3 Unity2Uav(QuadrotorVector3 tfUnity)
        {
            double x = tfUnity.x;
            tfUnity.x = tfUnity.z;
            tfUnity.z = -tfUnity.y;
            tfUnity.y = x;
            return tfUnity;
        }

        public static Vector3 Unity2Uav(Vector3 tfUnity)
        {
            float x = tfUnity.x;
            tfUnity.x = tfUnity.z;
            tfUnity.z = -tfUnity.y;
            tfUnity.y = x;
            return tfUnity;
        }

        public static QuadrotorVector3 Uav2Unity(QuadrotorVector3 tfUav)
        {
            double x = tfUav.x;
            tfUav.x = tfUav.y;
            tfUav.y = -tfUav.z;
            tfUav.z = x;
            return tfUav;
        }

        public static Vector3 Uav2Unity(Vector3 tfUav)
        {
            float x = tfUav.x;
            tfUav.x = tfUav.y;
            tfUav.y = -tfUav.z;
            tfUav.z = x;
            return tfUav;
        }

        public static QuadrotorVector3 Ros2Uav(QuadrotorVector3 tfRos)
        {
            tfRos.y = -tfRos.y;
            tfRos.z = -tfRos.z;
            return tfRos;
        }
        public static Vector3 Ros2Uav(Vector3 tfRos)
        {
            tfRos.y = -tfRos.y;
            tfRos.z = -tfRos.z;
            return tfRos;
        }
        public static QuadrotorVector3 Uav2Ros(QuadrotorVector3 tfUav)
        {
            tfUav.y = -tfUav.y;
            tfUav.z = -tfUav.z;
            return tfUav;
        }

        public static Vector3 Uav2Ros(Vector3 tfUav)
        {
            tfUav.y = -tfUav.y;
            tfUav.z = -tfUav.z;
            return tfUav;
        }

        public static QuadrotorVector3 Unity2Ros(QuadrotorVector3 tfUnity)
        {
            double x = tfUnity.x;
            tfUnity.x = tfUnity.z;
            tfUnity.z = tfUnity.y;
            tfUnity.y = -x;
            return tfUnity;
        }

        public static Vector3 Unity2Ros(Vector3 tfUnity)
        {
            float x = tfUnity.x;
            tfUnity.x = tfUnity.z;
            tfUnity.z = tfUnity.y;
            tfUnity.y = -x;
            return tfUnity;
        }

        public static QuadrotorVector3 Ros2Unity(QuadrotorVector3 tfRos)
        {
            double x = tfRos.x;
            tfRos.x = -tfRos.y;
            tfRos.y = tfRos.z;
            tfRos.z = x;
            return tfRos;
        }
        public static Vector3 Ros2Unity(Vector3 tfRos)
        {
            float x = tfRos.x;
            tfRos.x = -tfRos.y;
            tfRos.y = tfRos.z;
            tfRos.z = x;
            return tfRos;
        }

    }
}

namespace DTUAV.Quadrotor.QuadrotorMath
{

    public class QuadrotorMatrix33
    {
        private double[,] _data;
        private int _row;
        private int _col;
        public QuadrotorMatrix33()
        {
            _data = new double[3,3];
            _row = 3;
            _col = 3;
        }


        public static QuadrotorMatrix33 operator +(QuadrotorMatrix33 outMatrix33, QuadrotorMatrix33 inMatrix33)
        {
            for (int i = 0; i < 3; ++i)
            {
                for (int j = 0; j < 3; ++j)
                {
                    outMatrix33._data[i, j] += inMatrix33._data[i, j];
                }
            }

            return outMatrix33;
        }
        public static QuadrotorMatrix33 operator -(QuadrotorMatrix33 outMatrix33, QuadrotorMatrix33 inMatrix33)
        {
            for (int i = 0; i < 3; ++i)
            {
                for (int j = 0; j < 3; ++j)
                {
                    outMatrix33._data[i, j] -= inMatrix33._data[i, j];
                }
            }

            return outMatrix33;
        }

        public static QuadrotorMatrix33 operator *(QuadrotorMatrix33 outMatrix33, QuadrotorMatrix33 inMatrix33)
        {
            QuadrotorMatrix33 ret = new QuadrotorMatrix33();
            ret._data[0, 0] = outMatrix33._data[0, 0] * inMatrix33._data[0, 0] +
                              outMatrix33._data[0, 1] * inMatrix33._data[1, 0] +
                              outMatrix33._data[0, 2] * inMatrix33._data[2, 0];
            ret._data[0, 1] = outMatrix33._data[0, 0] * inMatrix33._data[0, 1] +
                              outMatrix33._data[0, 1] * inMatrix33._data[1, 1] +
                              outMatrix33._data[0, 2] * inMatrix33._data[2, 1];
            ret._data[0, 2] = outMatrix33._data[0, 0] * inMatrix33._data[0, 2] +
                              outMatrix33._data[0, 1] * inMatrix33._data[1, 2] +
                              outMatrix33._data[0, 2] * inMatrix33._data[2, 2];
            ret._data[1, 0] = outMatrix33._data[1, 0] * inMatrix33._data[0, 0] +
                              outMatrix33._data[1, 1] * inMatrix33._data[1, 0] +
                              outMatrix33._data[1, 2] * inMatrix33._data[2, 0];
            ret._data[1, 1] = outMatrix33._data[1, 0] * inMatrix33._data[0, 1] +
                              outMatrix33._data[1, 1] * inMatrix33._data[1, 1] +
                              outMatrix33._data[1, 2] * inMatrix33._data[2, 1];
            ret._data[1, 2] = outMatrix33._data[1, 0] * inMatrix33._data[0, 2] +
                              outMatrix33._data[1, 1] * inMatrix33._data[1, 2] +
                              outMatrix33._data[1, 2] * inMatrix33._data[2, 2];
            ret._data[2, 0] = outMatrix33._data[2, 0] * inMatrix33._data[0, 0] +
                              outMatrix33._data[2, 1] * inMatrix33._data[1, 0] +
                              outMatrix33._data[2, 2] * inMatrix33._data[2, 0];
            ret._data[2, 1] = outMatrix33._data[2, 0] * inMatrix33._data[0, 1] +
                              outMatrix33._data[2, 1] * inMatrix33._data[1, 1] +
                              outMatrix33._data[2, 2] * inMatrix33._data[2, 1];
            ret._data[2, 2] = outMatrix33._data[2, 0] * inMatrix33._data[0, 2] +
                              outMatrix33._data[2, 1] * inMatrix33._data[1, 2] +
                              outMatrix33._data[2, 2] * inMatrix33._data[2, 2];
            return ret;
        }

        public static QuadrotorMatrix33 operator -(QuadrotorMatrix33 matrix)
        {
            matrix._data[0, 0] = -matrix._data[0, 0];
            matrix._data[0, 1] = -matrix._data[0, 1];
            matrix._data[0, 2] = -matrix._data[0, 2];
            matrix._data[1, 0] = -matrix._data[1, 0];
            matrix._data[1, 1] = -matrix._data[1, 1];
            matrix._data[1, 2] = -matrix._data[1, 2];
            matrix._data[2, 0] = -matrix._data[2, 0];
            matrix._data[2, 1] = -matrix._data[2, 1];
            matrix._data[2, 2] = -matrix._data[2, 2];
            return matrix;
        }

        public static QuadrotorMatrix33 Inv(QuadrotorMatrix33 matrix)
        {
            double jxx = matrix._data[0,0];
                QuadrotorMatrix33 ret = new QuadrotorMatrix33();
                ret._data[0, 0] = (matrix._data[1, 1] * matrix._data[2, 2] - matrix._data[1, 2] * matrix._data[2, 1]) /
                                  (matrix._data[0, 0] * matrix._data[1, 1] * matrix._data[2, 2] -
                                   matrix._data[0, 0] * matrix._data[1, 2] * matrix._data[2, 1] -
                                   matrix._data[0, 1] * matrix._data[1, 0] * matrix._data[2, 2] +
                                   matrix._data[0, 1] * matrix._data[1, 2] * matrix._data[2, 0] +
                                   matrix._data[0, 2] * matrix._data[1, 0] * matrix._data[2, 1] -
                                   matrix._data[0, 2] * matrix._data[1, 1] * matrix._data[2, 0]);
                ret._data[0, 1] = -(matrix._data[0, 1] * matrix._data[2, 2] - matrix._data[0, 2] * matrix._data[2, 1]) /
                                  (matrix._data[0, 0] * matrix._data[1, 1] * matrix._data[2, 2] -
                                   matrix._data[0, 0] * matrix._data[1, 2] * matrix._data[2, 1] -
                                   matrix._data[0, 1] * matrix._data[1, 0] * matrix._data[2, 2] +
                                   matrix._data[0, 1] * matrix._data[1, 2] * matrix._data[2, 0] +
                                   matrix._data[0, 2] * matrix._data[1, 0] * matrix._data[2, 1] -
                                   matrix._data[0, 2] * matrix._data[1, 1] * matrix._data[2, 0]);
                ret._data[0, 2] = (matrix._data[0, 1] * matrix._data[1, 2] - matrix._data[0, 2] * matrix._data[1, 1]) /
                                  (matrix._data[0, 0] * matrix._data[1, 1] * matrix._data[2, 2] -
                                   matrix._data[0, 0] * matrix._data[1, 2] * matrix._data[2, 1] -
                                   matrix._data[0, 1] * matrix._data[1, 0] * matrix._data[2, 2] +
                                   matrix._data[0, 1] * matrix._data[1, 2] * matrix._data[2, 0] +
                                   matrix._data[0, 2] * matrix._data[1, 0] * matrix._data[2, 1] -
                                   matrix._data[0, 2] * matrix._data[1, 1] * matrix._data[2, 0]);
                ret._data[1, 0] = -(matrix._data[1, 0] * matrix._data[2, 2] - matrix._data[1, 2] * matrix._data[2, 0]) /
                                  (matrix._data[0, 0] * matrix._data[1, 1] * matrix._data[2, 2] -
                                   matrix._data[0, 0] * matrix._data[1, 2] * matrix._data[2, 1] -
                                   matrix._data[0, 1] * matrix._data[1, 0] * matrix._data[2, 2] +
                                   matrix._data[0, 1] * matrix._data[1, 2] * matrix._data[2, 0] +
                                   matrix._data[0, 2] * matrix._data[1, 0] * matrix._data[2, 1] -
                                   matrix._data[0, 2] * matrix._data[1, 1] * matrix._data[2, 0]);
                ret._data[1, 1] = (matrix._data[0, 0] * matrix._data[2, 2] - matrix._data[0, 2] * matrix._data[2, 0]) /
                                  (matrix._data[0, 0] * matrix._data[1, 1] * matrix._data[2, 2] -
                                   matrix._data[0, 0] * matrix._data[1, 2] * matrix._data[2, 1] -
                                   matrix._data[0, 1] * matrix._data[1, 0] * matrix._data[2, 2] +
                                   matrix._data[0, 1] * matrix._data[1, 2] * matrix._data[2, 0] +
                                   matrix._data[0, 2] * matrix._data[1, 0] * matrix._data[2, 1] -
                                   matrix._data[0, 2] * matrix._data[1, 1] * matrix._data[2, 0]);
                ret._data[1, 2] = -(matrix._data[0, 0] * matrix._data[1, 2] - matrix._data[0, 2] * matrix._data[1, 0]) /
                                  (matrix._data[0, 0] * matrix._data[1, 1] * matrix._data[2, 2] -
                                   matrix._data[0, 0] * matrix._data[1, 2] * matrix._data[2, 1] -
                                   matrix._data[0, 1] * matrix._data[1, 0] * matrix._data[2, 2] +
                                   matrix._data[0, 1] * matrix._data[1, 2] * matrix._data[2, 0] +
                                   matrix._data[0, 2] * matrix._data[1, 0] * matrix._data[2, 1] -
                                   matrix._data[0, 2] * matrix._data[1, 1] * matrix._data[2, 0]);
                ret._data[2, 0] = (matrix._data[1, 0] * matrix._data[2, 1] - matrix._data[1, 1] * matrix._data[2, 0]) /
                                  (matrix._data[0, 0] * matrix._data[1, 1] * matrix._data[2, 2] -
                                   matrix._data[0, 0] * matrix._data[1, 2] * matrix._data[2, 1] -
                                   matrix._data[0, 1] * matrix._data[1, 0] * matrix._data[2, 2] +
                                   matrix._data[0, 1] * matrix._data[1, 2] * matrix._data[2, 0] +
                                   matrix._data[0, 2] * matrix._data[1, 0] * matrix._data[2, 1] -
                                   matrix._data[0, 2] * matrix._data[1, 1] * matrix._data[2, 0]);
                ret._data[2, 1] = -(matrix._data[0, 0] * matrix._data[2, 1] - matrix._data[0, 1] * matrix._data[2, 0]) /
                                  (matrix._data[0, 0] * matrix._data[1, 1] * matrix._data[2, 2] -
                                   matrix._data[0, 0] * matrix._data[1, 2] * matrix._data[2, 1] -
                                   matrix._data[0, 1] * matrix._data[1, 0] * matrix._data[2, 2] +
                                   matrix._data[0, 1] * matrix._data[1, 2] * matrix._data[2, 0] +
                                   matrix._data[0, 2] * matrix._data[1, 0] * matrix._data[2, 1] -
                                   matrix._data[0, 2] * matrix._data[1, 1] * matrix._data[2, 0]);
                ret._data[2, 2] = (matrix._data[0, 0] * matrix._data[1, 1] - matrix._data[0, 1] * matrix._data[1, 0]) /
                                  (matrix._data[0, 0] * matrix._data[1, 1] * matrix._data[2, 2] -
                                   matrix._data[0, 0] * matrix._data[1, 2] * matrix._data[2, 1] -
                                   matrix._data[0, 1] * matrix._data[1, 0] * matrix._data[2, 2] +
                                   matrix._data[0, 1] * matrix._data[1, 2] * matrix._data[2, 0] +
                                   matrix._data[0, 2] * matrix._data[1, 0] * matrix._data[2, 1] -
                                   matrix._data[0, 2] * matrix._data[1, 1] * matrix._data[2, 0]);
            return ret;
        }
        public static QuadrotorVector3 operator*(QuadrotorMatrix33 matrix33, QuadrotorVector3 vector3)
        {
            QuadrotorVector3 ret = new QuadrotorVector3();
            ret.x = matrix33._data[0, 0] * vector3.x + matrix33._data[0, 1] * vector3.y +
                    matrix33._data[0, 2] * vector3.z;
            ret.y = matrix33._data[1, 0] * vector3.x + matrix33._data[1, 1] * vector3.y +
                    matrix33._data[1, 2] * vector3.z;
            ret.z = matrix33._data[2, 0] * vector3.x + matrix33._data[2, 1] * vector3.y +
                    matrix33._data[2, 2] * vector3.z;
            return ret;
        }

        public QuadrotorMatrix33(QuadrotorMatrix33 matrix)
        {
            _data = matrix._data;
            _row = 3;
            _col = 3;
        }

        public bool Set(int i, int j, double value)
        {
            if (i < _row && i >= 0 && j < _col && j >= 0)
            {
                _data[i, j] = value;
                return true;
            }
            else
            {
                Debug.LogError("QuadrotorMatrix33----i-j-error");
                return false;
            }
                

        }
        public double Get(int i, int j)
        {
            if(i<_row&&i>=0&&j<_col&&j>=0)
                return _data[i, j];
            else
            {
                Debug.LogError("QuadrotorMatrix33----i-j-error");
                return Double.NaN;
            }
        }


    }

    public struct QuadrotorTargetPosition
    {
        public double x;
        public double y;
        public double z;
        public double yaw;

        public QuadrotorTargetPosition(double initX, double initY, double initZ, double initYaw)
        {
            x = initX;
            y = initY;
            z = initZ;
            yaw = initYaw;
        }
    }

    public struct QuadrotorVector2
    {
        public double x;
        public double y;

        public QuadrotorVector2(double initX, double initY)
        {
            x = initX;
            y = initY;
        }

        public static QuadrotorVector2 operator +(QuadrotorVector2 outVector2, QuadrotorVector2 inVector2)
        {
            outVector2.x += inVector2.x;
            outVector2.y += inVector2.y;
            return outVector2;
        }
        public static QuadrotorVector2 operator -(QuadrotorVector2 outVector2, QuadrotorVector2 inVector2)
        {
            outVector2.x -= inVector2.x;
            outVector2.y -= inVector2.y;
            return outVector2;
        }
        public static QuadrotorVector2 operator -(QuadrotorVector2 outVector2)
        {
            outVector2.x = -outVector2.x;
            outVector2.y = -outVector2.y;
            return outVector2;
        }

    }

    public struct QuadrotorVector3
    {
        public double x;
        public double y;
        public double z;

        public QuadrotorVector3(double initX, double initY,double initZ)
        {
            x = initX;
            y = initY;
            z = initZ;
        }

        public static QuadrotorVector3 operator +(QuadrotorVector3 outVector3, QuadrotorVector3 inVector3)
        {
            outVector3.x += inVector3.x;
            outVector3.y += inVector3.y;
            outVector3.z += inVector3.z;
            return outVector3;
        }
        public static QuadrotorVector3 operator -(QuadrotorVector3 outVector3, QuadrotorVector3 inVector3)
        {
            outVector3.x -= inVector3.x;
            outVector3.y -= inVector3.y;
            outVector3.z -= inVector3.z;
            return outVector3;
        }
        public static QuadrotorVector3 operator -(QuadrotorVector3 outVector3)
        {
            outVector3.x = -outVector3.x;
            outVector3.y = -outVector3.y;
            outVector3.z = -outVector3.z;
            return outVector3;
        }

        public static QuadrotorVector3 operator *(QuadrotorVector3 outVector3, QuadrotorVector3 inVector3)
        {
            outVector3.x *= inVector3.x;
            outVector3.y *= inVector3.y;
            outVector3.z *= inVector3.z;
            return outVector3;
        }

        public static QuadrotorVector3 operator *(QuadrotorVector3 outVector3, double value)
        {
            outVector3.x *= value;
            outVector3.y *= value;
            outVector3.z *= value;
            return outVector3;
        }

        public static double dot(QuadrotorVector3 outVector3, QuadrotorVector3 inVector3)
        {
            return (outVector3.x * inVector3.x + outVector3.y * inVector3.y + outVector3.z * inVector3.z);
        }


    }

    public struct QuadrotorState
    {
        //The position for Quadrotor
        public double PosX;
        public double PosY;
        public double PosZ;
        //The Linear Velocity for Quadrotor
        public double VelX;
        public double VelY;
        public double VelZ;
        //The Acceleration for Quadrotor
        public double AccX;
        public double AccY;
        public double AccZ;
        //The Attitude Angle for Quadrotor
        public double Roll;
        public double Pitch;
        public double Yaw;
        //The Attitude Angle Velocity for Quadrotor
        public double VelRoll;
        public double VelPitch;
        public double VelYaw;
        //The Attitude Angle Acceleration for Quadrotor
        public double AccRoll;
        public double AccPitch;
        public double AccYaw;

        //The Rotation Velocity for Quadrotor in body coordinate system
        public double OmegaX;
        public double OmegaY;
        public double OmegaZ;

        //The Rotation Acceleration for Quadrotor in body coordinate system
        public double OmegaAccX;
        public double OmegaAccY;
        public double OmegaAccZ;

        public static QuadrotorState operator *(double value,QuadrotorState stateOut)
        {
            stateOut.PosX = stateOut.PosX * value;
            stateOut.PosY = stateOut.PosY * value;
            stateOut.PosZ = stateOut.PosZ * value;
            stateOut.VelX = stateOut.VelX * value;
            stateOut.VelY = stateOut.VelY * value;
            stateOut.VelZ = stateOut.VelZ * value;
            stateOut.AccX = stateOut.AccX * value;
            stateOut.AccY = stateOut.AccY * value;
            stateOut.AccZ = stateOut.AccZ * value;
            stateOut.Pitch = stateOut.Pitch * value;
            stateOut.Roll = stateOut.Roll * value;
            stateOut.Yaw = stateOut.Yaw * value;
            stateOut.VelPitch = stateOut.VelPitch * value;
            stateOut.VelRoll = stateOut.VelRoll * value;
            stateOut.VelYaw = stateOut.VelYaw * value;
            stateOut.AccPitch = stateOut.AccPitch * value;
            stateOut.AccRoll = stateOut.AccRoll * value;
            stateOut.AccYaw = stateOut.AccYaw * value;
            stateOut.OmegaAccX = stateOut.OmegaAccX * value;
            stateOut.OmegaAccY = stateOut.OmegaAccY * value;
            stateOut.OmegaAccZ = stateOut.OmegaAccZ * value;
            stateOut.OmegaX = stateOut.OmegaX * value;
            stateOut.OmegaY = stateOut.OmegaY * value;
            stateOut.OmegaZ = stateOut.OmegaZ * value;
            return stateOut;
        }
        public static QuadrotorState operator *(QuadrotorState stateOut, double value)
        {
            stateOut.PosX = stateOut.PosX * value;
            stateOut.PosY = stateOut.PosY * value;
            stateOut.PosZ = stateOut.PosZ * value;
            stateOut.VelX = stateOut.VelX * value;
            stateOut.VelY = stateOut.VelY * value;
            stateOut.VelZ = stateOut.VelZ * value;
            stateOut.AccX = stateOut.AccX * value;
            stateOut.AccY = stateOut.AccY * value;
            stateOut.AccZ = stateOut.AccZ * value;
            stateOut.Pitch = stateOut.Pitch * value;
            stateOut.Roll = stateOut.Roll * value;
            stateOut.Yaw = stateOut.Yaw * value;
            stateOut.VelPitch = stateOut.VelPitch * value;
            stateOut.VelRoll = stateOut.VelRoll * value;
            stateOut.VelYaw = stateOut.VelYaw * value;
            stateOut.AccPitch = stateOut.AccPitch * value;
            stateOut.AccRoll = stateOut.AccRoll * value;
            stateOut.AccYaw = stateOut.AccYaw * value;
            stateOut.OmegaAccX = stateOut.OmegaAccX * value;
            stateOut.OmegaAccY = stateOut.OmegaAccY * value;
            stateOut.OmegaAccZ = stateOut.OmegaAccZ * value;
            stateOut.OmegaX = stateOut.OmegaX * value;
            stateOut.OmegaY = stateOut.OmegaY * value;
            stateOut.OmegaZ = stateOut.OmegaZ * value;
            return stateOut;
        }

        public static QuadrotorState operator /(QuadrotorState stateOut, double value)
        {
            if (value > 10e-10)
            {
                stateOut.PosX = stateOut.PosX / value;
                stateOut.PosY = stateOut.PosY / value;
                stateOut.PosZ = stateOut.PosZ / value;
                stateOut.VelX = stateOut.VelX / value;
                stateOut.VelY = stateOut.VelY / value;
                stateOut.VelZ = stateOut.VelZ / value;
                stateOut.AccX = stateOut.AccX / value;
                stateOut.AccY = stateOut.AccY / value;
                stateOut.AccZ = stateOut.AccZ / value;
                stateOut.Pitch = stateOut.Pitch / value;
                stateOut.Roll = stateOut.Roll / value;
                stateOut.Yaw = stateOut.Yaw / value;
                stateOut.VelPitch = stateOut.VelPitch / value;
                stateOut.VelRoll = stateOut.VelRoll / value;
                stateOut.VelYaw = stateOut.VelYaw / value;
                stateOut.AccPitch = stateOut.AccPitch / value;
                stateOut.AccRoll = stateOut.AccRoll / value;
                stateOut.AccYaw = stateOut.AccYaw / value;
                stateOut.OmegaAccX = stateOut.OmegaAccX / value;
                stateOut.OmegaAccY = stateOut.OmegaAccY / value;
                stateOut.OmegaAccZ = stateOut.OmegaAccZ / value;
                stateOut.OmegaX = stateOut.OmegaX / value;
                stateOut.OmegaY = stateOut.OmegaY / value;
                stateOut.OmegaZ = stateOut.OmegaZ / value;
                
            }
            return stateOut;
        }

        public static QuadrotorState operator +(QuadrotorState stateOut, QuadrotorState stateIn)
        {
            stateOut.PosX += stateIn.PosX;
            stateOut.PosY += stateIn.PosY;
            stateOut.PosZ += stateIn.PosZ;
            stateOut.VelX += stateIn.VelX;
            stateOut.VelY += stateIn.VelY;
            stateOut.VelZ += stateIn.VelZ;
            stateOut.AccX += stateIn.AccX;
            stateOut.AccY += stateIn.AccY;
            stateOut.AccZ += stateIn.AccZ;
            stateOut.Pitch += stateIn.Pitch;
            stateOut.Roll += stateIn.Roll;
            stateOut.Yaw += stateIn.Yaw;
            stateOut.VelPitch += stateIn.VelPitch;
            stateOut.VelRoll += stateIn.VelRoll;
            stateOut.VelYaw += stateIn.VelYaw;
            stateOut.AccPitch += stateIn.AccPitch;
            stateOut.AccRoll += stateIn.AccRoll;
            stateOut.AccYaw += stateIn.AccYaw;
            stateOut.OmegaAccX += stateIn.OmegaAccX;
            stateOut.OmegaAccY += stateIn.OmegaAccY;
            stateOut.OmegaAccZ += stateIn.OmegaAccZ;
            stateOut.OmegaX += stateIn.OmegaX;
            stateOut.OmegaY += stateIn.OmegaY;
            stateOut.OmegaZ += stateIn.OmegaZ;
            return stateOut;
        }

        public static QuadrotorState operator -(QuadrotorState stateOut, QuadrotorState stateIn)
        {
            stateOut.PosX -= stateIn.PosX;
            stateOut.PosY -= stateIn.PosY;
            stateOut.PosZ -= stateIn.PosZ;
            stateOut.VelX -= stateIn.VelX;
            stateOut.VelY -= stateIn.VelY;
            stateOut.VelZ -= stateIn.VelZ;
            stateOut.AccX -= stateIn.AccX;
            stateOut.AccY -= stateIn.AccY;
            stateOut.AccZ -= stateIn.AccZ;
            stateOut.Pitch -= stateIn.Pitch;
            stateOut.Roll -= stateIn.Roll;
            stateOut.Yaw -= stateIn.Yaw;
            stateOut.VelPitch -= stateIn.VelPitch;
            stateOut.VelRoll -= stateIn.VelRoll;
            stateOut.VelYaw -= stateIn.VelYaw;
            stateOut.AccPitch -= stateIn.AccPitch;
            stateOut.AccRoll -= stateIn.AccRoll;
            stateOut.AccYaw -= stateIn.AccYaw;
            stateOut.OmegaAccX -= stateIn.OmegaAccX;
            stateOut.OmegaAccY -= stateIn.OmegaAccY;
            stateOut.OmegaAccZ -= stateIn.OmegaAccZ;
            stateOut.OmegaX -= stateIn.OmegaX;
            stateOut.OmegaY -= stateIn.OmegaY;
            stateOut.OmegaZ -= stateIn.OmegaZ;
            return stateOut;
        }

    }

    public struct QuadrotorInput
    {
        //The Target Force.
        public double F;
        //The Target Torque
        public double Tx;
        public double Ty;
        public double Tz;

        public static QuadrotorInput operator +(QuadrotorInput outInput, QuadrotorInput inInput)
        {
            outInput.F += inInput.F;
            outInput.Tx += inInput.Tx;
            outInput.Ty += inInput.Ty;
            outInput.Tz += inInput.Tz;
            return outInput;
        }
        public static QuadrotorInput operator -(QuadrotorInput outInput, QuadrotorInput inInput)
        {
            outInput.F -= inInput.F;
            outInput.Tx -= inInput.Tx;
            outInput.Ty -= inInput.Ty;
            outInput.Tz -= inInput.Tz;
            return outInput;
        }

    }
    public struct QuadrotorVector4
    {
        public double x;
        public double y;
        public double z;
        public double w;

        public QuadrotorVector4(double initX, double initY, double initZ, double initW)
        {
            x = initX;
            y = initY;
            z = initZ;
            w = initW;
        }

        public static QuadrotorVector4 operator -(QuadrotorVector4 data)
        {
            data.x = -data.x;
            data.y = -data.y;
            data.z = -data.z;
            data.w = -data.w;
            return data;
        }

        public static QuadrotorVector4 operator -(QuadrotorVector4 outVector4, QuadrotorVector4 inVector4)
        {
            outVector4.x = outVector4.x - inVector4.x;
            outVector4.y = outVector4.y - inVector4.y;
            outVector4.z = outVector4.z - inVector4.z;
            outVector4.w = outVector4.w - inVector4.w;
            return outVector4;
        }

        public static QuadrotorVector4 operator +(QuadrotorVector4 outVector4, QuadrotorVector4 inVector4)
        {
            outVector4.x = outVector4.x + inVector4.x;
            outVector4.y = outVector4.y + inVector4.y;
            outVector4.z = outVector4.z + inVector4.z;
            outVector4.w = outVector4.w + inVector4.w;
            return outVector4;
        }

        public static QuadrotorVector4 Dot(QuadrotorVector4 outVector4, QuadrotorVector4 inVector4)
        {
            outVector4.x = outVector4.x * inVector4.x;
            outVector4.y = outVector4.y * inVector4.y;
            outVector4.z = outVector4.z * inVector4.z;
            outVector4.w = outVector4.w * inVector4.w;
            return outVector4;
        }

    }
}
