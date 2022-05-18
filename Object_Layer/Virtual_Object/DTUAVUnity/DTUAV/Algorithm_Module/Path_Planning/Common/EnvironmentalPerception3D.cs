using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.EventSystems;

namespace DTUAV.Algorithm_Module.Path_Planning
{

    public class EnvironmentalPerception3D
    {
        private LayerMask _layerMask;
        private float _minRange;
        private float _maxRange;
        private Vector3 _currentPosition;
        private float _verticalAngleStart;
        private float _verticalAngleEnd;
        private float _verticalAngleInc;
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
            bool isSafe = false;
            for (int i = 0; i < _distances.Count; i++)
            {
                if (_distances[i] <= _safeRange)
                {
                    isSafe = false;
                    break;
                }
                else
                {
                    isSafe = true;
                }
            }
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

        public bool SetVerticalAngleInc(float verticalAngleInc)
        {
            _verticalAngleInc = verticalAngleInc;
            UpdateDirection();
            return true;
        }

        public bool SetVerticalAngleEnd(float verticalAngleEnd)
        {
            _verticalAngleEnd = verticalAngleEnd;
            UpdateDirection();
            return true;
        }

        public bool SetVerticalAngleStart(float verticalAngleStart)
        {
            _verticalAngleStart = verticalAngleStart;
            UpdateDirection();
            return true;
        }

        private void UpdateDirection()
        {
            float currentVerticalAngle = _verticalAngleStart;
            float currenthorizontalAngle = _horizontalAngleStart;
            while (currenthorizontalAngle <= _horizontalAngleEnd)
            {
                while (currentVerticalAngle <= _verticalAngleEnd)
                {
                    _rayDirections.Add(new Vector3(Mathf.Cos(currentVerticalAngle * Mathf.PI / 180.0f) * Mathf.Sin(currenthorizontalAngle * Mathf.PI / 180.0f), Mathf.Sin(currentVerticalAngle * Mathf.PI / 180.0f), Mathf.Cos(currentVerticalAngle * Mathf.PI / 180.0f) * Mathf.Cos(currenthorizontalAngle * Mathf.PI / 180.0f)));
                    currentVerticalAngle = currentVerticalAngle + _verticalAngleInc;
                }

                currenthorizontalAngle = _verticalAngleStart;
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
        public float GetVerticalAngleInc()
        {
            return _verticalAngleInc;
        }
        public float GetVerticalAngleEnd()
        {
            return _verticalAngleEnd;
        }
        public float GetVerticalAngleStart()
        {
            return _verticalAngleStart;
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
        public EnvironmentalPerception3D(LayerMask layerMask, float minRange, float maxRange, Vector3 currentPosition,
            float verticalAngleStart, float verticalAngleEnd, float verticalAngleInc, float horizontalAngleStart,
            float horizontalAngleEnd, float horizontalAngleInc,float safeRange)
        {
            _layerMask = layerMask;
            _minRange = minRange;
            _maxRange = maxRange;
            _currentPosition = currentPosition;
            _verticalAngleStart = verticalAngleStart;
            _verticalAngleEnd = verticalAngleEnd;
            _verticalAngleInc = verticalAngleInc;
            _horizontalAngleStart = horizontalAngleStart;
            _horizontalAngleEnd = horizontalAngleEnd;
            _horizontalAngleInc = horizontalAngleInc;
            _safeRange = safeRange;
            _showLidar = false;
            _rayDirections = new List<Vector3>();
            _rayPositions = new List<Vector3>();
            _distances = new List<float>();
            float currentVerticalAngle = _verticalAngleStart;
            float currenthorizontalAngle = _horizontalAngleStart;
            while (currenthorizontalAngle <= _horizontalAngleEnd)
            {
                while (currentVerticalAngle <= _verticalAngleEnd)
                {
                    _rayDirections.Add(new Vector3(Mathf.Cos(currentVerticalAngle * Mathf.PI / 180.0f) * Mathf.Sin(currenthorizontalAngle * Mathf.PI / 180.0f), Mathf.Sin(currentVerticalAngle * Mathf.PI / 180.0f), Mathf.Cos(currentVerticalAngle * Mathf.PI / 180.0f) * Mathf.Cos(currenthorizontalAngle * Mathf.PI / 180.0f)));
                    currentVerticalAngle = currentVerticalAngle + _verticalAngleInc;
                }

                currenthorizontalAngle = _verticalAngleStart;
                currenthorizontalAngle = currenthorizontalAngle + _horizontalAngleInc;
            }
        }

        public EnvironmentalPerception3D(LayerMask layerMask, float minRange, float maxRange, Vector3 currentPosition,
            float verticalAngleStart, float verticalAngleEnd, float verticalAngleInc, float horizontalAngleStart,
            float horizontalAngleEnd, float horizontalAngleInc, float safeRange, bool showLidar)
        {
            _layerMask = layerMask;
            _minRange = minRange;
            _maxRange = maxRange;
            _currentPosition = currentPosition;
            _verticalAngleStart = verticalAngleStart;
            _verticalAngleEnd = verticalAngleEnd;
            _verticalAngleInc = verticalAngleInc;
            _horizontalAngleStart = horizontalAngleStart;
            _horizontalAngleEnd = horizontalAngleEnd;
            _horizontalAngleInc = horizontalAngleInc;
            _safeRange = safeRange;
            _showLidar = showLidar;
            _rayDirections = new List<Vector3>();
            _rayPositions = new List<Vector3>();
            _distances = new List<float>();
            float currentVerticalAngle = _verticalAngleStart;
            float currenthorizontalAngle = _horizontalAngleStart;
            while (currenthorizontalAngle <= _horizontalAngleEnd)
            {
                while (currentVerticalAngle <= _verticalAngleEnd)
                {
                    _rayDirections.Add(new Vector3(Mathf.Cos(currentVerticalAngle * Mathf.PI / 180.0f) * Mathf.Sin(currenthorizontalAngle * Mathf.PI / 180.0f), Mathf.Sin(currentVerticalAngle * Mathf.PI / 180.0f), Mathf.Cos(currentVerticalAngle * Mathf.PI / 180.0f) * Mathf.Cos(currenthorizontalAngle * Mathf.PI / 180.0f)));
                    currentVerticalAngle = currentVerticalAngle + _verticalAngleInc;
                }
                currentVerticalAngle = _verticalAngleStart;
                currenthorizontalAngle = currenthorizontalAngle + _horizontalAngleInc;
            }
        }

    }

}
