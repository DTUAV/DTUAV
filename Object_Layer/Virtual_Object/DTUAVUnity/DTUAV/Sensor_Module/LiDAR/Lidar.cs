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
using DTUAV.Math.DataNoise;
using UnityEngine;
using UnityEngine.EventSystems;

namespace DTUAV.Sensor_Module.LiDAR
{
    
    public class Lidar
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
        private List<float> _intensities;
        private bool _showLidar;
        private bool _isAddNoise =false;
        private Vector3 _noise;
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
                    currentVerticalAngle += _verticalAngleInc;
                    //currentVerticalAngle =  currentVerticalAngle > 360 ? currentVerticalAngle - 360:currentVerticalAngle < -360 ? currentVerticalAngle + 360 : currentVerticalAngle;
                }
                currentVerticalAngle = _verticalAngleStart;
                currenthorizontalAngle += _horizontalAngleInc;
                //currenthorizontalAngle = currenthorizontalAngle > 360 ? currenthorizontalAngle - 360 : currenthorizontalAngle < -360 ? currenthorizontalAngle + 360 : currenthorizontalAngle;
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

        public List<float> GetIntensities()
        {
            return _intensities;
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

        //2D Lidar with updated yaw
        public bool UpdateSensor(Vector3 currentPosition,float horizontalAngleStart,float horizontalAngleEnd)
        {
            _horizontalAngleStart = horizontalAngleStart;
            _horizontalAngleEnd = horizontalAngleEnd;
            _rayDirections.Clear();
            UpdateDirection();
            _distances.Clear();
            _rayPositions.Clear();
            _intensities.Clear();
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
                        if (_isAddNoise)
                        {
                            targetRayPosition.x = currentPosition.x + _minRange * ray.direction.x + (float) DataNoise.GaussNiose1() / 100.0f;
                            targetRayPosition.y = currentPosition.y + _minRange * ray.direction.y + (float) DataNoise.GaussNiose1() / 100.0f; ;
                            targetRayPosition.z = currentPosition.z + _minRange * ray.direction.z + (float) DataNoise.GaussNiose1() / 100.0f; ;
                            _distances.Add(_minRange + (float) DataNoise.GaussNiose1() / 100.0f);
                        }
                        else
                        {
                            targetRayPosition.x = currentPosition.x + _minRange * ray.direction.x;
                            targetRayPosition.y = currentPosition.y + _minRange * ray.direction.y;
                            targetRayPosition.z = currentPosition.z + _minRange * ray.direction.z;
                            _distances.Add(_minRange);
                        }
                        
                        if (_showLidar)
                        {
                            Debug.DrawLine(currentPosition, targetRayPosition, Color.red);
                        }
                        _rayPositions.Add(targetRayPosition);
                        _intensities.Add(0);

                    }
                    else
                    {
                        if (_showLidar)
                        {
                            Debug.DrawLine(currentPosition, hit.point, Color.red);
                        }

                        if (_isAddNoise)
                        {
                            _noise.x = (float) DataNoise.GaussNiose1() / 100.0f;
                            _noise.y = (float)DataNoise.GaussNiose1() / 100.0f;
                            _noise.z = (float)DataNoise.GaussNiose1() / 100.0f;
                            _rayPositions.Add(hit.point + _noise);
                            _distances.Add(hit.distance+ (float)DataNoise.GaussNiose1() / 100.0f);
                        }
                        else
                        {
                            _rayPositions.Add(hit.point);
                            _distances.Add(hit.distance);
                        }
                        _intensities.Add(255 * (hit.distance - _minRange) / _minRange);

                    }
                }
                else
                {
                    if (_isAddNoise)
                    {
                        targetRayPosition.x = currentPosition.x + _maxRange * ray.direction.x + (float)DataNoise.GaussNiose1() / 100.0f;
                        targetRayPosition.y = currentPosition.y + _maxRange * ray.direction.y + (float)DataNoise.GaussNiose1() / 100.0f;
                        targetRayPosition.z = currentPosition.z + _maxRange * ray.direction.z + (float)DataNoise.GaussNiose1() / 100.0f;
                        _distances.Add(_maxRange + (float)DataNoise.GaussNiose1() / 100.0f);
                    }
                    else
                    {
                        targetRayPosition.x = currentPosition.x + _maxRange * ray.direction.x;
                        targetRayPosition.y = currentPosition.y + _maxRange * ray.direction.y;
                        targetRayPosition.z = currentPosition.z + _maxRange * ray.direction.z;
                        _distances.Add(_maxRange);
                    }

                    if (_showLidar)
                    {
                        Debug.DrawLine(currentPosition, targetRayPosition, Color.blue);
                    }
                    _rayPositions.Add(targetRayPosition);
                    _intensities.Add(255);
                }
            }
            return true;
        }

        public bool UpdateSensor(Vector3 currentPosition)
        {
            _distances.Clear();
            _rayPositions.Clear();
            _intensities.Clear();
            _currentPosition = currentPosition;
            Ray ray = new Ray(_currentPosition,Vector3.zero);
            RaycastHit hit;
            Vector3 targetRayPosition = Vector3.zero;
            for (int i = 0; i < _rayDirections.Count; i++)
            {
                ray.direction = _rayDirections[i];
                if (Physics.Raycast(ray, out hit, _maxRange, _layerMask))
                {
                    if (hit.distance < _minRange)
                    {
                        if (_isAddNoise)
                        {
                            targetRayPosition.x = currentPosition.x + _minRange * ray.direction.x + (float)DataNoise.GaussNiose1() / 100.0f;
                            targetRayPosition.y = currentPosition.y + _minRange * ray.direction.y + (float)DataNoise.GaussNiose1() / 100.0f; ;
                            targetRayPosition.z = currentPosition.z + _minRange * ray.direction.z + (float)DataNoise.GaussNiose1() / 100.0f; ;
                            _distances.Add(_minRange + (float)DataNoise.GaussNiose1() / 100.0f);
                        }
                        else
                        {
                            targetRayPosition.x = currentPosition.x + _minRange * ray.direction.x;
                            targetRayPosition.y = currentPosition.y + _minRange * ray.direction.y;
                            targetRayPosition.z = currentPosition.z + _minRange * ray.direction.z;
                            _distances.Add(_minRange);
                        }

                        if (_showLidar)
                        {
                            Debug.DrawLine(currentPosition, targetRayPosition, Color.red);
                        }
                        _rayPositions.Add(targetRayPosition);
                        _intensities.Add(0);

                    }
                    else
                    {
                        if (_showLidar)
                        {
                            Debug.DrawLine(currentPosition, hit.point, Color.red);
                        }

                        if (_isAddNoise)
                        {
                            _noise.x = (float)DataNoise.GaussNiose1() / 100.0f;
                            _noise.y = (float)DataNoise.GaussNiose1() / 100.0f;
                            _noise.z = (float)DataNoise.GaussNiose1() / 100.0f;
                            _rayPositions.Add(hit.point +_noise);
                            _distances.Add(hit.distance + (float)DataNoise.GaussNiose1() / 100.0f);
                        }
                        else
                        {
                            _rayPositions.Add(hit.point);
                            _distances.Add(hit.distance);
                        }
                        _intensities.Add(255 * (hit.distance - _minRange) / _maxRange);

                    }
                }
                else
                {
                    if (_isAddNoise)
                    {
                        targetRayPosition.x = currentPosition.x + _maxRange * ray.direction.x + (float)DataNoise.GaussNiose1() / 100.0f;
                        targetRayPosition.y = currentPosition.y + _maxRange * ray.direction.y + (float)DataNoise.GaussNiose1() / 100.0f;
                        targetRayPosition.z = currentPosition.z + _maxRange * ray.direction.z + (float)DataNoise.GaussNiose1() / 100.0f;
                        _distances.Add(_maxRange + (float)DataNoise.GaussNiose1() / 100.0f);
                    }
                    else
                    {
                        targetRayPosition.x = currentPosition.x + _maxRange * ray.direction.x;
                        targetRayPosition.y = currentPosition.y + _maxRange * ray.direction.y;
                        targetRayPosition.z = currentPosition.z + _maxRange * ray.direction.z;
                        _distances.Add(_maxRange);
                    }

                    if (_showLidar)
                    {
                        Debug.DrawLine(currentPosition, targetRayPosition, Color.blue);
                    }
                    _rayPositions.Add(targetRayPosition);
                    _intensities.Add(255);
                }
            }
            return true;
        }
        public Lidar(LayerMask layerMask, float minRange, float maxRange, Vector3 currentPosition,
            float verticalAngleStart, float verticalAngleEnd, float verticalAngleInc, float horizontalAngleStart,
            float horizontalAngleEnd, float horizontalAngleInc)
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
            _showLidar = false;
            _isAddNoise = false;
            _rayDirections = new List<Vector3>();
            _rayPositions = new List<Vector3>();
            _distances = new List<float>();
            _intensities = new List<float>();
            _noise = new Vector3();
            float currentVerticalAngle = _verticalAngleStart;
            float currenthorizontalAngle = _horizontalAngleStart;
            while (currenthorizontalAngle<=_horizontalAngleEnd)
            {
                while (currentVerticalAngle<=_verticalAngleEnd)
                {
                    _rayDirections.Add(new Vector3(Mathf.Cos(currentVerticalAngle*Mathf.PI/180.0f)* Mathf.Sin(currenthorizontalAngle * Mathf.PI / 180.0f),Mathf.Sin(currentVerticalAngle*Mathf.PI/180.0f), Mathf.Cos(currentVerticalAngle * Mathf.PI / 180.0f) * Mathf.Cos(currenthorizontalAngle * Mathf.PI / 180.0f)));
                    currentVerticalAngle = currentVerticalAngle + _verticalAngleInc;
                }

                currenthorizontalAngle = _verticalAngleStart;
                currenthorizontalAngle = currenthorizontalAngle + _horizontalAngleInc;
            }
        }

        public Lidar(LayerMask layerMask, float minRange, float maxRange, Vector3 currentPosition,
            float verticalAngleStart, float verticalAngleEnd, float verticalAngleInc, float horizontalAngleStart,
            float horizontalAngleEnd, float horizontalAngleInc,bool showLidar)
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
            _showLidar = showLidar;
            _isAddNoise = false;
            _rayDirections = new List<Vector3>();
            _rayPositions = new List<Vector3>();
            _distances = new List<float>();
            _intensities = new List<float>();
            _noise = new Vector3();
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
        public Lidar(LayerMask layerMask, float minRange, float maxRange, Vector3 currentPosition,
            float verticalAngleStart, float verticalAngleEnd, float verticalAngleInc, float horizontalAngleStart,
            float horizontalAngleEnd, float horizontalAngleInc, bool showLidar,bool isAddNoise)
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
            _showLidar = showLidar;
            _isAddNoise = isAddNoise;
            _rayDirections = new List<Vector3>();
            _rayPositions = new List<Vector3>();
            _distances = new List<float>();
            _intensities = new List<float>();
            _noise = new Vector3();
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
