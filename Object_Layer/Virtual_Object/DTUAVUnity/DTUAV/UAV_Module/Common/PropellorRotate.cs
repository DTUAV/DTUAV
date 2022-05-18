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

using System.Collections;
using System.Collections.Generic;
using UnityEngine;

namespace DTUAV.UAV_Module.Quadrotor
{
    public class PropellorRotate : MonoBehaviour
    {
        [Header("Rotation direction of propeller: true: clockwise, false: counterclockwise")] public bool RotationDec;

        [Header("Whether to start the motor")] public bool IsStart;

        [Header("Propeller object")] public GameObject PropellorObject;

        [Header("Propeller object rotation speed / degrees per second")] public float RotationAngleRate;

        private int _rotationDec;
        // Start is called before the first frame update
        //   void Start()
        //  {
        //  }
        void FixedUpdate()
        {
            if (IsStart)
            {
                _rotationDec = RotationDec ? 1 : -1;
                PropellorObject.transform.Rotate(new Vector3(0, 1, 0), RotationAngleRate * UnityEngine.Time.fixedDeltaTime * _rotationDec, Space.Self);
            }

        }
    }
}