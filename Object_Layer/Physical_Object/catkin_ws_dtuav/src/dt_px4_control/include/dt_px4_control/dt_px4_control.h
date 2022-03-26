#ifndef DT_PX4_CONTROL_H
#define DT_PX4_CONTROL_H
#include "iostream"
#include "ros/ros.h"
#include "mavros_msgs/GlobalPositionTarget.h"
#include "geometry_msgs/PoseStamped.h"
#include "mavros_msgs/RCIn.h"
#include "geometry_msgs/TwistStamped.h"
#include "ros/time.h"
#include "pthread.h"
#include "sensor_msgs/NavSatFix.h"
#include "mavros_msgs/State.h"
#include <mavros_msgs/CommandBool.h>
#include <mavros_msgs/SetMode.h>
#include <std_msgs/Bool.h>
#include <std_msgs/Int8.h>

class dt_px4_control
{
public:
  dt_px4_control();

  static void *run(void *args);
  void rc_sub_cb(const mavros_msgs::RCInConstPtr& msg);
  void velocity_cmd_sub_cb(const geometry_msgs::TwistStamped::ConstPtr& msg);
  void local_position_cmd_sub_cb(const geometry_msgs::PoseStamped::ConstPtr& msg);
  void global_position_cmd_sub_cb(const mavros_msgs::GlobalPositionTargetConstPtr& msg);
  void local_pose_sub_cb(const geometry_msgs::PoseStampedConstPtr& msg);
  void global_position_sub_cb(const sensor_msgs::NavSatFixConstPtr& msg);
  void px4_state_msg_sub_cb(const mavros_msgs::StateConstPtr& msg);
  void change_control_type_sub_cb(const std_msgs::Int8ConstPtr& msg);
private:
  std::string _rc_sub_topic;
  std::string _local_pose_sub_topic;
  std::string _global_position_sub_topic;
  std::string _target_velocity_pub_topic;
  std::string _target_local_position_pub_topic;
  std::string _target_global_position_pub_topic;

  std::string _velocity_cmd_sub_topic;
  std::string _local_position_cmd_sub_topic;
  std::string _global_position_cmd_sub_topic;


  std::string _px4_state_msg_sub_topic;//The Message from PX4--about the current state of px4
  std::string _px4_arming_client_topic;//The Client Message to PX4 -- arm the vehicle
  std::string _px4_set_mode_client_topic;//The Client Message to PX4 -- set the vehicle mode to offboard control


  std::string _change_control_type_sub_topic;


  int _control_start_type;
  int _start_type;


  int _rc_ref_cmd_channel;
  int _rc_land_channel;
  int _rc_ref_cmd_way;

  ros::Subscriber _rc_sub;
  ros::Subscriber _local_pose_sub;
  ros::Subscriber _global_position_sub;
  ros::Subscriber _velocity_cmd_sub;
  ros::Subscriber _local_position_cmd_sub;
  ros::Subscriber _global_position_cmd_sub;
  ros::Subscriber _change_control_type_sub;

  ros::Subscriber _px4_state_msg_sub;//The Subscriber for Subscribe PX4 State

  ros::ServiceClient _px4_arming_client;//The ServiceClient to Arm the Vehecle
  ros::ServiceClient _px4_set_mode_client;//The ServiceClient to Set the Offboard Control Mode to Vehecle


  int _control_type;//0:Velocity Control 1:Local Position Control 2:Global Position Control
  bool _is_land;

  ros::Publisher _target_velocity_pub;
  ros::Publisher _target_local_position_pub;
  ros::Publisher _target_global_position_pub;

  float _ref_velocity_x;
  float _ref_velocity_y;
  float _ref_velocity_z;

  float _ref_rotation_x;
  float _ref_rotation_y;
  float _ref_rotation_z;
  float _ref_rotation_w;

  bool _is_get_init_rotation;

  float _ref_local_position_x;
  float _ref_local_position_y;
  float _ref_local_position_z;

  float _cur_local_position_x;
  float _cur_local_position_y;
  float _cur_local_position_z;

  float _cur_latitude;
  float _cur_longitude;
  float _cur_altitude;

  bool _is_get_home_local_position;
  bool _is_init_home_local_position;
  float _home_local_position_x;
  float _home_local_position_y;
  float _home_local_position_z;

  double _ref_latitude;
  double _ref_longitude;
  double _ref_altitude;

  int _change_flag;
  int _model_change_flag;

  double _home_latitude;
  double _home_longitude;
  double _home_altitude;
  bool _is_get_global_pos;
  bool _is_use_gps;

  bool _is_fist_run;
  bool _is_start_uav;

  mavros_msgs::State _px4_current_state;
  mavros_msgs::SetMode _px4_set_mode;
  mavros_msgs::CommandBool _px4_arming;


  pthread_t _run_thread;
  float _run_frequency_hz;
};

#endif // DT_PX4_CONTROL_H
