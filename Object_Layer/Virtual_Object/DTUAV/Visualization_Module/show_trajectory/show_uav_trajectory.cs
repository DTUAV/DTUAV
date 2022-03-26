/*
 * Author: Yuanlin Yang
 * Date: 2022-1-3
 * Location: Guangdong University of Technology
 */
using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using DTUAV.Visualization_Module;
public class show_uav_trajectory : MonoBehaviour
{
    private show_trajectory _showTrajectory;
    private Vector3 _lastPosition;

    public Rigidbody UavRb;

    public Material Mat;

    public Color LineColor;

    public float WidthX;

    public float WidthY;

    public bool IsPlot;

    public float Duration;
    // Start is called before the first frame update
    void Start()
    {
        _showTrajectory = new show_trajectory(Mat, LineColor, WidthX, WidthY, UavRb.position, IsPlot, Duration);
    }

    // Update is called once per frame
    [System.Obsolete]
    void Update()
    {
        _showTrajectory.SetCurrentPosition(UavRb.position);
        _showTrajectory.DrawLine();

    }
}
