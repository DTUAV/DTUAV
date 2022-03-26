using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using DTUAV.Math.DataStructure;
namespace DTUAV.UAV_Module.Quadrotor
{
    public class DOF6 : MonoBehaviour
    {
        public DT_Vector3 GlobalInitPosition = new DT_Vector3();
        public DT_Vector3 GlobalPosition = new DT_Vector3();
        public DT_Vector3 LocalPosition = new DT_Vector3();
        public DT_Vector3 AttitudeAngle = new DT_Vector3();
        public DT_Vector4 Rotation = new DT_Vector4();

        public DT_Vector3 GlobalPositionRos = new DT_Vector3();
        public DT_Vector3 LocalPositionRos = new DT_Vector3();
        public DT_Vector4 RotationRos = new DT_Vector4();


        public DT_Vector3 LineVelocity = new DT_Vector3();
        public DT_Vector3 AngleVelocity = new DT_Vector3();

        public DT_Vector3 LineAAcceleration = new DT_Vector3();
        public DT_Vector3 AngleAAcceleration = new DT_Vector3();

        public DT_Vector3 LineAcceleration = new DT_Vector3();
        public DT_Vector3 AngleAcceleration = new DT_Vector3();

        public float Weight;
        public float CurrentPitch;
        public float CurrentRoll;
        public float CurrentYaw;
        public DT_Vector3 Size = new DT_Vector3();


    }
}
