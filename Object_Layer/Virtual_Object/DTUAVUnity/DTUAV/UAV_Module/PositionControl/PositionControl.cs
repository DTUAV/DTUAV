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

using DTUAV.Math.DataNoise;
using System.Collections;
using System.Collections.Generic;
using DTUAV.TF;
using UnityEngine;

namespace DTUAV.UAV_Module.Quadrotor
{
    public class PositionControl : MonoBehaviour
    {
        public GameObject UavObj;
        public bool IsStart;
        public float SimulationTime;
        public bool IsAddNoise = false;
        public Vector3 RefLocalPoseRos;
        public Vector3 RefRotationRos;
        public float VelocityMove;
        public float RotateSpeed;
        private Vector3 InitPoseUnity;
        private Vector3 InitRotationUnity;
        private Vector3 lastPosition;
        private Coroutine _velocityCot;
        // Start is called before the first frame update
        void Start()
        {
            InitPoseUnity = new Vector3();
            InitPoseUnity = UavObj.transform.position;
            InitRotationUnity =UavObj.transform.eulerAngles;
            lastPosition = TF.TF.Unity2Ros(UavObj.transform.position);
            IsStart = true;
            _velocityCot = StartCoroutine(AddPosition());
            
        }

        [System.Obsolete]
        private IEnumerator AddPosition()
        {
            float runTime = 0;
            while (IsStart)
            {
                if (runTime >= SimulationTime)
                {
                    float stepMove = VelocityMove * UnityEngine.Time.deltaTime;
                    float stepRotate = RotateSpeed * UnityEngine.Time.deltaTime;
                    if (IsAddNoise)
                    {
                        UavObj.transform.position = Vector3.MoveTowards(gameObject.transform.position, TF.TF.Ros2Unity(RefLocalPoseRos) + InitPoseUnity, stepMove) + new Vector3((float)DataNoise.GaussNiose1() / 1000.0f, (float)DataNoise.GaussNiose1() / 1000.0f, (float)DataNoise.GaussNiose1() / 1000.0f);
                    }
                    else
                    {
                        UavObj.transform.position = Vector3.MoveTowards(gameObject.transform.position, TF.TF.Ros2Unity(RefLocalPoseRos) + InitPoseUnity, stepMove);
                    }
                    
                    RefRotationRos.y = -(RefLocalPoseRos.x - TF.TF.Unity2Ros(UavObj.transform.position - InitPoseUnity).x)*8;
                    RefRotationRos.x = (RefLocalPoseRos.y - TF.TF.Unity2Ros(UavObj.transform.position - InitPoseUnity).y)*8;
                    RefRotationRos.x = Mathf.Clamp(RefRotationRos.x, -15, 15);
                    RefRotationRos.y = Mathf.Clamp(RefRotationRos.y, -15, 15);

                    if (IsAddNoise)
                    {
                        Quaternion targetRotationUnity = Quaternion.Euler(TF.TF.Ros2Unity(RefRotationRos) + InitRotationUnity + new Vector3((float)DataNoise.GaussNiose1() / 1000.0f, (float)DataNoise.GaussNiose1() / 1000.0f, (float)DataNoise.GaussNiose1() / 1000.0f));
                        UavObj.transform.rotation = Quaternion.Slerp(UavObj.transform.rotation, targetRotationUnity, stepRotate);
                    }
                    else
                    {
                        Quaternion targetRotationUnity = Quaternion.Euler(TF.TF.Ros2Unity(RefRotationRos) + InitRotationUnity);
                        UavObj.transform.rotation = Quaternion.Slerp(UavObj.transform.rotation, targetRotationUnity, stepRotate);
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