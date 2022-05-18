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

namespace DTUAV.Visualization_Module.Line
{
    public class Line
    {
        private Material _mat;//The Material of Draw Line
        private Color _color;//The Color of Draw Line
        private float _widthX;//The Width X of Draw Line
        private float _widthY;//The Width Y of Draw Line
        private Vector3 _startPosition;//The Start Position of Draw Line
        private Vector3 _targetPosition;//The End Position of Draw Line
        private bool _isPlot;//The Flag to Draw Line
        private List<GameObject> _lineObjects;//The all Draw Lines Objects

        public bool ClearAllLine()
        {
            for (int i = 0; i < _lineObjects.Count; i++)
            {
                GameObject.Destroy(_lineObjects[i]);
            }

            return true;
        }
        public Line(Material mat, Color color, float widthX, float widthY, bool isPlot)
        {
            _mat = mat;
            _color = color;
            _widthX = widthX;
            _widthY = widthY;
            _isPlot = isPlot;
            _startPosition = new Vector3();
            _targetPosition = new Vector3();
            _lineObjects = new List<GameObject>();
           
        }

        public bool SetPosition(Vector3 startPosition,Vector3 targetPosition)
        {
            _startPosition = startPosition;
            _targetPosition = targetPosition;
            return true;
        }

        public bool SetMaterial(Material mat)
        {
            _mat = mat;
            return true;
        }

        public bool SetColor(Color color)
        {
            _color = color;
            return true;
        }

        public bool SetWidthX(float widthX)
        {
            _widthX = widthX;
            return true;
        }

        public bool SetWidthY(float widthY)
        {
            _widthY = widthY;
            return true;
        }

        public bool SetIsPlot(bool isPlot)
        {
            _isPlot = isPlot;
            return true;
        }


        [System.Obsolete]
        public bool DrawLine()
        {
            if (_isPlot)
            {
                GameObject myLine = new GameObject();
                myLine.AddComponent<LineRenderer>();
                myLine.transform.position = _startPosition;
                LineRenderer lr = myLine.GetComponent<LineRenderer>();
                lr.material = _mat;
                lr.SetColors(_color, _color);
                ;
                lr.SetWidth(_widthX, _widthY);
                lr.SetPosition(0, _startPosition);
                lr.SetPosition(1, _targetPosition);
                _lineObjects.Add(myLine);
                //GameObject.Destroy(myLine, _duration);
                return true;
            }
            else
            {
                return false;
            }

        }

    }
}
