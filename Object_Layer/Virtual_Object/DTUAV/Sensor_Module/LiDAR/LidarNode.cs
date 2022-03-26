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

        private List<Vector3> _rayPositions;

        private List<float> _rayDistances;
        // Start is called before the first frame update
        void Start()
        {
            _sleepTime = (int)((1.0 / runHz) * 1000);
            _isRun = true;
            _currentPosition = lidarObject.position;
            _rayPositions = new List<Vector3>();
            _rayDistances = new List<float>();
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
                _rayDistances.Clear();
                _rayPositions.Clear();
                Loom.QueueOnMainThread(() =>
                {
                    _currentPosition = lidarObject.position;
                    _lidarNode.UpdateSensor(_currentPosition);
                    _rayDistances = _lidarNode.GetDistances();
                    _rayPositions = _lidarNode.GetRayPosition();
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
