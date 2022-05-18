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

public struct CollisionObjectInf
{
    public Vector3 ObjectPosition;
    public Quaternion ObjectDir;
    public float Distance;
    public float SafeDistanceX;
    public float SafeDistanceH;
    public float SafeDistanceZ;
}
public class get_collision : MonoBehaviour
{
    public GameObject Uav;//要避障的无人机对象
    public GameObject UavMotorFR;//无人机1号电机对象
    public GameObject UavMotorFL;//无人机2号电机对象
    public GameObject UavMotorBR;//无人机3号电机对象
    public GameObject UavMotorBL;//无人机4号电机对象
    public float SafeDistanceX;//x轴方向的安全距离
    public float SafeDistanceH;//高度返现的安全距离
    public float SafeDistanceZ;//z轴方向的安全距离
    public int CheckCollisionAngleInc;//避障探测的旋转角度增量
    public float CheckCollisionDistance;//避障探测的距离
    public List<CollisionObjectInf> CollisionInf = new List<CollisionObjectInf>();//障碍物的位置
    public LayerMask Mask;//障碍物的层级
    private Vector3 orDir;

    //检查无人机上方是否有障碍物
    public bool CheckUpCollision()
    {
        bool isCollision = false;
        float checkDistanceX = UavMotorFR.transform.position.x-UavMotorFL.transform.position.x;
        float checkDistanceZ =UavMotorFR.transform.position.z - UavMotorBR.transform.position.z;
        float checkDistanceXInc = checkDistanceX / 10;
        float checkDistanceZInc = checkDistanceZ / 10;
        Vector3 checkCurrentPositionOri = UavMotorBL.transform.position;
        for (int i = 0; i < 10; i++)
        {
            Vector3 checkCurrentPosition = checkCurrentPositionOri;
            checkCurrentPosition.x = checkCurrentPosition.x + i*checkDistanceXInc;
            for (int j = 0; j < 10; j++)
            {
                checkCurrentPosition.z = checkCurrentPositionOri.z + j * checkDistanceZInc;
                Vector3 fwd = transform.TransformDirection(Vector3.up);
                RaycastHit hit;
                if (Physics.Raycast(checkCurrentPosition, fwd, out hit, CheckCollisionDistance,Mask))
                {
                    if (hit.distance<=SafeDistanceH)
                    {
                        isCollision = true;
                        break;
                    }
                }
            }

            if (isCollision)
            {
                break;
            }
        }

        if (isCollision)
        {
            return true;
        }
        else
        {
            return false;
        }
    }
   //检查无人机下方是否有障碍物
    public bool CheckDownCollision()
    {
        bool isCollision = false;
        float checkDistanceX = UavMotorFR.transform.position.x - UavMotorFL.transform.position.x;
        float checkDistanceZ = UavMotorFR.transform.position.z - UavMotorBR.transform.position.z;
        float checkDistanceXInc = checkDistanceX / 10;
        float checkDistanceZInc = checkDistanceZ / 10;
        Vector3 checkCurrentPositionOri = UavMotorBL.transform.position;
        for (int i = 0; i < 10; i++)
        {
            Vector3 checkCurrentPosition = checkCurrentPositionOri;
            checkCurrentPosition.x = checkCurrentPosition.x + i * checkDistanceXInc;
            for (int j = 0; j < 10; j++)
            {
                checkCurrentPosition.z = checkCurrentPositionOri.z + j * checkDistanceZInc;
                Vector3 fwd = transform.TransformDirection(Vector3.down);
                RaycastHit hit;
                if (Physics.Raycast(checkCurrentPosition, fwd, out hit, CheckCollisionDistance, Mask))
                {
                    if (hit.distance <= SafeDistanceH)
                    {
                        isCollision = true;
                        break;
                    }
                }
            }

            if (isCollision)
            {
                break;
            }
        }

        if (isCollision)
        {
            return true;
        }
        else
        {
            return false;
        }
    }
   //检查无人机前方是否有障碍物
    public bool CheckForwardCollision()
    {
        bool isCollision = false;
        float checkDistanceX = UavMotorFR.transform.position.x - UavMotorFL.transform.position.x;
        float checkDistanceXInc = checkDistanceX / 10;
        Vector3 checkCurrentPositionOri = UavMotorFL.transform.position;
        for (int j = 0; j < 10; j++)
        {
                Vector3 checkCurrentPosition = checkCurrentPositionOri;
                checkCurrentPosition.x = checkCurrentPosition.x + j * checkDistanceXInc;
                Vector3 fwd = transform.TransformDirection(Vector3.forward);
                RaycastHit hit;
                if (Physics.Raycast(checkCurrentPosition, fwd, out hit, CheckCollisionDistance, Mask))
                {
                    if (hit.distance <= SafeDistanceZ)
                    {
                        isCollision = true;
                        break;
                    }
                }
            }

        if (isCollision)
        {
            return true;
        }
        else
        {
            return false;
        }
    }
   //检查无人机后方是否有障碍物
    public bool CheckBackCollision()
    {
        bool isCollision = false;
        float checkDistanceX = UavMotorBR.transform.position.x - UavMotorBL.transform.position.x;
        float checkDistanceXInc = checkDistanceX / 10;
        Vector3 checkCurrentPositionOri = UavMotorBL.transform.position;
        for (int j = 0; j < 10; j++)
        {
            Vector3 checkCurrentPosition = checkCurrentPositionOri;
            checkCurrentPosition.x = checkCurrentPosition.x + j * checkDistanceXInc;
            Vector3 fwd = transform.TransformDirection(Vector3.back);
            RaycastHit hit;
            if (Physics.Raycast(checkCurrentPosition, fwd, out hit, CheckCollisionDistance, Mask))
            {
                if (hit.distance <= SafeDistanceZ)
                {
                    isCollision = true;
                    break;
                }
            }
        }

        if (isCollision)
        {
            return true;
        }
        else
        {
            return false;
        }
    }
   //检查无人机右方是否有障碍物
    public bool CheckRightCollision()
    {
        bool isCollision = false;
        float checkDistanceZ = UavMotorFR.transform.position.z - UavMotorBR.transform.position.z;
        float checkDistanceZInc = checkDistanceZ / 10;
        Vector3 checkCurrentPositionOri = UavMotorBR.transform.position;
        for (int j = 0; j < 10; j++)
        {
            Vector3 checkCurrentPosition = checkCurrentPositionOri;
            checkCurrentPosition.z = checkCurrentPosition.z + j * checkDistanceZInc;
            Vector3 fwd = transform.TransformDirection(Vector3.right);
            RaycastHit hit;
            if (Physics.Raycast(checkCurrentPosition, fwd, out hit, CheckCollisionDistance, Mask))
            {
                if (hit.distance <= SafeDistanceX)
                {
                    isCollision = true;
                    break;
                }
            }
        }

        if (isCollision)
        {
            return true;
        }
        else
        {
            return false;
        }
    }
    //检查无人机左方是否有障碍物
    public bool CheckLeftCollision()
    {
        bool isCollision = false;
        float checkDistanceZ = UavMotorFL.transform.position.z - UavMotorBL.transform.position.z;
        float checkDistanceZInc = checkDistanceZ / 10;
        Vector3 checkCurrentPositionOri = UavMotorBL.transform.position;
        for (int j = 0; j < 10; j++)
        {
            Vector3 checkCurrentPosition = checkCurrentPositionOri;
            checkCurrentPosition.z = checkCurrentPosition.z + j * checkDistanceZInc;
            Vector3 fwd = transform.TransformDirection(Vector3.left);
            RaycastHit hit;
            if (Physics.Raycast(checkCurrentPosition, fwd, out hit, CheckCollisionDistance, Mask))
            {
                if (hit.distance <= SafeDistanceX)
                {
                    isCollision = true;
                    break;
                }
            }
        }

        if (isCollision)
        {
            return true;
        }
        else
        {
            return false;
        }
    }
    //此函数未完成--获取无人机水平面的障碍物信息
    public void CheckHorizontalCollision()
    {
        CollisionInf.Clear();//清空容器
        for (int i = 0; i < 360 / CheckCollisionAngleInc; i++)
        {
            float currenAngle = i * CheckCollisionAngleInc;
            Vector3 currentPosition = Vector3.zero;
            currentPosition.z = Uav.transform.position.z +
                                CheckCollisionDistance * Mathf.Cos(currenAngle * Mathf.Deg2Rad);
            currentPosition.x = Uav.transform.position.x +
                                CheckCollisionDistance * Mathf.Sin(currenAngle * Mathf.Deg2Rad);
            currentPosition.y = Uav.transform.position.y;
            Vector3 targetDir = Vector3.zero;
            Quaternion offsetRot = Quaternion.AngleAxis(currenAngle,Uav.transform.up);
            targetDir = offsetRot * orDir;
            Vector3 dir = (currentPosition - Uav.transform.position).normalized;
            Ray rays = new Ray(Uav.transform.position,dir);
            RaycastHit hit;
            if (Physics.Raycast(rays, out hit, CheckCollisionDistance, Mask))
            {
                if (Mathf.Abs(hit.transform.position.x-Uav.transform.position.x)>=SafeDistanceX)
                {
                    
                }
            }

        }
    }

    // Start is called before the first frame update
    void Start()
    {
        orDir = Uav.transform.forward;
    }

    // Update is called once per frame
    void Update()
    {

    }
}
