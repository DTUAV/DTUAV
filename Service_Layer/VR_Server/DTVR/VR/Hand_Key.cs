using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class Hand_Key : MonoBehaviour
{
    public bool isCenterHit_rightHand = false;

    public bool isSideHit_rightHand = false;

    public bool isAHit_rightHand = false;

    public bool isBHit_rightHand = false;
    // Start is called before the first frame update
    void Start()
    {
        
    }

    // Update is called once per frame
    void Update()
    {
        
        if (OVRInput.GetDown(OVRInput.RawButton.A))
        {
            Debug.Log("XBOX-----A");
        }

        if (OVRInput.GetDown(OVRInput.RawButton.B))
        {
            Debug.Log("XBOX-----B");
        }

        if (OVRInput.GetDown(OVRInput.RawButton.X))
        {
            Debug.Log("XBOX-----X");
        }

        if (OVRInput.GetDown(OVRInput.RawButton.Y))
        {
            Debug.Log("XBOX-----Y");
        }

        if (OVRInput.GetDown(OVRInput.RawButton.DpadDown))
        {
            Debug.Log("OVRInput.RawButton.DpadDown");
        }
        if (OVRInput.GetDown(OVRInput.RawButton.DpadLeft))
        {
            Debug.Log("OVRInput.RawButton.DpadLeft");
        }
        if (OVRInput.GetDown(OVRInput.RawButton.DpadRight))
        {
            Debug.Log("OVRInput.RawButton.DpadRight");
        }
        if (OVRInput.GetDown(OVRInput.RawButton.DpadUp))
        {
            Debug.Log("OVRInput.RawButton.DpadUp");
        }

       
        if (OVRInput.GetDown(OVRInput.RawButton.LShoulder))
        {
            Debug.Log("OVRInput.RawButton.LShoulder");
        }

        if (OVRInput.GetDown(OVRInput.RawButton.RShoulder))
        {
            Debug.Log("OVRInput.RawButton.RShoulder");
        }


       
        if (OVRInput.GetDown(OVRInput.RawButton.Start))
        {
            Debug.Log("start");
        }

        if (OVRInput.GetDown(OVRInput.RawButton.Back))
        {
            Debug.Log("Back");
        }


        
        if (OVRInput.GetDown(OVRInput.RawButton.LThumbstickDown))
        {
            Debug.Log("LThumbstickDown");
        }
        if (OVRInput.GetDown(OVRInput.RawButton.LThumbstickLeft))
        {
            Debug.Log("LThumbstickLeft");
        }

        if (OVRInput.GetDown(OVRInput.RawButton.LThumbstickRight))
        {
            Debug.Log("LThumbstickRight");
        }
        if (OVRInput.GetDown(OVRInput.RawButton.LThumbstickUp))
        {
            Debug.Log("LThumbstickUp");
        }
        if (OVRInput.GetDown(OVRInput.RawButton.LThumbstick))
        {
            Debug.Log("LThumbstick");
        }

        if (OVRInput.GetDown(OVRInput.RawButton.Any))
        {
            Debug.Log("Any");
        }
        if (OVRInput.GetDown(OVRInput.RawButton.LHandTrigger))
        {
            Debug.Log("LHandTrigger");
        }
        if (OVRInput.GetDown(OVRInput.RawButton.RHandTrigger))
        {
            Debug.Log("RHandTrigger");
        }
        if (OVRInput.GetDown(OVRInput.RawButton.LIndexTrigger))
        {
            Debug.Log("LIndexTrigger");
        }
        if (OVRInput.GetDown(OVRInput.RawButton.RIndexTrigger))
        {
            Debug.Log("RIndexTrigger");
        }
        if (OVRInput.GetDown(OVRInput.RawButton.RThumbstickDown))
        {
            Debug.Log("RThumbstickDown");
        }
        if (OVRInput.GetDown(OVRInput.RawButton.RThumbstickLeft))
        {
            Debug.Log("RThumbstickLeft");
        }
        if (OVRInput.GetDown(OVRInput.RawButton.RThumbstickRight))
        {
            Debug.Log("RThumbstickRight");
        }
        if (OVRInput.GetDown(OVRInput.RawButton.RThumbstickUp))
        {
            Debug.Log("RThumbstickUp");
        }
        if (OVRInput.GetDown(OVRInput.RawButton.RThumbstick))
        {
            Debug.Log("RThumbstick");
        }

        if (OVRInput.GetDown(OVRInput.RawButton.LIndexTrigger))
        {
            Debug.Log("OVRInput.RawButton.LIndexTrigger");
        }
        if (OVRInput.GetDown(OVRInput.RawButton.RIndexTrigger))
        {
            Debug.Log("OVRInput.RawButton.RIndexTrigger");
        }
    }
}
