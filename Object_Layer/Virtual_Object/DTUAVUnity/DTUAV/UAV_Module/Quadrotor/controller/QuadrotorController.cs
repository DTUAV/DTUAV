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
using System.Collections;
using System.Collections.Generic;
using DTUAV.Quadrotor.QuadrotorMath;
using UnityEngine;

namespace DTUAV.Quadrotor.Controller
{

    public class PController
    {
        private double _kp;
        private double _targetValue;
        private double _output;
        public PController(double kp)
        {
            _kp = kp;
        }

        public double UpdateController(double targetValue, double currentValue)
        {
            _targetValue = targetValue;
            _output = _kp * (targetValue - currentValue);
            return _output;
        }
    }

    public class PDController
    {
        private double _kp;
        private double _kd;
        private double _targetValue;
        private double _output;
        private double _lastError;
        public PDController(double kp, double kd)
        {
            _kp = kp;
            _kd = kd;
            _lastError = 0;
        }

        public double UpdateController(double targetValue, double curValue)
        {
            _targetValue = targetValue;
            double curError = _targetValue - curValue;
            double devError = curError - _lastError;
            _lastError = curError;
            _output = _kp * curError + _kd * devError;
            return _output;
        }
    }

    public class PIDController
    {
        private double _kp;
        private double _ki;
        private double _kd;
        private double _lastError;
        private double _errorSum;
        private double _targetValue;
        private double _output;


        public PIDController(double kp, double ki, double kd)
        {
            _kp = kp;
            _ki = ki;
            _kd = kd;
            _lastError = 0;
            _errorSum = 0;
        }

        public double UpdateController(double targetValue, double curValue)
        {
            _targetValue = targetValue;
            double curError = _targetValue - curValue;
            double devError = curError - _lastError;
            _lastError = curError;
            _errorSum += curError;
            _output = _kp * curError + _ki * _errorSum + _kd * devError;
            return _output;
        }

        public double UpdateController(double curError)
        {
            double devError = curError - _lastError;
            _lastError = curError;
            _errorSum += curError;
            _output = _kp * curError + _ki * _errorSum + _kd * devError;
            return _output;
        }

    }

    public class PositionController
    {
        private PController _xPController;
        private PController _yPController;
        private PController _zPController;

        private PIDController _vxPidController;
        private PIDController _vyPidController;
        private PIDController _vzPidController;

        private PController _rollPController;
        private PController _pitchPController;
        private PController _yawPController;

        private PIDController _rxPidController;
        private PIDController _ryPidController;
        private PIDController _rzPidController;

        private QuadrotorState _state;

        private QuadrotorTargetPosition _targetPosition;

        private double _maxDevVelocity;
        private double _maxAngle;
        private double _maxF;
        private double _maxRotation;
        private double _maxTorque;
        private double _mass;
        public void InitRollController(double kp)
        {
            _rollPController = new PController(kp);
        }

        public void InitRxController(double kp, double ki, double kd)
        {
            _rxPidController = new PIDController(kp,ki,kd);
        }

        public void InitPitchController(double kp)
        {
            _pitchPController = new PController(kp);
        }

        public void InitRyController(double kp, double ki, double kd)
        {
            _ryPidController = new PIDController(kp,ki,kd);
        }

        public void InitYawController(double kp)
        {
            _yawPController = new PController(kp);
        }

        public void InitRzController(double kp, double ki, double kd)
        {
            _rzPidController = new PIDController(kp,ki,kd);
        }

        public void InitXController(double kp)
        {
            _xPController = new PController(kp);
        }

        public void InitVxController(double kp, double ki, double kd)
        {
            _vxPidController = new PIDController(kp,ki,kd);
        }

        public void InitYController(double kp)
        {
            _yPController = new PController(kp);
        }

        public void InitVyController(double kp, double ki, double kd)
        {
            _vyPidController = new PIDController(kp,ki,kd);
        }

        public void InitZController(double kp)
        {
            _zPController = new PController(kp);
        }

        public void InitVzController(double kp, double ki, double kd)
        {
            _vzPidController = new PIDController(kp,ki,kd);
        }

        public PositionController(double maxDevVelocity,double maxAngle,double maxF,double maxRotation,double maxTorque,double mass)
        {
            _state = new QuadrotorState();
            _targetPosition = new QuadrotorTargetPosition();
            _maxDevVelocity = maxDevVelocity;
            _maxAngle = maxAngle;
            _maxF = maxF;
            _maxRotation = maxRotation;
            _maxTorque = maxTorque;
            _mass = mass;
        }

        public double SatGd(double value, double maxValue)
        {
            return (System.Math.Abs(value) < maxValue ? value : (maxValue * value / System.Math.Abs(value)));
        }
        public QuadrotorVector2 SatGd(QuadrotorVector2 value, double maxValue)
        {
            double absValueX = System.Math.Abs(value.x);
            double absValueY = System.Math.Abs(value.y);
            double maxAbsValue = absValueX > absValueY ? absValueX : absValueY;
            if (maxAbsValue > maxValue)
            {
                value.x = (value.x / maxAbsValue) * maxValue;
                value.y = (value.y / maxAbsValue) * maxValue;
            }
            return value;
        }

        
        public QuadrotorInput UpdateController(QuadrotorState curState,QuadrotorTargetPosition targetPosition)
        {
            _targetPosition = targetPosition;
            Debug.Log("curState.PosX: "+curState.PosX+", curState.PosY: "+curState.PosY+", curState.PosZ: "+curState.PosZ);
            Debug.Log("targetPosition.x: " + targetPosition.x + ", targetPosition.y: " + targetPosition.y + ", targetPosition.z: " + targetPosition.z);
            double targetVx = _xPController.UpdateController(_targetPosition.x, curState.PosX);
            double targetVy = _yPController.UpdateController(_targetPosition.y, curState.PosY);
            double targetVz = _zPController.UpdateController(_targetPosition.z, curState.PosZ);

            targetVx = System.Math.Abs(targetVx) > 5 ? 5 * targetVx / System.Math.Abs(targetVx) : targetVx;
            targetVy = System.Math.Abs(targetVy) > 5 ? 5 * targetVy / System.Math.Abs(targetVy) : targetVy;

            Debug.Log("targetVx: "+targetVx+", targetVy: "+targetVy+", targetVz: "+targetVz);


            Debug.Log("curState.VelX: " + curState.VelX + ", curState.VelY: " + curState.VelY + ", curState.VelZ: " + curState.VelZ);
          //  QuadrotorVector2 errorVxy = SatGd(new QuadrotorVector2(targetVx-curState.VelX, targetVy-curState.VelY), _maxDevVelocity);
            //Debug.Log("errorVxy.x: " + errorVxy.x + ", errorVxy.y: " + errorVxy.y);
            double errorVz = SatGd(targetVz-curState.VelZ, _maxDevVelocity);
            Debug.Log("errorVz: " + errorVz);
            double f = SatGd(_mass * (9.8 + _vzPidController.UpdateController(errorVz)),_maxF);
            Debug.Log("f: " + f);
            f = -f;
            f = f < 0 ? 0 : f;
            Debug.Log("End f: " + f);
            // double targetAngleX = _vxPidController.UpdateController(errorVxy.x);
            double targetAngleX = _vxPidController.UpdateController(targetVx,curState.VelX);
            Debug.Log("targetAngleX: " + targetAngleX);

            //double targetAngleY = _vyPidController.UpdateController(errorVxy.y);
            double targetAngleY = _vxPidController.UpdateController(targetVy, curState.VelY);
            Debug.Log("targetAngleY: " + targetAngleY);

            double targetRoll = -System.Math.Sin(curState.Yaw) * targetAngleX +
                                System.Math.Cos(curState.Yaw) * targetAngleY;
            double targetPitch = -System.Math.Cos(curState.Yaw) * targetAngleX -
                                 System.Math.Sin(curState.Yaw) * targetAngleY;
            Debug.Log("targetRoll: " + targetRoll);
            Debug.Log("targetPitch: " + targetPitch);
            //QuadrotorVector2 LimitRollPitch = SatGd(new QuadrotorVector2(targetRoll, targetPitch), _maxAngle);

            //Debug.Log("LimitRoll: " + LimitRollPitch.x);
            //Debug.Log("LimitPitch: " + LimitRollPitch.y);
            targetRoll = SatGd(targetRoll, _maxAngle);
            targetPitch = SatGd(targetPitch, _maxAngle);
            Debug.Log("targetRoll: " + targetRoll);
            Debug.Log("targetPitch: " + targetPitch);

            // double targetRx = _rollPController.UpdateController(LimitRollPitch.x, curState.Roll);
            // double targetRy = _pitchPController.UpdateController(LimitRollPitch.y, curState.Pitch);
             double targetRx = _rollPController.UpdateController(targetRoll, curState.Roll);
             double targetRy = _pitchPController.UpdateController(targetPitch, curState.Pitch);
            double targetRz = _yawPController.UpdateController(_targetPosition.yaw, curState.Yaw);

            Debug.Log("targetRx: " + targetRx);
            Debug.Log("targetRy: " + targetRy);
            Debug.Log("targetRz: " + targetRz);

            targetRx = SatGd(targetRx, _maxRotation);
            targetRy = SatGd(targetRy, _maxRotation);
            targetRz = SatGd(targetRz, _maxRotation);

            Debug.Log("EndTargetRx: " + targetRx);
            Debug.Log("EndTargetRy: " + targetRy);
            Debug.Log("EmdTargetRz: " + targetRz);

            double tx = SatGd(_rxPidController.UpdateController(targetRx, curState.OmegaX), _maxTorque);
            double ty = SatGd(_rxPidController.UpdateController(targetRy, curState.OmegaY), _maxTorque);
            double tz = SatGd(_rxPidController.UpdateController(targetRz, curState.OmegaZ), _maxTorque);

            Debug.Log("tx: " + tx);
            Debug.Log("ty: " + ty);
            Debug.Log("tz: " + tz);

            QuadrotorInput ret = new QuadrotorInput();
            ret.F = f;
            ret.Tx = tx;
            ret.Ty = ty;
            ret.Tz = tz;
            return ret;
        }

    }
}