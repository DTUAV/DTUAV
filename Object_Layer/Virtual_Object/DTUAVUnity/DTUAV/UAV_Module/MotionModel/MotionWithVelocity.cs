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
using System.Threading;
using UnityEngine;
using DTUAV.TF;

namespace DTUAV.UAV_Module.Quadrotor
{
    public class MotionWithVelocity
    {
        private Rigidbody _objectRigidbody;
        private Vector3 _targetVelocity;
        private float _maxAngle;
        private float _runningHz;
        private int _sleepTime;
        private Thread _runningThread;
        private Vector3 _currentLocalPosition;
        private Vector3 _currentGlobalPosition;
        private Vector3 _currentVelocity;
        private Vector3 _homePosition;
        private bool _isRun;

        public Vector3 GetHomePosition()
        {
            return _homePosition;
        }

        public Vector3 GetCurrentLocalPosition()
        {
            return _currentLocalPosition;
        }

        public Vector3 GetCurrentGlobalPosition()
        {
            return _currentGlobalPosition;
        }

        public Vector3 GetCurrentVelocity()
        {
            return _currentVelocity;
        }

        public bool SetRunningHz(float runningHz)
        {
            _runningHz = runningHz;
            return true;
        }



            public MotionWithVelocity(Rigidbody objectRigidbody, Vector3 targetVelocity, float maxAngle, float runningHz)
        {
            _objectRigidbody = objectRigidbody;
            _homePosition = TF.TF.Unity2Ros(objectRigidbody.position);
            _currentGlobalPosition = TF.TF.Unity2Ros(objectRigidbody.position);
            _currentLocalPosition = Vector3.zero;
            _currentVelocity = TF.TF.Unity2Ros(objectRigidbody.velocity);
            _targetVelocity = targetVelocity;
            _maxAngle = maxAngle;
            _runningHz = runningHz;
            _isRun = true;
            _sleepTime = (int) ((1.0 / _runningHz) * 1000);
            Loom.RunAsync(
                () =>
                {
                    _runningThread = new Thread(Run);
                    _runningThread.IsBackground = true;
                    _runningThread.Start();
                }
            );
        }

        public bool UpdateVelocity(Vector3 velocity)
        {
            _targetVelocity = velocity;
            return true;
        }
        public bool SetIsRun(bool run)
        {
            _isRun = run;
            return true;
        }
        private float CountRotationAngle(float velocity, float k, float maxAngle)
        {
            return maxAngle * (1 - Mathf.Exp(-k * velocity)) / (1 + Mathf.Exp(-k * velocity));
        }

        [System.Obsolete]
        void Run()
        {
            while (_isRun)
            {
                
                Loom.QueueOnMainThread(() =>
                {
                    Vector3 targetGlobalVelocity = TF.TF.Ros2Unity(_targetVelocity);
                    Vector3 currentLocalVelocity = TF.TF.Global2Local(new Vector3(targetGlobalVelocity.z,0,-targetGlobalVelocity.x), _objectRigidbody.rotation.eulerAngles.y * Mathf.Deg2Rad);
                    _objectRigidbody.velocity = TF.TF.Ros2Unity(_targetVelocity);
                    _currentGlobalPosition = TF.TF.Unity2Ros(_objectRigidbody.position);
                    _currentLocalPosition = _currentGlobalPosition - _homePosition;
                    _currentVelocity = TF.TF.Unity2Ros(_objectRigidbody.velocity);
                    _objectRigidbody.rotation = Quaternion.Euler(CountRotationAngle(currentLocalVelocity.x,0.5f,_maxAngle),_objectRigidbody.rotation.eulerAngles.y, CountRotationAngle(currentLocalVelocity.z, 0.5f, _maxAngle));
                });
                System.Threading.Thread.Sleep(_sleepTime);
                /*
                Loom.QueueOnMainThread(() =>
                {
                    _objectRigidbody.velocity = Vector3.zero; // if want to control the simulation frequency
                });
                    System.Threading.Thread.Sleep(_sleepTime);
                  */
            }
        }

    }
}
