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
using DTUAV.Quadrotor.QuadrotorMath;
using System;
using System.Diagnostics;
using UnityEngine;
using Debug = UnityEngine.Debug;

namespace DTUAV.Quadrotor.Motion
{
    //  UAV Model
    /*
     *      / \
     *       | x  
     *  2         1  )
     *    -     -   \/ 
     *       -
     *   -      -   
     *  3         4 /\
     *               )
     */

    public class Motion
    {
        private float _mass;//The mass of Quadrotor
        private QuadrotorState _state;//The current state of Quadrotor: Acceleration\Linear Velocity\Position\Angular Acceleration\Angular Velocity\Angular
        private QuadrotorInput _input;//The target input of Quadrotor: Force and Torque
        private QuadrotorMatrix33 _j;//The Moment of Inertia for Quadrotor
        private double _jm;//The Moment of Inertia for Motor and Propeller
        private double _ct;//The Drag Coefficient of Propeller
        private double _cm;//The Torque Coefficient of Propeller
        private double _d;//The Length of Arm
        private double _currentTime;
        private bool _isLinearModel = true;
        public double GetCurrentTime()
        {
            return _currentTime;
        }
        public QuadrotorMatrix33 GetJ()
        {
            return _j;
        }

        public bool SetJ(QuadrotorMatrix33 j)
        {
            _j = j;
            return true;
        }

        public double GetJm()
        {
            return _jm;
        }

        public bool SetJm(double jm)
        {
            _jm = jm;
            return true;
        }

        public double GetCt()
        {
            return _ct;
        }

        public bool SetCt(double ct)
        {
            _ct = ct;
            return true;
        }

        public double GetCm()
        {
            return _cm;
        }

        public bool SetCm(double cm)
        {
            _cm = cm;
            return true;
        }

        public double GetD()
        {
            return _d;
        }

        public bool SetD(double d)
        {
            _d = d;
            return true;
        }
        public float GetMass()
        {
            return _mass;

        }

        public bool SetMass(float mass)
        {
            _mass = mass;
            return true;
        }


        public Motion(float mass,QuadrotorState initState,QuadrotorMatrix33 j,double jm,double ct,double cm,double d)
        {
            _mass = mass;
            _state = initState;
            _j = j;
            _jm = jm;
            _ct = ct;
            _cm = cm;
            _d = d;
            _input = new QuadrotorInput();
            _currentTime = 0;
            _isLinearModel = true;
        }

        public Motion(float mass, QuadrotorState initState, QuadrotorMatrix33 j, double jm, double ct, double cm, double d,bool isLinearModel)
        {
            _mass = mass;
            _state = initState;
            _j = j;
            _jm = jm;
            _ct = ct;
            _cm = cm;
            _d = d;
            _input = new QuadrotorInput();
            _currentTime = 0;
            _isLinearModel = isLinearModel;
        }


        public QuadrotorState UpdateModel(QuadrotorVector4 rate,double timeInterval)
        {
           return(RungeKutta4(_state, CalculateQuadrotorInput(rate), CountGroMoment(rate, _state), timeInterval));
        }

        private QuadrotorInput CalculateQuadrotorInput(QuadrotorVector4 rate)
        {
            //The x type of Quadrotor 
           // Debug.Log("rate.x: " + rate.x + ",rate.y: " + rate.y + ",rate.z: " + rate.z + ",rate.w " + rate.w);
            QuadrotorInput ret = new QuadrotorInput();
            ret.F = _ct * (rate.x * rate.x + rate.y * rate.y + rate.z * rate.z + rate.w * rate.w);
            ret.Tx = _d * _ct * 0.707107 * (rate.x * rate.x - rate.y * rate.y - rate.z * rate.z + rate.w * rate.w);
            ret.Ty = _d * _ct * 0.707107 * (rate.x * rate.x + rate.y * rate.y - rate.z * rate.z - rate.w * rate.w);
            ret.Tz = _cm * (rate.x * rate.x - rate.y * rate.y + rate.z * rate.z - rate.w * rate.w);
           // Debug.Log("F: "+ret.F+",Tx: "+ret.Tx+",Ty: "+ret.Ty+",Tz: "+ret.Tz);

            return ret;
        }
        private QuadrotorState RungeKutta4(QuadrotorState inputState, QuadrotorInput inputControl, QuadrotorVector3 gyroMoment,double step)
        {
            QuadrotorState k1 = MotionFun(inputState, inputControl, gyroMoment);
            QuadrotorState k2 = MotionFun(inputState + k1 * step / 2, inputControl, gyroMoment);
            QuadrotorState k3 = MotionFun(inputState + k2 * step / 2, inputControl, gyroMoment);
            QuadrotorState k4 = MotionFun(inputState + k3 * step, inputControl, gyroMoment);
            _state = inputState + (k1 + 2 * k2 + 2 * k3 + k4) * step / 6;
            _state.AccX = k1.AccX;
            _state.AccY = k1.AccY;
            _state.AccZ = k1.AccZ;
            _state.OmegaAccX = k1.OmegaAccX;
            _state.OmegaAccY = k1.OmegaAccY;
            _state.OmegaAccZ = k1.OmegaAccZ;
            _state.AccPitch = (_state.VelPitch - inputState.VelPitch) / step;
            _state.AccRoll = (_state.VelRoll - inputState.VelRoll) / step;
            _state.AccYaw = (_state.VelYaw - inputState.VelYaw) / step;
            CheckValue();
            _currentTime += step;
            return _state;
        }

        private void CheckValue()
        {
            _state.Roll = _state.Roll >= 6.28 ? 6.28 : _state.Roll <= -6.28 ? -6.28 : _state.Roll;
            _state.Pitch = _state.Pitch >= 6.28 ? 6.28 : _state.Pitch <= -6.28 ? -6.28 : _state.Pitch;
            _state.Yaw = _state.Yaw >= 6.28 ? _state.Yaw - 6.28 : _state.Yaw <= -6.28 ? -6.28 - _state.Yaw : _state.Yaw;
        }

        private QuadrotorVector3 CountGroMoment(QuadrotorVector4 rate, QuadrotorState inputState)
        {
            /*
             * rate.x = w1
             * rate.y = w2
             * rate.z = w3
             * rate.w = w4
             */

            QuadrotorVector3 ret = new QuadrotorVector3();
            ret.x = _jm * inputState.OmegaY * (rate.x - rate.y + rate.z - rate.w);
            ret.y = _jm * inputState.OmegaX * (-rate.x + rate.y - rate.z + rate.w);
            ret.z = 0;
            //Debug.Log("GroMoment.x: " + ret.x + ",GroMoment.y: " + ret.y + ",GroMoment.z: " + ret.z);
            return ret;
        }

        private QuadrotorState MotionFun(QuadrotorState inputState, QuadrotorInput inputControl,QuadrotorVector3 gyroMoment)
        {
            if (_isLinearModel)
            {
                //=======================>Linear Model<===================
                //update position
                inputState.PosX = inputState.VelX;
                inputState.PosY = inputState.VelY;
                inputState.PosZ = inputState.VelZ;
                //update linear velocity
                inputState.VelX = inputState.AccX;
                inputState.VelY = inputState.AccY;
                inputState.VelZ = inputState.AccZ;

                //update linear acceleration
                inputState.AccX = -(inputControl.F / _mass) * (System.Math.Cos(inputState.Yaw) * inputState.Pitch
                                                               + System.Math.Sin(inputState.Yaw) * inputState.Roll);
                inputState.AccY = -(inputControl.F / _mass) * (System.Math.Sin(inputState.Yaw) * inputState.Pitch
                                                               - System.Math.Cos(inputState.Yaw) * inputState.Roll);
                inputState.AccZ = -(inputControl.F / _mass) + 9.8;

                //update roll, pitch and yaw 
                inputState.Roll = inputState.VelRoll;
                inputState.Pitch = inputState.VelPitch;
                inputState.Yaw = inputState.VelYaw;


                //update the rotation of uav body
                inputState.OmegaX = inputState.OmegaAccX;
                inputState.OmegaY = inputState.OmegaAccY;
                inputState.OmegaZ = inputState.OmegaAccZ;

                //update the rate of roll, pitch and yaw 
                inputState.VelRoll = inputState.OmegaX;
                inputState.VelPitch = inputState.OmegaY;
                inputState.VelYaw = inputState.OmegaZ;

                QuadrotorVector3 torque = new QuadrotorVector3(inputControl.Tx, inputControl.Ty, inputControl.Tz);
                QuadrotorVector3 tem = QuadrotorMatrix33.Inv(_j) * torque;

                //update the rotation acceleration.
                inputState.OmegaAccX = tem.x;
                inputState.OmegaAccY = tem.y;
                inputState.OmegaAccZ = tem.z;

                return inputState;
            }
            else
            {
                //non-linear model
                // /*
                //update position
                inputState.PosX = inputState.VelX;
                inputState.PosY = inputState.VelY;
                inputState.PosZ = inputState.VelZ;
                //update linear velocity
                inputState.VelX = inputState.AccX;
                inputState.VelY = inputState.AccY;
                inputState.VelZ = inputState.AccZ;
                //update linear acceleration  
                inputState.AccX = -(inputControl.F / _mass) *
                                  (System.Math.Cos(inputState.Yaw) * System.Math.Sin(inputState.Pitch) *
                                   System.Math.Cos(inputState.Roll)
                                   + System.Math.Sin(inputState.Yaw) * System.Math.Sin(inputState.Roll));
                inputState.AccY = -(inputControl.F / _mass) *
                                  (System.Math.Sin(inputState.Yaw) * System.Math.Sin(inputState.Pitch) *
                                   System.Math.Cos(inputState.Roll)
                                   - System.Math.Cos(inputState.Yaw) * System.Math.Sin(inputState.Roll));
                inputState.AccZ = -(inputControl.F / _mass) * System.Math.Cos(inputState.Roll) *
                                  System.Math.Cos(inputState.Pitch) + 9.8;
                Debug.Log("inputState.AccZ" + inputState.AccZ);
                Debug.Log("inputControl.F / _mass" + inputControl.F);
                //update roll, pitch and yaw 
                inputState.Roll = inputState.VelRoll;
                inputState.Pitch = inputState.VelPitch;
                inputState.Yaw = inputState.VelYaw;
                
                //update the rotation of uav body
                inputState.OmegaX = inputState.OmegaAccX;
                inputState.OmegaY = inputState.OmegaAccY;
                inputState.OmegaZ = inputState.OmegaAccZ;

                //update the rate of roll, pitch and yaw 
                inputState.VelRoll =
                    inputState.OmegaX + inputState.OmegaY * System.Math.Tan(inputState.Pitch) *
                                      System.Math.Sin(inputState.Roll)
                                      + inputState.OmegaZ * System.Math.Tan(inputState.Pitch) *
                                      System.Math.Cos(inputState.Roll);
                inputState.VelPitch = System.Math.Cos(inputState.Roll) * inputState.OmegaY -
                                      System.Math.Sin(inputState.Roll) * inputState.OmegaZ;
                inputState.VelYaw = (System.Math.Sin(inputState.Roll) / System.Math.Cos(inputState.Pitch)) *
                                    inputState.OmegaY +
                                    (System.Math.Cos(inputState.Roll) / System.Math.Cos(inputState.Pitch)) *
                                    inputState.OmegaZ;

                QuadrotorMatrix33 crossRotation = new QuadrotorMatrix33();
                crossRotation.Set(0, 0, 0);
                crossRotation.Set(0, 1, -inputState.OmegaZ);
                crossRotation.Set(0, 2, inputState.OmegaY);
                crossRotation.Set(1, 0, inputState.OmegaZ);
                crossRotation.Set(1, 1, 0);
                crossRotation.Set(1, 2, -inputState.OmegaX);
                crossRotation.Set(2, 0, -inputState.OmegaY);
                crossRotation.Set(2, 1, -inputState.OmegaX);
                crossRotation.Set(2, 2, 0);

                QuadrotorVector3 rotationBody =
                    new QuadrotorVector3(inputState.OmegaX, inputState.OmegaY, inputState.OmegaZ);
                QuadrotorVector3 torque = new QuadrotorVector3(inputControl.Tx, inputControl.Ty, inputControl.Tz);
                QuadrotorVector3 tem = -(QuadrotorMatrix33.Inv(_j) * crossRotation * _j * rotationBody) + torque +
                                       gyroMoment;

                //update the rotation acceleration.
                inputState.OmegaAccX = tem.x;
                inputState.OmegaAccY = tem.y;
                inputState.OmegaAccZ = tem.z;

                return inputState;
            }
            //inputState.AccX = 

           // */
        }

    }
}
