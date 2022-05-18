using System.Collections;
using System.Collections.Generic;
using UnityEngine;

namespace DTUAV.Algorithm_Module.Path_Planning
{
    public class EnvironmentalPerception2D
    {
        private LayerMask _layerMask;
        private float _minRange;
        private float _maxRange;
        private Vector3 _currentPosition;
        private float _horizontalAngleStart;
        private float _horizontalAngleEnd;
        private float _horizontalAngleInc;
        private List<Vector3> _rayDirections;
        private List<Vector3> _rayPositions;
        private List<float> _distances;
        private bool _showLidar;
        private float _safeRange;


        public bool GetIsSafe()
        {
            bool isSafe = true;
            for (int i = 0; i < _distances.Count; i++)
            {
                if (_distances[i] <= _safeRange)
                {
                    isSafe = false;
                    break;
                }
            }
          //  Debug.Log(isSafe);
            return isSafe;
           
        }

        public float GetSafeRange()
        {
            return _safeRange;

        }

        public bool SetSafeRange(float safeRange)
        {
            _safeRange = safeRange;
            return true;
        }

        public bool SetHorizontalAngleInc(float horizontalAngleInc)
        {
            _horizontalAngleInc = horizontalAngleInc;
            UpdateDirection();
            return true;
        }

        public bool SetHorizontalAngleEnd(float horizontalAngleEnd)
        {
            _horizontalAngleEnd = horizontalAngleEnd;
            UpdateDirection();
            return true;
        }

        public bool SetHorizontalAngleStart(float horizontalAngleStart)
        {
            _horizontalAngleStart = horizontalAngleStart;
            UpdateDirection();
            return true;
        }

        private void UpdateDirection()
        {

            float currenthorizontalAngle = _horizontalAngleStart;
            while (currenthorizontalAngle <= _horizontalAngleEnd)
            {
                _rayDirections.Add(new Vector3(Mathf.Sin(currenthorizontalAngle * Mathf.PI / 180.0f), 0,
                    Mathf.Cos(currenthorizontalAngle * Mathf.PI / 180.0f)));

                currenthorizontalAngle = currenthorizontalAngle + _horizontalAngleInc;
            }
        }

        public bool SetCurrentPosition(Vector3 currentPosition)
        {
            _currentPosition = currentPosition;
            return true;
        }

        public bool SetMaxRange(float maxRange)
        {
            _maxRange = maxRange;
            return true;
        }

        public bool SetMinRange(float minRange)
        {
            _minRange = minRange;
            return true;
        }

        public bool SetLayerMask(LayerMask layerMask)
        {
            _layerMask = layerMask;
            return true;
        }

        public bool SetShowLidar(bool isShow)
        {
            _showLidar = isShow;
            return true;
        }

        public Vector3 GetCurrentPosition()
        {
            return _currentPosition;
        }

        public float GetHorizontalAngleInc()
        {
            return _horizontalAngleInc;
        }

        public float GetHorizontalAngleEnd()
        {
            return _horizontalAngleEnd;
        }

        public float GetHorizontalAngleStart()
        {
            return _horizontalAngleStart;
        }

        public float GetMinRange()
        {
            return _minRange;
        }

        public float GetMaxRange()
        {
            return _maxRange;
        }

        public List<float> GetDistances()
        {
            return _distances;
        }

        public List<Vector3> GetRayDirections()
        {
            return _rayDirections;
        }

        public List<Vector3> GetRayPosition()
        {
            return _rayPositions;
        }

        public bool UpdateSensor(Vector3 currentPosition)
        {
           // Debug.Log(currentPosition);
            _distances.Clear();
            _rayPositions.Clear();
            _currentPosition = currentPosition;
            Ray ray = new Ray(_currentPosition, Vector3.zero);
            RaycastHit hit;
            Vector3 targetRayPosition = Vector3.zero;
            for (int i = 0; i < _rayDirections.Count; i++)
            {
                ray.direction = _rayDirections[i];
                if (Physics.Raycast(ray, out hit, _maxRange, _layerMask))
                {
                    if (hit.distance < _minRange)
                    {
                        targetRayPosition.x = currentPosition.x + _minRange * ray.direction.x;
                        targetRayPosition.y = currentPosition.y + _minRange * ray.direction.y;
                        targetRayPosition.z = currentPosition.z + _minRange * ray.direction.z;
                        if (_showLidar)
                        {
                            Debug.DrawLine(currentPosition, targetRayPosition, Color.red);
                        }

                        _rayPositions.Add(targetRayPosition);
                        _distances.Add(_minRange);
                    }
                    else
                    {
                        if (_showLidar)
                        {
                            Debug.DrawLine(currentPosition, hit.point, Color.red);
                        }

                        _rayPositions.Add(hit.point);
                        _distances.Add(hit.distance);
                    }
                }
                else
                {
                    targetRayPosition.x = currentPosition.x + _maxRange * ray.direction.x;
                    targetRayPosition.y = currentPosition.y + _maxRange * ray.direction.y;
                    targetRayPosition.z = currentPosition.z + _maxRange * ray.direction.z;
                    if (_showLidar)
                    {
                        Debug.DrawLine(currentPosition, targetRayPosition, Color.blue);
                    }

                    _rayPositions.Add(targetRayPosition);
                    _distances.Add(_maxRange);
                }
            }

            return true;
        }

        public EnvironmentalPerception2D(LayerMask layerMask, float minRange, float maxRange, Vector3 currentPosition,
            float horizontalAngleStart, float horizontalAngleEnd, float horizontalAngleInc, float safeRange)
        {
            _layerMask = layerMask;
            _minRange = minRange;
            _maxRange = maxRange;
            _currentPosition = currentPosition;
            _horizontalAngleStart = horizontalAngleStart;
            _horizontalAngleEnd = horizontalAngleEnd;
            _horizontalAngleInc = horizontalAngleInc;
            _showLidar = false;
            _safeRange = safeRange;
            _rayDirections = new List<Vector3>();
            _rayPositions = new List<Vector3>();
            _distances = new List<float>();
            float currenthorizontalAngle = _horizontalAngleStart;
            while (currenthorizontalAngle <= _horizontalAngleEnd)
            {
                _rayDirections.Add(new Vector3(Mathf.Sin(currenthorizontalAngle * Mathf.PI / 180.0f), 0,
                    Mathf.Cos(currenthorizontalAngle * Mathf.PI / 180.0f)));
                currenthorizontalAngle = currenthorizontalAngle + _horizontalAngleInc;
            }
        }

        public EnvironmentalPerception2D(LayerMask layerMask, float minRange, float maxRange, Vector3 currentPosition,
            float horizontalAngleStart, float horizontalAngleEnd, float horizontalAngleInc, float safeRange,
            bool showLidar)
        {
            _layerMask = layerMask;
            _minRange = minRange;
            _maxRange = maxRange;
            _currentPosition = currentPosition;
            _horizontalAngleStart = horizontalAngleStart;
            _horizontalAngleEnd = horizontalAngleEnd;
            _horizontalAngleInc = horizontalAngleInc;
            _safeRange = safeRange;
            _showLidar = showLidar;
            _rayDirections = new List<Vector3>();
            _rayPositions = new List<Vector3>();
            _distances = new List<float>();
            float currenthorizontalAngle = _horizontalAngleStart;
            while (currenthorizontalAngle <= _horizontalAngleEnd)
            {
                _rayDirections.Add(new Vector3(Mathf.Sin(currenthorizontalAngle * Mathf.PI / 180.0f), 0,
                    Mathf.Cos(currenthorizontalAngle * Mathf.PI / 180.0f)));
                currenthorizontalAngle = currenthorizontalAngle + _horizontalAngleInc;
            }
        }

    }
}

