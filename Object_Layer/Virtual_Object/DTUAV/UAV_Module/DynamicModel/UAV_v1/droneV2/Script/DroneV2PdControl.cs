
namespace DTUAV.UAV_Module.droneV2
{

    [System.Serializable]
    public class DroneV2PdControl 
    {
        public float Pfactor;//积分系数
        public float Dfactor;//微分系数

        public float lastError;//上一次的误差

        public DroneV2PdControl(float pFactor, float dFactor)
        {
            this.Dfactor = dFactor;
            this.Pfactor = pFactor;
        }


        public float UpdatePD(float refValue, float feeBackValue, float timeFrame)
        {
            float presentError = refValue - feeBackValue;
            float deriv = (presentError - lastError) / timeFrame;
            lastError = presentError;
            float finalPID = presentError * Pfactor + deriv * Dfactor;
            //设置PID的精度
            /* if ((finalPID > -0.1) && (finalPID < 0.1))
             {
                 finalPID = 0;
             }*/

            return finalPID;


        }
    }
}