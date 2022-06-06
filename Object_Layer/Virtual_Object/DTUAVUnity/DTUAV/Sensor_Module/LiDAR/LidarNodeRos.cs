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
using RosSharp.RosBridgeClient;
using System.Collections;
using System.Collections.Generic;
using System.Threading;
using RosSharp.RosBridgeClient.MessageTypes.Std;
using UnityEngine;

namespace DTUAV.Sensor_Module.LiDAR
{
    public class LidarNodeRos : UnityPublisher<RosSharp.RosBridgeClient.MessageTypes.Sensor.LaserScan>
    {
        [Header("The Layer Mask of Lidar Perception")]
        public LayerMask LayerMaskUsing;
        [Header("The Perceived Minimum Distance")]
        public float MinRange;
        [Header("The Perceived Maximum Distance")]
        public float MaxRange;
        [Header("The Start Angle of Vertical Direction")]
        public float VerticalAngleStart;
        [Header("The End Angle of Vertical Direction")]
        public float VerticalAngleEnd;
        [Header("The Increment of Vertical Angle")]
        public float VerticalAngleInc;
        [Header("The Start Angle of Horizontal Direction")]
        public float HorizontalAngleStart;
        [Header("The End Angle of Horizontal Direction")]
        public float HorizontalAngleEnd;
        [Header("The Increment of Horizontal Angle")]
        public float HorizontalAngleInc;
        [Header("Is Show Lidar")]
        public bool ShowLidar;
        [Header("The Transform of Lidar Object")]
        public Transform LidarObject;
        [Header("The Running Frequency of Lidar")]
        public float RunHz;
        [Header("The Frame ID of Lidar Scan Message")]
        public string FrameId = "Lidar";

        private RosSharp.RosBridgeClient.MessageTypes.Sensor.LaserScan _message;
        private Vector3 _currentPosition;
        private Lidar _lidarNode;
        private Thread _lidarThread;
        private int _sleepTime;
        private bool _isRun;
        private float _systemTime;
        private List<Vector3> _rayPositions;
        private List<float> _rayDistances;
        private List<float> _intensities;
        private int _pointNum;
        private void SendLidarMsg()
        {
            if (_rayDistances.Count > 0)
            {
                _message.scan_time = _systemTime;
                _message.header.Update();
                _message.ranges = _rayDistances.ToArray();
                _message.intensities = _intensities.ToArray();
                Publish(_message);
            }
        }

        // Start is called before the first frame update
        protected override void Start()
        {
            base.Start();
            _pointNum = (int)((HorizontalAngleEnd - HorizontalAngleStart) / HorizontalAngleInc);
           // Debug.Log(_pointNum);
            _message = new RosSharp.RosBridgeClient.MessageTypes.Sensor.LaserScan
            {
                header = new RosSharp.RosBridgeClient.MessageTypes.Std.Header { frame_id = FrameId },
                angle_min = HorizontalAngleStart * 3.14f/180,
                angle_max = HorizontalAngleEnd * 3.14f / 180,
                angle_increment = HorizontalAngleInc * 3.14f / 180,
                time_increment = 1.0f/RunHz,
                scan_time = 0,
                range_min = MinRange,
                range_max = MaxRange,
                ranges = new float[_pointNum+1],
                intensities = new float[_pointNum + 1]
            };
            _sleepTime = (int)((1.0 / RunHz) * 1000);
            _isRun = true;
            _currentPosition = LidarObject.position;
            _rayPositions = new List<Vector3>();
            _rayDistances = new List<float>();
            _intensities = new List<float>();
            _lidarNode = new Lidar(LayerMaskUsing, MinRange, MaxRange, _currentPosition, VerticalAngleStart, VerticalAngleEnd, VerticalAngleInc, HorizontalAngleStart, HorizontalAngleEnd, HorizontalAngleInc, ShowLidar);
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
                _systemTime += (1.0f / RunHz);
                _rayDistances.Clear();
                _rayPositions.Clear();
                Loom.QueueOnMainThread(() =>
                {
                    _currentPosition = LidarObject.position;
                    _lidarNode.UpdateSensor(_currentPosition, LidarObject.transform.eulerAngles.y, LidarObject.transform.eulerAngles.y + (HorizontalAngleEnd - HorizontalAngleStart));
                    _rayDistances = _lidarNode.GetDistances();
                    _rayPositions = _lidarNode.GetRayPosition();
                    _intensities = _lidarNode.GetIntensities();
                    SendLidarMsg();
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