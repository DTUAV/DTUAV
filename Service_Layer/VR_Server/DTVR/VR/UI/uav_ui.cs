using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using DigitalTwin.UavCarProject;
using DTUAV.TF;

public class uav_ui : MonoBehaviour
{
    public Transform MoveObject;
    private Vector3 _initPosition;
    private Vector3 _globalCurrentPosition;
    private Vector3 _refPosition;
    // Start is called before the first frame update
    void Start()
    {
        _initPosition = MoveObject.position;
        _globalCurrentPosition = MoveObject.position;
    }

    void OnGUI()
    {
        GUIStyle label_style1 = new GUIStyle();
        label_style1.normal.textColor = Color.red;

        _globalCurrentPosition = MoveObject.position;
        Vector3 localPosition = _globalCurrentPosition - _initPosition;
        _refPosition = TF.Unity2Ros(localPosition);
        GUILayout.BeginVertical();
        GUILayout.Label("ref_positon");
        GUILayout.Label("x: "+ _refPosition.x,label_style1);
        GUILayout.Label("y: " + _refPosition.y, label_style1);
        GUILayout.Label("z: " + _refPosition.z, label_style1);
        GUILayout.EndVertical();
    }
}
