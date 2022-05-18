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
using System.Collections.Generic;
using UnityEngine;

namespace DTUAV.VR
{
    /*------------>How To Use This Code<-----------------------------
     * (1)include the namespace: using DTUAVCARS.DTVisualization
     * (2)define a class instance : private show_trajectory _showTrajectory = new show_trajectory(Material mat, Color color, float widthX, float widthY, Vector3 lastPosition, bool isPlot, float duration)
     * (3)update && get data:1)set the currentPosition:_showTrajectory.SetCurrentPosition(currentPositionRos)
     *                       3)draw the line:DrawLine()
     *
     */
    public class Trajectory
    {
        private Material _mat;//The Material of Draw Line
        private Color _color;//The Color of Draw Line
        private float _widthX;//The Width X of Draw Line
        private float _widthY;//The Width Y of Draw Line
        private Vector3 _lastPosition;//The Start Position of Draw Line
        private Vector3 _currentPosition;//The End Position of Draw Line
        private bool _isPlot;//The Flag to Draw Line
        private List<GameObject> _lineObjects;//The all Draw Lines Objects
        private float _duration;//The exit Time of Draw Line
        private bool _isAuto = false;
        public List<Vector3> GetMissionPath(float distance)
        {
            List<Vector3> ret = new List<Vector3>(_lineObjects.Count);
            if (!(_lineObjects.Count<=0))
            {
                Vector3 startPos = _lineObjects[0].transform.position;
                ret.Add(TF.TF.Unity2Ros(startPos));
                for (int i = 1; i < _lineObjects.Count; i++)
                {
                    if (Vector3.Distance(startPos,_lineObjects[i].transform.position)>=distance)
                    {
                        ret.Add(TF.TF.Unity2Ros(_lineObjects[i].transform.position));
                        startPos = _lineObjects[i].transform.position;
                    }
                }
            }
            return ret;
        }
        public Trajectory(Material mat, Color color, float widthX, float widthY, Vector3 lastPosition, bool isPlot, float duration, bool isAuto)
        {
            _mat = mat;
            _color = color;
            _widthX = widthX;
            _widthY = widthY;
            _lastPosition = lastPosition;
            _isPlot = isPlot;
            _duration = duration;
            _isAuto = isAuto;
            _lineObjects = new List<GameObject>();
        }
        public Trajectory(Material mat, Color color, float widthX, float widthY, Vector3 lastPosition, bool isPlot, float duration)
        {
            _mat = mat;
            _color = color;
            _widthX = widthX;
            _widthY = widthY;
            _lastPosition = lastPosition;
            _isPlot = isPlot;
            _duration = duration;
            _lineObjects = new List<GameObject>();
        }

        public bool SetIsAuto(bool auto)
        {
            _isAuto = auto;
            return true;
        }
        public bool ClearAllLine()
        {
            for (int i = 0; i < _lineObjects.Count; i++)
            {
                GameObject.Destroy(_lineObjects[i]);
            }
            _lineObjects.Clear();
            return true;
        }
        public bool SetCurrentPosition(Vector3 currentPosition)
        {
            _currentPosition = currentPosition;
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

        public bool SetLastPosition(Vector3 lastPosition)
        {
            _lastPosition = lastPosition;
            return true;
        }

        public bool SetIsPlot(bool isPlot)
        {
            _isPlot = isPlot;
            return true;
        }

        public bool SetDuration(float duration)
        {
            _duration = duration;
            return true;
        }

        [System.Obsolete]
        public bool DrawLine()
        {
            if (_isPlot)
            {
                GameObject myLine = new GameObject();
                myLine.AddComponent<LineRenderer>();
                myLine.transform.position = _lastPosition;
                LineRenderer lr = myLine.GetComponent<LineRenderer>();
                lr.material = _mat;
                lr.SetColors(_color, _color);
                ;
                lr.SetWidth(_widthX, _widthY);
                lr.SetPosition(0, _lastPosition);
                lr.SetPosition(1, _currentPosition);
                _lastPosition = _currentPosition;
                if (_isAuto)
                {
                    GameObject.Destroy(myLine, _duration);
                }
                else
                {
                    _lineObjects.Add(myLine);
                }

                return true;
            }
            else
            {
                return false;
            }

        }
    }
}
