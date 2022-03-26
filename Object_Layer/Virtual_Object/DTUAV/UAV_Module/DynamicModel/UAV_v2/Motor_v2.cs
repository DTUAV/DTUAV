using System.Collections;
using System.Collections.Generic;
using UnityEngine;

namespace DTUAV.UAV_Module.Quadrotor
{
    public class Motor_v2 : MonoBehaviour
    {
        public float UpForce = 0.0f;
        public float SideForce = 0.0f;

        public float Power_Auto = 5f;
        public float Power_Man = 0.5f;

        public bool InvertDirection;

        public float YawFactor_Auto = 0.0f;
        public float PitchFactor_Auto = 0.0f;
        public float RollFactor_Auto = 0.0f;

        public float YawFactor_Man = 0.0f;
        public float PitchFactor_Man = 0.0f;
        public float RollFactor_Man = 0.0f;

        public float SpeedPropeller = 0;

        public GameObject Propeller;

        public GameObject MotorObject;

        public ControlWay_v2 ControlWayInstace;

        public float Auto_ThrottleValue;
        public float Auto_PitchValue;
        public float Auto_RollValue;
        public float Auto_YawValue;

        public float Man_ThrottleValue;
        public float Man_PitchValue;
        public float Man_RollValue;
        public float Man_YawValue;


        public void UpdateForce()
        {
            float UpForceTotal;
            if (ControlWayInstace == ControlWay_v2.AutomaticFlight)
            {
                UpForceTotal = Mathf.Clamp(Auto_ThrottleValue, 0, 1) * Power_Auto;
                UpForceTotal -= Auto_PitchValue * PitchFactor_Auto;
                UpForceTotal -= Auto_RollValue * RollFactor_Auto;
                SideForce = PreNormalize(Auto_YawValue, YawFactor_Auto);
               // UpForceTotal += SideForce;
                
            }
            else
            {
                UpForceTotal = Mathf.Clamp(Man_ThrottleValue, 0, 1) * Power_Man;
                UpForceTotal -= Man_PitchValue * PitchFactor_Man;
                UpForceTotal -= Man_RollValue * RollFactor_Man;
                SideForce = PreNormalize(Man_YawValue, YawFactor_Man);


            }

            UpForce = UpForceTotal;

            SpeedPropeller = Mathf.Lerp(SpeedPropeller, UpForce * 1550000.0f, UnityEngine.Time.deltaTime);
            UpdatePropeller(SpeedPropeller);
        }

        public void UpdatePropeller(float speed)
        {
            Propeller.transform.Rotate(0.0f, SpeedPropeller * 2 * UnityEngine.Time.deltaTime, 0.0f);
        }


        float PreNormalize(float input, float factor)
        {
            float finalValue = input;

            if (InvertDirection)
                finalValue = Mathf.Clamp(finalValue, -1, 0);
            else
                finalValue = Mathf.Clamp(finalValue, 0, 1);

            if (ControlWayInstace == ControlWay_v2.AutomaticFlight)
            {
                return finalValue * (YawFactor_Auto);
            }
            else
            {
                return finalValue * (YawFactor_Man);
            }

        }
    }
}
