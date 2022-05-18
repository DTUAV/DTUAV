using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class move_uav : MonoBehaviour
{
    // Use this for initialization
   public bool isOk = false; 
   public bool isVROk = false;
   public float moveSpeed = 0.5f;
   public Transform VR_Hander_Right;
   private Vector3 hander_right_position_last;
   private Vector3 hander_right_position_current;
   private Vector3 uav_position_last;

    void Start()
    {
        // this.GetComponent<MeshRenderer>().material.color = Color.red;
       hander_right_position_last = VR_Hander_Right.transform.position;
       hander_right_position_current = VR_Hander_Right.transform.position;
       uav_position_last = transform.position;

    }

    // Update is called once per frame
    void Update()
    {
        
        if (Input.GetMouseButtonDown(0))
        {
            
            Ray ray = Camera.main.ScreenPointToRay(Input.mousePosition);
            RaycastHit hit;
            if (Physics.Raycast(ray, out hit))
            {
                Debug.Log(hit.transform.tag);
                
                if (hit.transform.tag == "uav")
                {
                    isOk = true;
                }
            }
        }
        
        if (Input.GetMouseButtonUp(0))
        {
            isOk = false;

        }

        if (isOk)
        {
            Vector3 targer = Camera.main.WorldToScreenPoint(this.transform.position);
            Vector3 mouse = Input.mousePosition;
            mouse.z = targer.z;
            Vector3 mouseScreenPos = Camera.main.ScreenToWorldPoint(mouse);
            this.transform.position = mouseScreenPos;
        }

        if (isVROk)
        {
            if (OVRInput.GetDown(OVRInput.RawButton.RThumbstickDown))
            {
                transform.position += Vector3.back * moveSpeed;
               
            }
            if (OVRInput.GetDown(OVRInput.RawButton.RThumbstickLeft))
            {
                transform.position += Vector3.left * moveSpeed;
            }
            if (OVRInput.GetDown(OVRInput.RawButton.RThumbstickRight))
            {
                transform.position += Vector3.right * moveSpeed ;
                //Debug.Log("ddddddddd");
            }
            if (OVRInput.GetDown(OVRInput.RawButton.RThumbstickUp))
            {
                transform.position += Vector3.forward* moveSpeed;
            }

            if (OVRInput.GetUp(OVRInput.RawButton.A))
            {
                transform.position += Vector3.up * moveSpeed;
            }

            if (OVRInput.GetUp(OVRInput.RawButton.B))
            {
                transform.position += Vector3.down * moveSpeed;
            }
        }

        /*
        if (isVROk)
        {
            hander_right_position_current = VR_Hander_Right.position;
            float distant_x = hander_right_position_current.x - hander_right_position_last.x;
            float distant_y = hander_right_position_current.y - hander_right_position_last.y;
            float distant_z = hander_right_position_current.z - hander_right_position_last.z;
            Vector3 target_position = new Vector3(distant_x,distant_y,distant_z)*10+uav_position_last;
            transform.position = target_position;
            uav_position_last = transform.position;
            hander_right_position_last = VR_Hander_Right.position;

        }
        else
        {
            hander_right_position_last = VR_Hander_Right.position;
            uav_position_last = transform.position;
        }
*/


    }

}
