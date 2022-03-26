/*
 *
 *  GNU General Public License (GPL)
 *
 * Update Information:
 *                    First: 2021-8-6 In Guangdong University of Technology By Yuanlin Yang  Email: yongwang0808@163.com
 *
 *
 *
 *
 *
 */

using System.Collections;
using System.Collections.Generic;
using UnityEngine;

namespace DTUAV.UAV_Module.Quadrotor
{
    public class PropellorRotate : MonoBehaviour
    {
        [Header("Rotation direction of propeller: true: clockwise, false: counterclockwise")] public bool RotationDec;

        [Header("Whether to start the motor")] public bool IsStart;

        [Header("Propeller object")] public GameObject PropellorObject;

        [Header("Propeller object rotation speed / degrees per second")] public float RotationAngleRate;

        private int _rotationDec;
        // Start is called before the first frame update
        //   void Start()
        //  {
        //  }
        void FixedUpdate()
        {
            if (IsStart)
            {
                _rotationDec = RotationDec ? 1 : -1;
                PropellorObject.transform.Rotate(new Vector3(0, 1, 0), RotationAngleRate * UnityEngine.Time.fixedDeltaTime * _rotationDec, Space.Self);
            }

        }
    }
}