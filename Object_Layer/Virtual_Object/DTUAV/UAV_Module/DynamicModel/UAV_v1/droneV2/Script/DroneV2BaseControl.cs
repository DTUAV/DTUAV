using System.Collections;
using System.Collections.Generic;
using UnityEngine;
namespace DTUAV.UAV_Module.droneV2
{
    public class DroneV2BaseControl : MonoBehaviour
    {
        [Header("Attitude angle limit")]
        public float PitchLimit = 30;
        public float RollLimit = 30;

        [Header("PID Controller")]
        [Header("Throttle PID controller")]
        public DroneV2PidControl PidThrottle;
        [Header("Throttle correction output by controller")]
        public float HeightCorrection;

        [Header("Pitch angle PID controller")]
        public DroneV2PidControl PidPitch;
        [Header("Pitch angle correction output by controller")]
        public float PitchCorrection;

        [Header("Rolling angle PID controller")]
        public DroneV2PidControl PidRoll;
        [Header("Roll angle correction output by controller")]
        public float RollCorrection;

        [Header("Motor")]
        public DroneV2Motor[] Motors;


        [Header("UAV Object")]
        public GameObject uav;

        public Rigidbody uav_rb;

        [Header("Current attitude angle of UAV")]
        public float Pitch;
        public float Roll;
        public float Yaw;
        [Header("UAV current altitude and velocity vector")]
        public float Altitude;
        public float VelocityScalar;
        public Vector3 VelocityVector;

        public DroneV2XYZControl xyzControl;
        public float ref_yaw = 0;
        
        public float PitchCorrectionTo;
        public float RollCorrectionTo;
        public float HeightCorrectionTo;


        float rotateSpeed = 2f;
        Quaternion targetAngels;

        [Header("Cotroller")]
        public DroneV2ControlMode inputControl;



        public void UpdateAngle()
        {
            Pitch = uav.transform.eulerAngles.x;
            Pitch = (Pitch > 180) ? Pitch - 360 : Pitch;

            Roll = uav.transform.eulerAngles.z;
            Roll = (Roll > 180) ? Roll - 360 : Roll;

            Yaw = uav.transform.eulerAngles.y;
            Yaw = (Yaw > 180) ? Yaw - 360 : Yaw;

            Altitude = uav.transform.position.y;
            VelocityVector = uav_rb.velocity;
            VelocityScalar = VelocityVector.magnitude;
        }

        void UpdatePID()
        {
            if (inputControl.ControlModel == false)
            {
                PitchCorrection = PidPitch.Update(inputControl.PitchToUav * PitchLimit, Pitch, UnityEngine.Time.deltaTime);
                RollCorrection = PidRoll.Update(Roll, inputControl.RollToUav * RollLimit, UnityEngine.Time.deltaTime);
                HeightCorrection = PidThrottle.Update(inputControl.ThrottleToUav * inputControl.IncreaseToUav, VelocityVector.y, UnityEngine.Time.deltaTime);

                PitchCorrectionTo = PitchCorrection;
                RollCorrectionTo = RollCorrection;
                HeightCorrectionTo = HeightCorrection;
            }
            else
            {
                PitchCorrectionTo = xyzControl.pitchPID_result;
                RollCorrectionTo = xyzControl.rollPID_result;
                HeightCorrectionTo = xyzControl.yPid_result;
            }



        }
        void ComputeMotors()
        {
            float yaw = 0.0f;
            

            int i = 0;
            foreach (DroneV2Motor motor in Motors)
            {
                motor.UpdateForce();
                yaw += motor.SideForce;
                i++;
                Transform t = motor.motor.GetComponent<Transform>();
                if (inputControl.ControlModel == false)
                {
                    
                    uav_rb.AddForceAtPosition(transform.up * motor.UpForce, t.position, ForceMode.Impulse);
                }
                else
                {
                    
                    uav_rb.AddForceAtPosition(transform.up * motor.UpForce, t.position, ForceMode.Force);
                }

            }
            uav_rb.AddTorque(Vector3.up * yaw, ForceMode.Force);
        }
        void ComputeMotorSpeeds()
        {
            foreach (DroneV2Motor motor in Motors)
            {
                if (Altitude < 0.1)
                    motor.UpdatePropeller(0.0f);
                else
                    motor.UpdatePropeller(5200.0f);
            }
        }


        void FixedUpdate()
        {
            if (!xyzControl.takeoff && xyzControl.lane)
            {

            }
            else
            {
                UpdateAngle();
                UpdatePID();
                ComputeMotors();
            }
        }
    }
}