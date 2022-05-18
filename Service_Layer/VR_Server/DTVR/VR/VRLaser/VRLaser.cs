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
using System.Diagnostics.Eventing.Reader;
using System.Text;
using DigitalTwin.UavCarProject;
using DTUAV.Message;
using DTUAV.Time;
using UnityEngine;
using TMPro;
namespace DTUAV.VR
{
    public class VRLaser : MonoBehaviour
    {
        [Header("The environment layer mask")] public LayerMask EnvironmentLayerMask;
        public move_uav Uav;
        [Header("The name of UAV object")]
        public string UavName;
        [Header("The trajectory of operator")]
        public Transform OperatorTransform;
        public Material OperatorMat;
        public Color OperatorLineColor;
        public float OperatorWidthX;
        public float OperatorWidthY;
        public bool OperatorIsPlot;
        public float OperatorDuration;
        public bool OperatorIsAuto = true;
        private Trajectory _operatorTrajectory;
        [Header("The trajectory of UAV")]
        public Rigidbody UavRb;
        public Material UavMat;
        public Color UavLineColor;
        public float UavWidthX;
        public float UavWidthY;
        public bool UavIsPlot;
        public float UavDuration;
        public bool UavIsAuto = true;
        public VR_Server VrServerNode;
        public int CommandType = 0;//0: one position 1:mission points
        public bool IsAutoPlotPath = false;//if it is set true, the trajectory of operator and uav will be plotted automatically.
        public TextMeshPro UavInfo;
        private Trajectory _uavTrajectory;
        private GameObject myLine = null;
        private bool isHitUav = false;
        private string _showInfo = "VR Server";
        private bool _isShow = false;
        private int _showTime = 0;
        private int _modeId = 0; //0: operator planning mode. 1: uav planning mode. 2: no planning
        private RaycastHit _hit;
        private int _controlMode;//0: virtual UAV. 1: physical UAV

        [System.Obsolete]

        void Start()
        {
            _uavTrajectory = new Trajectory(UavMat,UavLineColor,UavWidthX,UavWidthY,UavRb.position,UavIsPlot,UavDuration,UavIsAuto);
            _operatorTrajectory = new Trajectory(OperatorMat,OperatorLineColor,OperatorWidthX,OperatorWidthY,OperatorTransform.position,OperatorIsPlot,OperatorDuration,OperatorIsAuto);
            UavInfo = UavRb.gameObject.GetComponentInChildren<TextMeshPro>();//
        }
        [System.Obsolete]
        void FixedUpdate()
        {
            if (OVRInput.GetDown(OVRInput.RawButton.LIndexTrigger))
            {
                _modeId = _modeId == 0 ? 1 : _modeId == 1 ? 2 : 0;
                if (_modeId == 0)
                {
                    _showInfo = "Now Enter Operator Planning Mode ...";
                    _operatorTrajectory.ClearAllLine();
                }
                else if(_modeId == 1)
                {
                    _showInfo = "Now Enter UAV Planning Mode ...";
                    _uavTrajectory.ClearAllLine();
                }
                else 
                {
                    _showInfo = "No Planning Mode ...";  
                }
                
                _isShow = true;

            }

            if (OVRInput.GetDown(OVRInput.RawButton.RIndexTrigger))
            {
                IotMessage iotMessage = new IotMessage();
                iotMessage.SourceID = ObjectId.VR_0;
                iotMessage.TimeStamp = SimTime.GetSystemTimeStampNs();
                if (_controlMode == 0)//virtual UAV
                {
                    iotMessage.TargetID = ObjectId.V_UAV_0;
                }
                else if(_controlMode == 1)//physical UAV
                {
                    iotMessage.TargetID = ObjectId.R_UAV_0;
                }

                iotMessage.MessageID = MessageId.ControlApplyMsgID;
                ControlApplyMsg applyMsg = new ControlApplyMsg();
                applyMsg.apply_info = true;
                iotMessage.MessageData = JsonUtility.ToJson(applyMsg);
                string sendApplyMsg = JsonUtility.ToJson(iotMessage);
                VrServerNode.SendMessage(sendApplyMsg);//send apply control message

                if (CommandType == 1)//send all mission point
                {
                    iotMessage.MessageID = MessageId.MissionPointID;
                    List<Vector3> path = new List<Vector3>();
                    if (_modeId == 0)
                    {
                        //Operator Mode
                        path = _operatorTrajectory.GetMissionPath(0.5f);

                    }
                    else if (_modeId == 1)
                    {
                        //UAV Mode
                        path = _uavTrajectory.GetMissionPath(0.5f);
                    }

                    MissionPoint point = new MissionPoint();
                    point.x = new double[path.Count];
                    point.y = new double[path.Count];
                    point.z = new double[path.Count];
                    for (int i = 0; i < path.Count; i++)
                    {
                        point.x[i] = path[i].x;
                        point.y[i] = path[i].y;
                        point.z[i] = path[i].z;
                    }

                    iotMessage.MessageData = JsonUtility.ToJson(point);
                    string msg = JsonUtility.ToJson(iotMessage);
                    VrServerNode.SendMessage(msg);
                }
                else if (CommandType == 0)//send one target position
                {
                    iotMessage.MessageID = MessageId.TargetLocalPositionMsgID;
                    Vector3 pos = new Vector3();
                    TargetLocalPositionMsg targetPos = new TargetLocalPositionMsg();
                    if (_modeId == 0)
                    {
                        pos = TF.TF.Unity2Ros(OperatorTransform.position);
                    }
                    else if (_modeId == 1)
                    {
                        pos = TF.TF.Unity2Ros(UavRb.position);
                    }
                    targetPos.position_x = pos.x;
                    targetPos.position_y = pos.y;
                    targetPos.position_z = pos.z;
                    targetPos.rotation_x = 0;//static
                    targetPos.rotation_y = 0;//static
                    targetPos.rotation_z = 0;//static
                    targetPos.rotation_w = 1;//static
                    iotMessage.MessageData = JsonUtility.ToJson(targetPos);
                    string msg = JsonUtility.ToJson(iotMessage);
                    VrServerNode.SendMessage(msg);
                }
            }

            if (_modeId == 1) //UAV Planning Mode
            {
                if (Physics.Raycast(transform.position, transform.forward, out _hit, float.MaxValue,
                    EnvironmentLayerMask))
                {
                    Debug.DrawLine(transform.position, _hit.point, Color.red);
                    DrawLineGame(transform.position, _hit.point, Color.red);
                    if (_hit.collider.gameObject.name == UavName)
                    {
                        isHitUav = true;
                        Uav.isVROk = true;
                    }

                    _showInfo = "Select " + _hit.collider.gameObject.name;
                    _isShow = true;
                }
                else
                {
                    Debug.DrawLine(transform.position,
                        new Vector3(transform.position.x + float.MaxValue * transform.forward.x,
                            transform.position.y + float.MaxValue * transform.forward.y,
                            transform.position.z + float.MaxValue * transform.forward.z), Color.blue);
                    DrawLineGame(transform.position,
                        new Vector3(transform.position.x + float.MaxValue * transform.forward.x,
                            transform.position.y + float.MaxValue * transform.forward.y,
                            transform.position.z + float.MaxValue * transform.forward.z), Color.blue);
                    isHitUav = false;
                    Uav.isVROk = false;
                }

                if (IsAutoPlotPath)
                {
                    _uavTrajectory.SetCurrentPosition(UavRb.position);
                    _uavTrajectory.DrawLine();
                }
               
            }
            else //Operator Planning Mode
            {
                if (IsAutoPlotPath)
                {
                    _operatorTrajectory.SetCurrentPosition(OperatorTransform.position);
                    _operatorTrajectory.DrawLine();
                }
            }

            if (OVRInput.GetDown(OVRInput.RawButton.RHandTrigger))
            {
                if (!IsAutoPlotPath)
                {
                    if (_modeId == 0)//Operator Planning Mode
                    {
                        _operatorTrajectory.SetCurrentPosition(OperatorTransform.position);
                        _operatorTrajectory.DrawLine();
                    }
                    else if (_modeId == 1) //UAV Planning Mode
                    {
                        _uavTrajectory.SetCurrentPosition(UavRb.position);
                        _uavTrajectory.DrawLine();
                    }
                }
               
            }

            UavInfo.text = _showInfo;
        }

        [System.Obsolete]
        void DrawLineGame(Vector3 start, Vector3 end, Color color, float duration = 0.2f)
        {
            if (myLine == null)
            {
                myLine = new GameObject();
                myLine.AddComponent<LineRenderer>();
            }

            myLine.transform.position = start;
            LineRenderer lr = myLine.GetComponent<LineRenderer>();
            lr.SetColors(color, color);
            lr.SetWidth(0.01f, 0.01f);
            lr.SetPosition(0, start);
            lr.SetPosition(1, end);
        }

        /*
        void OnGUI()
        {
            if (_isShow)
            {
                if (_showTime < 10)
                {
                    GUILayout.Label(_showInfo);
                    _showTime++;
                }
                else
                {
                    _showTime = 0;
                    _isShow = false;
                }
            }
        }
        */

    }
}
