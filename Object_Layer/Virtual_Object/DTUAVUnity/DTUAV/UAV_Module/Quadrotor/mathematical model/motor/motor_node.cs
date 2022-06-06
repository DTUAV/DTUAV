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
using System.Threading;
using DTUAV.Quadrotor.Propeller;
using UnityEngine;

namespace DTUAV.Quadrotor.Motor
{
    public class motor_node : MonoBehaviour
    {
        [Header("The no load voltage of motor.")]
        public double Um0 = 20;//V
        [Header("The no load current of motor.")]
        public double Im0 = 0.5;//A
        [Header("The resistance of motor")]
        public double Rm = 0.12;
        [Header("The KV value of motor")]
        public double Kv0 = 980;
        [Header("The voltage of motor.")] 
        public double Um;
        [Header("The current of motor.")] 
        public double Im;
        [Header("The output speed of motor.")] 
        public double N;
        [Header("The output torque of motor.")]
        public double Torque;

        [Header("The simulation frequency")]
        public double SimHz = 30;

        private Thread _motorTh;

        private int _sleepTime;

        private bool _isRun;

        private motor _motorNode;
        // Start is called before the first frame update

        public double GetIm(double torque)
        {
            return _motorNode.GetIm(torque);
        }

        public double GetUm(double torque, double n)
        {
            return _motorNode.GetUm(torque, n);
        }
        void Start()
        {
            if (SimHz <= 10e-6)
            {
                Debug.LogError("Motor Node: the SimHz is set error!!!");
            }
            else
            {
                _sleepTime = (int)((1 / SimHz) * 1000);//ms
                _isRun = true;
                _motorNode = new motor(Um0,Im0,Rm,Kv0);
                _motorTh = new Thread(UpdateMotor);
                _motorTh.IsBackground = true;
                _motorTh.Start();
            }
        }
        void UpdateMotor()
        {
            while (_isRun)
            {
                _motorNode.UpdateMotorWithVI(Um, Im);
                N = _motorNode.GetN();
                Torque = _motorNode.GetTorque();
                Thread.Sleep(_sleepTime);
            }
        }

        void OnDestroy()
        {
            _isRun = false;
            if (_motorTh.IsAlive)
            {
                _motorTh.Abort();
            }
        }
    }
}
