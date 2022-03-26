/*
 * Author: Yuanlin Yang
 * Date: 2022-1-3
 * Location: Guangdong University of Technology
 */
using System.Collections;
using System.Collections.Generic;
using UnityEngine;

namespace DTUAV.Visualization_Module
{
    /*------------>How To Use This Code<-----------------------------
     * (1)include the namespace: using DTUAVCARS.DTVisualization
     * (2)define a class instance : private show_trajectory _showTrajectory = new show_trajectory(Material mat, Color color, float widthX, float widthY, Vector3 lastPosition, bool isPlot, float duration)
     * (3)update && get data:1)set the currentPosition:_showTrajectory.SetCurrentPosition(currentPositionRos)
     *                       3)draw the line:DrawLine()
     *
     */
    public class show_trajectory
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

        public show_trajectory(Material mat, Color color, float widthX, float widthY, Vector3 lastPosition, bool isPlot, float duration)
        {
            _mat = mat;
            _color = color;
            _widthX = widthX;
            _widthY = widthY;
            _lastPosition = lastPosition;
            _isPlot = isPlot;
            _duration = duration;
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
                GameObject.Destroy(myLine, _duration);
                return true;
            }
            else
            {
                return false;
            }
           
        }





    }
}
