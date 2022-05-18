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

using System.Collections.Generic;
using UnityEngine;

namespace DTUAV.Camera_Module
{
    public class CameraChangeLookAt : MonoBehaviour
    {
        public List<Transform> Targets;
        public float DistanceUp = 15f;
        public float DistanceAway = 10f;
        public float Smooth = 2f;

        public float CamDepthSmooth = 5f;
        private Transform _targeTransform;
        private int _targetIDs;
        private int _targetID;
        void Start()
        {
            if (Targets.Count<=0)
            {
                Debug.LogError("CameraChangeLookAt---- No Target");
            }
            else
            {
                _targeTransform = Targets[0];
                _targetID = 1;
                _targetIDs = Targets.Count;
            }
        }
        void Update()
        {
            if ((Input.mouseScrollDelta.y < 0 && Camera.main.fieldOfView >= 3) ||
                Input.mouseScrollDelta.y > 0 && Camera.main.fieldOfView <= 80)
            {
                Camera.main.fieldOfView += Input.mouseScrollDelta.y * CamDepthSmooth * UnityEngine.Time.deltaTime;
            }

                if (Input.GetKeyDown(KeyCode.C))
                {
                    if (_targetID >= _targetIDs)
                    {
                        _targetID = 0;
                    }
                    _targeTransform = Targets[_targetID];
                    _targetID++;
                }

        }

        void LateUpdate()
        {
            Vector3 disPos = _targeTransform.position + Vector3.up * DistanceUp - _targeTransform.forward * DistanceAway;
            transform.position = Vector3.Lerp(transform.position, disPos, UnityEngine.Time.deltaTime * Smooth);
            transform.LookAt(_targeTransform.position);
        }
    }
}