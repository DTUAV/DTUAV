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

namespace DTUAV.Sensor_Module.Imu
{
    public class Imu
    {
        private Rigidbody _rb;
        private Vector3 _lastPosition;
        private Vector3 _lastVelocity;
        private Quaternion _rotation;
        private Vector3 _angularVelocity;
        private Vector3 _linearAcceleration;

        public Imu(Rigidbody rb)
        {
            _rb = rb;
            _lastPosition = rb.position;
            _lastVelocity = new Vector3();
            _rotation = rb.rotation;
            _angularVelocity = rb.angularVelocity;
            _linearAcceleration = new Vector3();
        }

        public bool UpdateSensor(float step)
        {
            Vector3 curVelocity = (_rb.position - _lastPosition) / step;
            _lastPosition = _rb.position;
            _linearAcceleration = (curVelocity - _lastVelocity) / step;
            _lastVelocity = curVelocity;
            _rotation = _rb.rotation;
            _angularVelocity = _rb.angularVelocity;
            return true;
        }

        public Vector3 GetLinearAcceleration()
        {
            return _linearAcceleration;
        }

        public Quaternion GetRotation()
        {
            return _rotation;
        }

        public Vector3 GetAngularVelocity()
        {
            return _angularVelocity;
        }
    }
}
