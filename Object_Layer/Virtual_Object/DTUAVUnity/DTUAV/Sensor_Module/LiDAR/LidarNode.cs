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
using System.Threading;
using UnityEngine;

namespace DTUAV.Sensor_Module.LiDAR
{
    public class LidarNode : MonoBehaviour
    {
        public LayerMask layerMask;
        public float minRange;
        public float maxRange;
        public float verticalAngleStart;
        public float verticalAngleEnd;
        public float verticalAngleInc;
        public float horizontalAngleStart;
        public float horizontalAngleEnd;
        public float horizontalAngleInc;
        public bool showLidar;
        public Transform lidarObject;

        public float runHz;

        private Vector3 _currentPosition;

        private Lidar _lidarNode;

        private Thread _lidarThread;

        private int _sleepTime;

        private bool _isRun;

        public List<Vector3> RayPositions;

        public List<float> RayDistances;
        // Start is called before the first frame update
        void Start()
        {
            _sleepTime = (int)((1.0 / runHz) * 1000);
            _isRun = true;
            _currentPosition = lidarObject.position;
            RayPositions = new List<Vector3>();
            RayDistances = new List<float>();
            _lidarNode = new Lidar(layerMask,minRange,maxRange,_currentPosition,verticalAngleStart,verticalAngleEnd,verticalAngleInc,horizontalAngleStart,horizontalAngleEnd,horizontalAngleInc,showLidar);
            Loom.RunAsync(
                () =>
                {
                    _lidarThread = new Thread(UpdateSensor);
                    _lidarThread.IsBackground = true;
                    _lidarThread.Start();
                }
            );
        }

        void UpdateSensor()
        {
            while (_isRun)
            {
                RayDistances.Clear();
                RayPositions.Clear();
                Loom.QueueOnMainThread(() =>
                {
                    _currentPosition = lidarObject.position;
                    _lidarNode.UpdateSensor(_currentPosition);
                    RayDistances = _lidarNode.GetDistances();
                    RayPositions = _lidarNode.GetRayPosition();
                });
                System.Threading.Thread.Sleep(_sleepTime);
            }
        }

        void OnDestroy()
        {
            _isRun = false;
        }
    }
}
