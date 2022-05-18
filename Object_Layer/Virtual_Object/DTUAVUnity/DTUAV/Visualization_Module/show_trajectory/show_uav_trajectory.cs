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
