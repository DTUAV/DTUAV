/*
 *
 *  Update Information:
 *                     First: 2021-8-7 In Guangdong University of Technology By Yang Yuanlin
 *
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
