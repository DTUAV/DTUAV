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

namespace DTUAV.Sensor_Module.Range
{
    public class Range
    {
        private float _minRange;
        private float _maxRange;
        private LayerMask _layerMask;
        private Vector3 _preDirection;
        private Ray _ray;
        private RaycastHit _hit;
        private float _curRange;
        private bool _isShow = false;
        private Vector3 _targetPos;
        public float GetCurRange()
        {
            return _curRange;
        }
        public Range(float minRange, float maxRange, LayerMask layerMask, Vector3 preDirection)
        {
            _minRange = minRange;
            _maxRange = maxRange;
            _layerMask = layerMask;
            _preDirection = preDirection;
            _ray = new Ray();
            _hit = new RaycastHit();
            _ray.direction = _preDirection;
            _isShow = false;
            _targetPos = new Vector3();
        }
        public Range(float minRange, float maxRange, LayerMask layerMask, Vector3 preDirection,bool isShow)
        {
            _minRange = minRange;
            _maxRange = maxRange;
            _layerMask = layerMask;
            _preDirection = preDirection;
            _ray = new Ray();
            _hit = new RaycastHit();
            _ray.direction = _preDirection;
            _isShow = isShow;
            _targetPos = new Vector3();
        }
        public float UpdateSensor(Vector3 pos)
        {
            _ray.origin = pos;
            if (Physics.Raycast(_ray, out _hit, _maxRange, _layerMask))
            {
                if (_hit.distance < _minRange)
                {
                    _curRange = _minRange;
                }
                else
                {
                    _curRange = _hit.distance;
                }
                if (_isShow)
                {
                    _targetPos = pos;
                    _targetPos.y = pos.y - _curRange;
                    Debug.DrawLine(pos, _targetPos, Color.red);
                }
            }
            return _curRange;
        }
    }
}
