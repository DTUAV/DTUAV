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

public class MoveOperator : MonoBehaviour
{
    public Transform VrTransform;
    public float moveSpeed = 0.5f;
    // Update is called once per frame
    void Update()
    {
        if (OVRInput.GetDown(OVRInput.RawButton.DpadDown))
        {
            VrTransform.position += Vector3.back * moveSpeed;
        }
        if (OVRInput.GetDown(OVRInput.RawButton.DpadLeft))
        {
            VrTransform.position += Vector3.left * moveSpeed;
        }
        if (OVRInput.GetDown(OVRInput.RawButton.DpadRight))
        {
            VrTransform.position += Vector3.right * moveSpeed;
        }
        if (OVRInput.GetDown(OVRInput.RawButton.DpadUp))
        {
            VrTransform.position += Vector3.forward * moveSpeed;
        }
        if (OVRInput.GetDown(OVRInput.RawButton.X))
        {
            VrTransform.position += Vector3.up * moveSpeed;
        }

        if (OVRInput.GetDown(OVRInput.RawButton.Y))
        {
            VrTransform.position += Vector3.down * moveSpeed;
        }
    }
}
