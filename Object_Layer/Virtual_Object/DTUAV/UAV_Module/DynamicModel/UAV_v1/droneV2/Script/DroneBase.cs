using System.Collections;
using System.Collections.Generic;
using UnityEngine;

namespace DTUAV.UAV_Module.droneV2
{
    public class DroneBase : MonoBehaviour
    {
        public GameObject droneV2;
        public GameObject propellorBR;
        public GameObject propellorBL;
        public GameObject propellorFR;
        public GameObject propellorFL;

        public GameObject camera_sensor;


        public float thrust_min = 0; //最小的油门
        public float thrust_max = 2; //最大的油门
        public float thrust_current; //当前的油门

        public float roll_min = -15; //限定最小的滚转角
        public float roll_max = 15; //限定最大的滚转角
        public float roll_current; //当前滚转角

        public float pitch_min = -15; //限定最小的俯仰角
        public float pitch_max = 15; //限定最大的俯仰角
        public float pitch_current; //当前俯仰角

        public Vector3 current_position; //当前的无人机位置
        public Vector3 current_rotation; //当前的无人机姿态角

        public float current_yaw; //当前的无人机偏航角
        public Vector3 ref_position; //指定的无人机位置
        public float ref_yaw; //指定无人机的偏航角；
        public float ref_step_move = 3; //指定无人机单次最大的移动距离

        public Vector3 ref_camera_rotation; //指定相机的旋转
        private Rigidbody droneV2Rb;
        public float speed_k = 4.4f;

        bool init_object()
        {
            if (droneV2 == null || propellorBL == null || propellorBR == null || propellorFL == null ||
                propellorFR == null)
            {
                Debug.Log("对象未初始化");
                return false;
            }
            else
            {
                return true;
            }
        }

        float update_roll()
        {
            //X-->roll-->rotation.z
            /*
             * Xd > X， roll<0;
             * 
             */
            float need_roll;
            float roll_k = (roll_max / ref_step_move);
            float x_err = ref_position.x - current_position.x; //只使用比例调整
            need_roll = -x_err * roll_k;
            need_roll = Mathf.Clamp(need_roll, roll_min, roll_max);
            return need_roll;
        }


        float update_pitch()
        {
            //Y-->pitch-->rotation.x
            float need_pitch;
            float pitch_k = (pitch_max / ref_step_move);
            float z_err = ref_position.z - current_position.z;
            need_pitch = z_err * pitch_k;
            need_pitch = Mathf.Clamp(need_pitch, pitch_min, pitch_max);
            return need_pitch;

        }

        float update_thrust()
        {
            float need_thrust;
            if (ref_position.y >= current_position.y)
            {
                float thrust_k = (thrust_max / ref_step_move);
                float y_err = ref_position.y - current_position.y;
                need_thrust = y_err * thrust_k;
                need_thrust = Mathf.Clamp(need_thrust, thrust_min, thrust_max);

            }
            else
            {
                need_thrust = 0;
            }

            return need_thrust;
        }


        void init()
        {
            droneV2Rb = droneV2.GetComponent<Rigidbody>();
            current_position = droneV2Rb.position;
            current_rotation = droneV2Rb.rotation.eulerAngles;
            ref_position = current_position;

        }

        void updataState()
        {
            current_position = droneV2Rb.position;
            current_rotation = droneV2Rb.rotation.eulerAngles;
        }

        void updateBase()
        {
            updataState();
            float need_roll = update_roll();
            float need_pitch = update_pitch();
            float need_thrust = update_thrust();
            if (ref_position.y >= current_position.y)
            {
                need_thrust = need_thrust + droneV2Rb.mass * 9.81f;
                droneV2Rb.AddForce(transform.up * need_thrust);
            }

            
            Vector3 targetAngle = new Vector3(need_pitch, 0, need_roll);
            Vector3 currentAngle = current_rotation;

            currentAngle = new Vector3(
                Mathf.LerpAngle(currentAngle.x, targetAngle.x, UnityEngine.Time.fixedDeltaTime * speed_k),
                Mathf.LerpAngle(currentAngle.y, targetAngle.y, UnityEngine.Time.fixedDeltaTime * speed_k),
                Mathf.LerpAngle(currentAngle.z, targetAngle.z, UnityEngine.Time.fixedDeltaTime * speed_k)
            );

           
            droneV2.transform.eulerAngles = new Vector3(currentAngle.x, currentAngle.y, currentAngle.z);
            droneV2.transform.localEulerAngles = new Vector3(droneV2.transform.localEulerAngles.x, ref_yaw,
                droneV2.transform.localEulerAngles.z);
        }


        void Start()
        {
            if (init_object())
            {
                init();
            }


        }

        void FixedUpdate()
        {
            updateBase();
        }








        /*
    
    
        public float minThrust = 0; // The minimum thrust that can be applied.
        public float idleThrust = 122.5f; // The amount needed to make the drone hover.
        public float maxThrust = 250; // The maximum thrust that can be applied.
        public float rotateSpeed = 2.2f; // The speed in which the drone can rotate.
        public float tiltSpeed = 4.4f; // The speed in which the drone will try to bank and pitch.
        public float maxTilt = 65.0f; // The maximum angle in degrees that the drone may tilt to.
    
        private Rigidbody rb;
        private float thrust; // The level of thrust being applied to the drone.
        private bool hover = true; // The Drone will hover using the idleThrust variable.
        private bool flipLock = true; // If the drone should be allowed to flip, toggleable.
    
        private float angleBank; // The desired angle of the bank.
        private float anglePitch; // The desired angle of the pitch.
        private float angleYaw; // The desired angle of the yaw.
    
        void Start()
        {
            rb = GetComponent<Rigidbody>();
    
            // Need to set the angleYaw, otherwise it will "null out".
            angleYaw = 0;
        }
    
        void Update()
        {
            // Hover toggle.
            if (Input.GetKey(KeyCode.H))
                hover = hover == true ? false : true;
    
            // Flip toggle.
            if (Input.GetKey(KeyCode.F))
                flipLock = flipLock == true ? false : true;
    
            // Thrust control.
            if (Input.GetKey(KeyCode.W))
            {
                thrust = maxThrust;
                // hover = false;
            }
            else if (Input.GetKey(KeyCode.S))
            {
                thrust = minThrust;
                // hover = false;
            }
            else if (hover)
            {
                thrust = idleThrust;
            }
            else
            {
                thrust = 0;
            }
    
            // Angles for banking upon key press.
            if (Input.GetKey(KeyCode.LeftArrow))
                angleBank = -maxTilt;
            else if (Input.GetKey(KeyCode.RightArrow))
                angleBank = maxTilt;
            else
                angleBank = 0;
    
            // Angles for pitching upon key press.
            if (Input.GetKey(KeyCode.DownArrow))
                anglePitch = -maxTilt;
            else if (Input.GetKey(KeyCode.UpArrow))
                anglePitch = maxTilt;
            else
                anglePitch = 0;
    
            if (Input.GetKey(KeyCode.A))
                angleYaw -= rotateSpeed;
            else if (Input.GetKey(KeyCode.D))
                angleYaw += rotateSpeed;
        }
    
        // Any physics updates.
        void FixedUpdate()
        {
            // Apply thrust.
            rb.AddForce(transform.up * thrust * Time.deltaTime);
    
            // Tell the drone what angle we would like it to bank to.
            Vector3 targetAngle = new Vector3(angleBank, angleYaw, anglePitch);
            Vector3 currentAngle = transform.eulerAngles;
    
            // Set the rotation using Lerp. (No idea what it is, don't worry).
            currentAngle = new Vector3(
                Mathf.LerpAngle(currentAngle.x, targetAngle.x, Time.deltaTime * tiltSpeed),
                Mathf.LerpAngle(currentAngle.y, targetAngle.y, Time.deltaTime * tiltSpeed),
                Mathf.LerpAngle(currentAngle.z, targetAngle.z, Time.deltaTime * tiltSpeed)
            );
    
            // Set the rotation angle.
            transform.eulerAngles = currentAngle;
        }
        */
    }
}
