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
using UnityEngine;
using System.Threading;

namespace DTUAV.Quadrotor.Propeller
{
    public class propeller_node : MonoBehaviour
    {
        [Header("The drag coefficient of propeller")]
        public double Ct;//the drag coefficient of propeller.
        [Header("The torque coefficient of propeller")]
        public double Cm;
        [Header("The diameter of propeller")]
        public double Dp;//the diameter of propeller (m).
        [Header("The temperature of environment")]
        public double Tt;//the temperature of environment (dotC).
        [Header("The altitude of Quadrotor")]
        public double H;//the altitude of Quadrotor.
        [Header("The rotation speed of propeller")]
        public double N;//the rotation speed of propeller (RPM).
        [Header("The pulling force of propeller")]
        public double Pull;//the pulling force of propeller (N).
        [Header("The torque of propeller")]
        public double Torque;//the torque of propeller (N.m).
        [Header("The simulation frequency")] 
        public double SimHz;

        private Thread _propellerTh;

        private int _sleepTime;

        private bool _isRun;

        private propeller _propellerNode;
        // Start is called before the first frame update

        public double GetPullByN(double n)
        {
            N = n;
            return _propellerNode.UpdatePull(n);
        }

        public double GetTorqueByN(double n)
        {
            N = n;
            return _propellerNode.UpdateTorque(N);
        }

        public double GetNByTorque(double torque)
        {
            return _propellerNode.GetSpeedByTorque(torque);
        }

        public double GetNByPull(double pull)
        {
            return _propellerNode.GetSpeedByPull(pull);
        }
        public bool SetN(double n)
        {
            N = n;
            return _propellerNode.SetN(n);
        }
        public bool SetCt(double ct)
        {
            Ct = ct;
            return _propellerNode.SetCt(Ct);
        }

        public bool SetCm(double cm)
        {
            Cm = cm;
            return _propellerNode.SetCm(Cm);
        }
        public bool SetTt(double tt)
        {
            Tt = tt;
            return _propellerNode.SetTt(Tt);
        }

        public bool SetH(double h)
        {
            H = h;
            return _propellerNode.SetH(H);
        }
        void Start()
        {
            if (SimHz<=10e-6)
            {
                Debug.LogError("Propeller Node: the SimHz is set error!!!");
            }
            else
            {
                _sleepTime = (int)((1 / SimHz) * 1000);//ms
                _isRun = true;
                _propellerNode = new propeller(Ct, Cm, Tt, H, N, Dp);
                _propellerTh = new Thread(UpdatePropeller);
                _propellerTh.IsBackground = true;
                _propellerTh.Start();
            }
           
        }

        void UpdatePropeller()
        {
            while (_isRun)
            {
                _propellerNode.Update(N);
                Pull = _propellerNode.GetPull();
                Torque = _propellerNode.GetTorque();
                Thread.Sleep(_sleepTime);
            }
        }

        void OnDestroy()
        {
            _isRun = false;
            if (_propellerTh.IsAlive)
            {
                _propellerTh.Abort();
            }
        }
    }
}
