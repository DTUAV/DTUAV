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
using Unity.Collections.LowLevel.Unsafe;

namespace DTUAV.Quadrotor.Propeller
{
    public class propeller
    {
        private double _ct;//the drag coefficient of propeller.
        private double _cm;//the torque coefficient of propeller.
        private double _rho;//the air density (kg/m^3).
        private double _n;//the rotation speed of propeller (RPM).
        private double _dp;//the diameter of propeller (m).
        private double _tt;//the temperature of environment (dotC).
        private double _h;//the altitude of Quadrotor.
        private double _pa;//the pressure of environment.
        private double _pull;//the pulling force of propeller (N).
        private double _torque;//the torque of propeller (N.m).

        public bool SetCm(double cm)
        {
            _cm = cm;
            return true;
        }
        public double GetCm()
        {
            return _cm;
        }
        public bool SetN(double n)
        {
            _n = n;
            return true;
        }
        public bool SetDp(double dp)
        {
            _dp = dp;
            return true;
        }

        public double GetDp()
        {
            return _dp;
        }
        public double GetPa()
        {
            return _pa;
        }

        public double GetRho()
        {
            return _rho;
        }

        public double GetN()
        {
            return _n;
        }

        public bool SetH(double h)
        {
            _h = h;
            _pa = 101325 * System.Math.Pow((1 - 0.0065 * (_h / (273 + _tt))), 5.2561);
            _rho = 273 * _pa * common.rho_0 / (101325 * (273 + _tt));
            return true;
        }

        public double GetH()
        {
            return _h;
        }

        public bool SetTt(double tt)
        {
            _tt = tt;
            _pa = 101325 * System.Math.Pow((1 - 0.0065 * (_h / (273 + _tt))), 5.2561);
            _rho = 273 * _pa * common.rho_0 / (101325 * (273 + _tt));
            return true;
        }

        public double GetTt()
        {
            return _tt;
        }

        public bool SetCt(double ct)
        {
            _ct = ct;
            return true;
        }

        public double GetCt()
        {
            return _ct;
        }

        public double GetPull(double n)
        {
            _n = n;
            return UpdatePull(_n);
        }

        public double GetPull()
        {
            return _pull;
        }

        public double GetTorque(double n)
        {
            _n = n;
            return UpdateTorque(_n);
        }
        public double GetTorque()
        {
            return _torque;
        }

        public propeller(double ct, double cm)
        {
            _ct = ct;
            _cm = cm;
            _rho = 1;
            _dp = 1;
        }
        public propeller(double ct, double cm,double tt,double h, double n,double dp)
        {
            _ct = ct;
            _cm = cm;
            _tt = tt;
            _h = h;
            _n = n;
            _dp = dp;
            _pa = 101325 * System.Math.Pow((1 - 0.0065 * (_h / (273 + _tt))),5.2561);
            _rho = 273 * _pa * common.rho_0 / (101325 * (273 + _tt));
            _pull = 0;
        }

        public double UpdatePull(double n)
        {
            _n = n;
            _pull = _ct * _rho * System.Math.Pow(_n / 60, 2) * System.Math.Pow(_dp, 4);
            return _pull;
        }

        public bool Update(double n)
        {
            _n = n;
            _pull = _ct * _rho * System.Math.Pow(_n / 60, 2) * System.Math.Pow(_dp, 4);
            _torque = _cm * _rho * System.Math.Pow(_n / 60, 2) * System.Math.Pow(_dp, 5);
            return true;
        }
        public double UpdateTorque(double n)
        {
            _n = n;
            _torque = _cm * _rho * System.Math.Pow(_n / 60, 2) * System.Math.Pow(_dp, 5);
            return _torque;
        }
        public double GetSpeedByPull(double pull)
        {
            return 60 * System.Math.Pow(pull / System.Math.Pow(_dp, 4) * _ct * _rho, 0.5);
        }

        public double GetSpeedByTorque(double Torque)
        {
            return 60 * System.Math.Pow(Torque / System.Math.Pow(_dp, 5) * _cm * _rho, 0.5);
        }

    }
}
