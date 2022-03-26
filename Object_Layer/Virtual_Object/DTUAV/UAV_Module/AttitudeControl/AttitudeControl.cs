﻿/*
 * 2021-8-17 In Guangdong University of Technology By Yang Yuanlin
 */

using System.Collections;
using System.Collections.Generic;
using UnityEngine;

namespace DTUAV.UAV_Module.Quadrotor
{
    public class AttitudeControl : MonoBehaviour
    {
        public Rigidbody UavRib;

        public bool IsStart;
        public float TakeOffHeigh;
        public bool TakeOff;
        public float SimulationTime;
        public float VelocityMove;
        public float RotateSpeed;
        public float ParaAngleToVelocity;
        public Vector3 RefAttitudeRos;
        private Vector3 InitRotationUnity;
        private Vector3 _refVelocityRos;
        private bool TakeOffFinish = false;

        private Coroutine _velocityCot;
        // Start is called before the first frame update
        void Start()
        {
            IsStart = true;
            InitRotationUnity = UavRib.transform.eulerAngles;
            _velocityCot = StartCoroutine(AddVelocity());
        }

        [System.Obsolete]
        private IEnumerator AddVelocity()
        {
            float runTime = 0;
            
            while (IsStart)
            {
                _refVelocityRos.y = ParaAngleToVelocity * RefAttitudeRos.x;
                _refVelocityRos.x = ParaAngleToVelocity * RefAttitudeRos.y;
                float stepMove = VelocityMove * UnityEngine.Time.deltaTime;
                float stepRotate = RotateSpeed * UnityEngine.Time.deltaTime;
                if (runTime >= SimulationTime)
                {
                    if (TakeOff&&UavRib.transform.position.y<2.0f&&!TakeOffFinish)
                    {
                        UavRib.transform.position = Vector3.MoveTowards(UavRib.transform.position,new Vector3(UavRib.transform.position.x, TakeOffHeigh, UavRib.transform.position.z),  stepMove);
                        TakeOffFinish = false;
                    }
                    else if (UavRib.transform.position.y >= 2.0f && !TakeOffFinish)
                    {
                        TakeOffFinish = true;
                    }
                    if (TakeOffFinish)
                    {
                        UavRib.velocity = TF.TF.Local2Global(TF.TF.Ros2Unity(_refVelocityRos), UavRib.rotation.eulerAngles.y * Mathf.Deg2Rad);
                        Quaternion targetRotationUnity = Quaternion.Euler(TF.TF.Ros2Unity(new Vector3(RefAttitudeRos.x ,-RefAttitudeRos.y,RefAttitudeRos.z)) + InitRotationUnity);
                        UavRib.transform.rotation = Quaternion.Slerp(UavRib.transform.rotation, targetRotationUnity, stepRotate);
                    }
                    runTime = 0;
                }
                else
                {
                    runTime += UnityEngine.Time.deltaTime;
                }
                yield return null;
            }

        }
    }
}