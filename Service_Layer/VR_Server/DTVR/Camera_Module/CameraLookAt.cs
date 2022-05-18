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
using UnityEngine;

namespace DTUAV.Camera_Module
{
    public class CameraLookAt : MonoBehaviour
    {
        public Transform Target;
        public float DistanceUp = 15f;
        public float DistanceAway = 10f;
        public float Smooth = 2f; 

        public float CamDepthSmooth = 5f;

        void Update()
        {
            
            if ((Input.mouseScrollDelta.y < 0 && Camera.main.fieldOfView >= 3) ||
                Input.mouseScrollDelta.y > 0 && Camera.main.fieldOfView <= 80)
            {
                Camera.main.fieldOfView += Input.mouseScrollDelta.y * CamDepthSmooth * UnityEngine.Time.deltaTime;
            }
        }

        void LateUpdate()
        {
            
            Vector3 disPos = Target.position + Vector3.up * DistanceUp - Target.forward * DistanceAway;
            transform.position = Vector3.Lerp(transform.position, disPos, UnityEngine.Time.deltaTime * Smooth);
            transform.LookAt(Target.position);
        }
    }
}
