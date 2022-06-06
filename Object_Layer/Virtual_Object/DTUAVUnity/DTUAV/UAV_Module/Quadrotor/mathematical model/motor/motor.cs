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
using System.Runtime.InteropServices.WindowsRuntime;

namespace DTUAV.Quadrotor.Motor
{
    public class motor
    {
        private double _te;//the electromagnetic torque of motor.
        private double _kt;//the torque constant of motor.
        private double _im;//the armature current of motor.(A)
        private double _um;//the voltage of motor (V) 
        private double _ke;
        private double _um0;
        private double _im0;
        private double _rm;
        private double _kv0;
        private double _torque;//the output torque of motor == propeller
        private double _n;//the output speed of motor == propeller

        public double GetTe()
        {
            return _te;
        }

        public bool SetTe(double te)
        {
            _te = te;
            return true;
        }

        public bool SetTorque(double torque)
        {
            _torque = torque;
            return true;
        }
        public double GetTorque()
        {
            return _torque;
        }

        public bool SetN(double n)
        {
            _n = n;
            return true;
        }

        public double GetN()
        {
            return _n;
        }

        public bool SetKv0(double kv0)
        {
            _kv0 = kv0;
            _ke = (_um0 - _im0 * _rm) / _kv0 * _um0;
            _kt = 9.55 * _ke;
            return true;
        }

        public double GetKv0()
        {
            return _kv0;
        }
        public bool SetRm(double rm)
        {
            _rm = rm;
            _ke = (_um0 - _im0 * _rm) / _kv0 * _um0;
            _kt = 9.55 * _ke;
            return true;
        }

        public double GetRm()
        {
            return _rm;
        }

        public bool SetIm0(double im0)
        {
            _im0 = im0;
            _ke = (_um0 - _im0 * _rm) / _kv0 * _um0;
            _kt = 9.55 * _ke;
            return true;
        }

        public double GetIm0()
        {
            return _im0;
        }

        public bool SetUm0(double um0)
        {
            _um0 = um0;
            _ke = (_um0 - _im0 * _rm) / _kv0 * _um0;
            _kt = 9.55 * _ke;
            return true;
        }

        public double GetUm0()
        {
            return _um0;
        }

        public bool SetKe(double ke)
        {
            _ke = ke;
            _kt = _ke * 9.55;
            return true;
        }

        public double GetKe()
        {
            return _ke;
        }

        public bool SetKt(double kt)
        {
            _kt = kt;
            _ke = _kt / 9.55;
            return true;
        }

        public double GetKt()
        {
            return _kt;

        }

        public double GetIm(double torque)
        {
            return  (torque / _kt) + _im0;
        }

        public double GetUm(double torque, double n)
        {
            double im = (torque / _kt) + _im0;
            return _ke * n + _rm * im;
        }
        public bool UpdateMotorWithTN(double torque,double n)
        {
            _torque = torque;
            _n = n;
            _im = _torque / _kt + _im0;
            _um = _ke * _n + _rm * _im;
            _te = _kt * _im;
            return true;
        }

        public bool UpdateMotorWithVI(double um, double im)
        {
            _um = um;
            _im = im;
            _n = (_um - _rm * _im) / _ke;
            _torque = _kt * (_im - _im0);
            _te = _kt * _im;
            return true;
        }

        public motor(double kt, double um0, double im0, double rm, double kv0)
        {
            _kt = kt;
            _um0 = um0;
            _im0 = im0;
            _rm = rm;
            _kv0 = kv0;
            _ke = (_um0 - _im0 * _rm) / (_kv0 * _um0);
        }

        public motor(double um0,double im0,double rm,double kv0)
        {
            _um0 = um0;
            _im0 = im0;
            _rm = rm;
            _kv0 = kv0;
            _ke = (_um0 - _im0 * _rm) / (_kv0 * _um0);
            _kt = 9.55 * _ke;
        }

    }
}
