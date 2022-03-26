namespace DTUAV.UAV_Module.droneV2
{
    [System.Serializable]
    public class DroneV2PidControl 
    {
        public float pFactor;
        public float iFactor;
        public float dFactor;

        public float integral;
        public float lastError;

        
        public DroneV2PidControl(float pFactor, float iFactor, float dFactor)
        {
            this.pFactor = pFactor;
            this.iFactor = iFactor;
            this.dFactor = dFactor;
        }


       
        public float Update(float setPoint, float actual, float timeFrame)
        {

            float presentError = setPoint - actual;
            integral += presentError * timeFrame;
            float deriv = (presentError - lastError) / timeFrame;
            lastError = presentError;
            float finalPID = presentError * pFactor + integral * iFactor + deriv * dFactor;
            
            if ((finalPID > -0.1) && (finalPID < 0.1))
            {
                finalPID = 0;
            }

            return finalPID;


        }
    }
}