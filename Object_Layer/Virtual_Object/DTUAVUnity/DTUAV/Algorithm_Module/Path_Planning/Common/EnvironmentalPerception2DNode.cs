using System.Collections;
using System.Collections.Generic;
using UnityEngine;

namespace DTUAV.Algorithm_Module.Path_Planning.RRT
{
    public class EnvironmentalPerception2DNode : MonoBehaviour
    {
        // Start is called before the first frame update
        [Header("Sensor")] public LayerMask layerMask;
        public float minRange;
        public float maxRange;
        public float safeRange;//the safe range
        public Vector3 currentPosition;
        public float horizontalAngleStart;
        public float horizontalAngleEnd;
        public float horizontalAngleInc;
        public bool showLidar;
        public Transform objecTransform;
        private EnvironmentalPerception2D _environmentalPerception2D;
        void Start()
        {
            _environmentalPerception2D = new EnvironmentalPerception2D(layerMask, minRange, maxRange, currentPosition,
                horizontalAngleStart, horizontalAngleEnd, horizontalAngleInc, safeRange, showLidar);
            
        }

        // Update is called once per frame
        void Update()
        {
            _environmentalPerception2D.UpdateSensor(objecTransform.position);
            Debug.Log(_environmentalPerception2D.GetIsSafe());
        }
    }
}
