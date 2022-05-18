using System.Collections;
using System.Collections.Generic;
using UnityEngine;

namespace DTUAV.Algorithm_Module.Path_Planning.RRT
{
    public class RRTNode : MonoBehaviour
    {
        [Header("RRT")]
        public float stepDetal;//the step to move
        public long maxFindStep;//the max step to find the path
        public float safeRange;//the safe range
        public float findError;
        public float rangeProbability;
        public Vector2 startPosition;
        public Vector2 targetPosition;
        public Vector2 workMinRange;
        public Vector2 workMaxRange;
        public float height;

        [Header("Sensor")]
        public LayerMask layerMask;
        public float minRange;
        public float maxRange;
        public Vector3 currentPosition;
        public float horizontalAngleStart;
        public float horizontalAngleEnd;
        public float horizontalAngleInc;
        public bool showLidar;

        [Header("Draw Line")] 
        public Material mat;
        public Color color;
        public float widthX;
        public float widthY;
        public bool isPlot;

        private RRT2D _rrt2D;
        // Start is called before the first frame update
        void Start()
        {
            _rrt2D = new RRT2D(stepDetal, maxFindStep,startPosition, targetPosition, workMinRange, workMaxRange, safeRange, findError, rangeProbability, height);
            _rrt2D.InitSensor(layerMask, minRange, maxRange, currentPosition, horizontalAngleStart, horizontalAngleEnd,
                horizontalAngleInc, safeRange, showLidar);
            _rrt2D.InitPlotLine(mat, color, widthX, widthY, isPlot);
            _rrt2D.FindPath(startPosition, targetPosition);
            Debug.Log(_rrt2D.GetIsFind());
            Debug.Log(_rrt2D.GetPath());
            for (int i = 0; i < _rrt2D.GetPath().Count; i++)
            {
                Debug.Log(_rrt2D.GetPath()[i]);
            }
        }

        // Update is called once per frame
        void Update()
        {

        }
    }
}
