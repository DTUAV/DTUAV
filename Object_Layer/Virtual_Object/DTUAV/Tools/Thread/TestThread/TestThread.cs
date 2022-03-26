using System.Collections;
using System.Collections.Generic;
using System.Threading;
using UnityEngine;

namespace DTUAV.Tools
{



    public class TestThread : MonoBehaviour
    {
        // Start is called before the first frame update
        public Transform ObjeTransform;
        public Vector3 localPosition;
        public bool isRun;
        void Start()
        {
            isRun = true;
           
            localPosition = new Vector3();
            Loom.RunAsync(
                () =>
                {
                    Thread thread = new Thread(Run);
                    thread.Start();
                }
            );


        }

        void Run()
        {
            while (isRun)
            {
                Loom.QueueOnMainThread(() => { localPosition = ObjeTransform.position; });
            }
           
        }

    }
}
