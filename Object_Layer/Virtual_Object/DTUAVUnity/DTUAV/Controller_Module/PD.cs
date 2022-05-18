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
    public class PD
    {
        private float _pFactor; //The Param of P
        private float _dFactor; //The Param of D

        private float _lastError; //The Value of Last Error

        public float GetPFactor()
        {
            return _dFactor;
        }

        public float GetDFactor()
        {
            return _dFactor;
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

        public bool SetDFactor(float dFactor)
        {
            _dFactor = dFactor;
            return true;
        }

        public PD(float pFactor, float dFactor)
        {
            this._dFactor = dFactor;
            this._pFactor = pFactor;
        }


        public float UpdatePD(float refValue, float feeBackValue, float timeFrame)
        {
            float presentError = refValue - feeBackValue;
            float deriv = (presentError - _lastError) / timeFrame;
            _lastError = presentError;
            float finalPID = presentError * _pFactor + deriv * _dFactor;
            
            return finalPID;
        }
    }
}
