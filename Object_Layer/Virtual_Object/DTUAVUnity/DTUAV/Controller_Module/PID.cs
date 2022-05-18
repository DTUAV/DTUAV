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
namespace DTUAV.Controller
{
    public class PID
    {
        private float _pFactor; //The Param of P
        private float _iFactor; //The Param of I
        private float _dFactor; //The Param of D

        private float _integral; //TheCumulative Amount
        private float _lastError; //The Value of Last Error

        public float GetPFactor()
        {
            return _pFactor;
        }

        public float GetIFactor()
        {
            return _iFactor;
        }

        public float GetDFactor()
        {
            return _dFactor;
        }

        public float GetIntegral()
        {
            return _integral;
        }

        public float GetLastError()
        {
            return _lastError;
        }

        public bool SetPFactor(float pFactor)
        {
            _pFactor = pFactor;
            return true;
        }

        public bool SetIFactor(float iFactor)
        {
            _iFactor = iFactor;
            return true;
        }

        public bool SetDFactor(float dFactor)
        {
            _dFactor = dFactor;
            return true;
        }


        public PID(float pFactor, float iFactor, float dFactor)
        {
            this._pFactor = pFactor;
            this._iFactor = iFactor;
            this._dFactor = dFactor;
        }

        public float UpdatePID(float setPoint, float actual, float timeFrame)
        {

            float presentError = setPoint - actual;
            _integral += presentError * timeFrame;
            float deriv = (presentError - _lastError) / timeFrame;
            _lastError = presentError;
            float finalPID = presentError * _pFactor + _integral * _iFactor + deriv * _dFactor;
            return finalPID;

        }
    }
}

