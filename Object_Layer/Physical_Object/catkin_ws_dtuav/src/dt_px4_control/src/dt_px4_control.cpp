#include "../include/dt_px4_control/dt_px4_control.h"
using namespace std;
dt_px4_control::dt_px4_control()
{
  ros::NodeHandle n("~");
  n.getParam("rc_sub_topic",_rc_sub_topic);
  n.getParam("local_pose_sub_topic",_local_pose_sub_topic);
  n.getParam("global_position_sub_topic",_global_position_sub_topic);
  n.getParam("target_velocity_pub_topic",_target_velocity_pub_topic);
  n.getParam("target_local_position_pub_topic",_target_local_position_pub_topic);
  n.getParam("target_global_position_pub_topic",_target_global_position_pub_topic);
  n.getParam("velocity_cmd_sub_topic",_velocity_cmd_sub_topic);
  n.getParam("local_position_cmd_sub_topic",_local_position_cmd_sub_topic);
  n.getParam("global_position_cmd_sub_topic",_global_position_cmd_sub_topic);
  n.getParam("control_start_type",_control_start_type);
  n.getParam("start_type",_start_type);
  n.getParam("rc_ref_cmd_channel",_rc_ref_cmd_channel);
  n.getParam("rc_ref_cmd_way",_rc_ref_cmd_way);
  n.getParam("rc_land_channel",_rc_land_channel);
  n.getParam("px4_state_msg_sub_topic",_px4_state_msg_sub_topic);
  n.getParam("px4_arming_client_topic",_px4_arming_client_topic);
  n.getParam("px4_set_mode_client_topic",_px4_set_mode_client_topic);
  n.getParam("run_frequency_hz",_run_frequency_hz);

  n.getParam("change_control_type_sub_topic",_change_control_type_sub_topic);

  n.getParam("is_use_gps",_is_use_gps);

  _rc_sub = n.subscribe(_rc_sub_topic,1,&dt_px4_control::rc_sub_cb,this);
  _local_pose_sub = n.subscribe(_local_pose_sub_topic,1,&dt_px4_control::local_pose_sub_cb,this);
  _global_position_sub = n.subscribe(_global_position_sub_topic,1,&dt_px4_control::global_position_sub_cb,this);
  _velocity_cmd_sub = n.subscribe(_velocity_cmd_sub_topic,1,&dt_px4_control::velocity_cmd_sub_cb,this);
  _local_position_cmd_sub = n.subscribe(_local_position_cmd_sub_topic,1,&dt_px4_control::local_position_cmd_sub_cb,this);
  _global_position_cmd_sub = n.subscribe(_global_position_cmd_sub_topic,1,&dt_px4_control::global_position_cmd_sub_cb,this);
  _px4_state_msg_sub = n.subscribe(_px4_state_msg_sub_topic,1,&dt_px4_control::px4_state_msg_sub_cb,this);
  _change_control_type_sub = n.subscribe(_change_control_type_sub_topic,1,&dt_px4_control::change_control_type_sub_cb,this);

  _target_velocity_pub = n.advertise<geometry_msgs::Twist>(_target_velocity_pub_topic,1);
  _target_local_position_pub = n.advertise<geometry_msgs::PoseStamped>(_target_local_position_pub_topic,1);
  _target_global_position_pub = n.advertise<mavros_msgs::GlobalPositionTarget>(_target_global_position_pub_topic,1);

  _ref_local_position_x = 0;
  _ref_local_position_y = 0;
  _ref_local_position_z = -50;

  _ref_rotation_x = 0;
  _ref_rotation_y = 0;
  _ref_rotation_z = 0;
  _ref_rotation_w = 1;

  _ref_velocity_x = 0;
  _ref_velocity_y = 0;
  _ref_velocity_z = 0;

  _change_flag = 0;
  _model_change_flag = 0;
  _control_type = 0;
  _is_land = false;
  _is_fist_run = true;
  _is_get_global_pos = false;

  _is_start_uav = false;

  _is_get_init_rotation = false;
  _is_init_home_local_position = false;

  _px4_arming_client = n.serviceClient<mavros_msgs::CommandBool>(_px4_arming_client_topic);
  _px4_set_mode_client = n.serviceClient<mavros_msgs::SetMode>(_px4_set_mode_client_topic);
  ros::Rate rate(20.0);

  geometry_msgs::Twist px4_ref_vel;
  px4_ref_vel.linear.x = 0;
  px4_ref_vel.linear.y = 0;
  px4_ref_vel.linear.z = 0;
  // wait for FCU connection
  while(ros::ok() && !_px4_current_state.connected)
  {
    ros::spinOnce();
    rate.sleep();
  }
  for(int i = 10; ros::ok() && i > 0; --i)
  {
    _target_velocity_pub.publish(px4_ref_vel);
    ros::spinOnce();
    rate.sleep();
  }

  int flag_thread = pthread_create(&_run_thread,NULL,&dt_px4_control::run,this);
  if (flag_thread < 0) {
    ROS_ERROR("pthread_create ros_process_thread failed: %d\n", flag_thread);
  }

}

void dt_px4_control::change_control_type_sub_cb(const std_msgs::Int8ConstPtr &msg)
{
  if(msg.get()->data != _control_type)
  {
    switch (msg.get()->data) {
    case 0:
     {
      geometry_msgs::Twist velocity_msg;
      velocity_msg.linear.x = 0;
      velocity_msg.linear.y = 0;
      velocity_msg.linear.z = 0;
      _target_velocity_pub.publish(velocity_msg);
      _control_type = msg.get()->data;
    }
      break;
    case 1:
    {
      geometry_msgs::PoseStamped pose_msg;
      pose_msg.pose.orientation.x = _ref_rotation_x;
      pose_msg.pose.orientation.y = _ref_rotation_y;
      pose_msg.pose.orientation.z = _ref_rotation_z;
      pose_msg.pose.orientation.w = _ref_rotation_w;

      pose_msg.pose.position.x = _ref_local_position_x;
      pose_msg.pose.position.y = _ref_local_position_y;
      pose_msg.pose.position.z = _ref_local_position_z;
      _target_local_position_pub.publish(pose_msg);
      _control_type = msg.get()->data;
    }
      break;
    case 2:
    {
      mavros_msgs::GlobalPositionTarget targetPos;
      targetPos.coordinate_frame = 5;
      targetPos.type_mask = 8+16+32+64+128+256+512+1024+2048;
      targetPos.altitude = _cur_altitude;
      targetPos.longitude = _cur_longitude;
      targetPos.latitude = _cur_latitude;
      if(_is_use_gps)
      {
        _target_global_position_pub.publish(targetPos);
        _control_type = msg.get()->data;
      }
      else
      {
        ROS_INFO("ERROR Target Global Position Command, No Use GPS !!! Change Control Way Fail !!!");
      }
    }
      break;

    default:
      break;
    }
  }
}

void dt_px4_control::px4_state_msg_sub_cb(const mavros_msgs::StateConstPtr &msg)
{
  _px4_current_state = *msg;
}
void dt_px4_control::global_position_cmd_sub_cb(const mavros_msgs::GlobalPositionTargetConstPtr &msg)
{
  if(_control_type == 3&&(!_is_land))
  {
    _ref_altitude = msg.get()->altitude;
    _ref_latitude = msg.get()->latitude;
    _ref_longitude = msg.get()->latitude;
    std::cout<<"other_control_global_position = "<<_ref_longitude<<","<<_ref_latitude<<","<<_ref_altitude<<std::endl;
  }
}

void dt_px4_control::local_position_cmd_sub_cb(const geometry_msgs::PoseStamped::ConstPtr &msg)
{

  if(_control_type == 2&&(!_is_land))
  {
    _ref_local_position_x = msg.get()->pose.position.x;
    _ref_local_position_y = msg.get()->pose.position.y;
    _ref_local_position_z = msg.get()->pose.position.z;

    // ref_position_x = msg.get()->pose.position.x + homeLocalPosition_x;
    // ref_position_y = msg.get()->pose.position.y + homeLocalPosition_y;
    // ref_position_z = msg.get()->pose.position.z + homeLocalPosition_z;

    std::cout<<"other_control_position = "<<_ref_local_position_x<<","<<_ref_local_position_y<<","<<_ref_local_position_z<<std::endl;
  }
}

void dt_px4_control::velocity_cmd_sub_cb(const geometry_msgs::TwistStamped::ConstPtr &msg)
{

  if(_control_type == 1&&(!_is_land))
  {
    _ref_velocity_x = msg.get()->twist.linear.x;
    _ref_velocity_y = msg.get()->twist.linear.y;
    _ref_velocity_z = msg.get()->twist.linear.z;
    std::cout<<"other_control_velocity = "<<_ref_velocity_x<<","<<_ref_velocity_y<<","<<_ref_velocity_z<<std::endl;
  }

}

void *dt_px4_control::run(void *args)
{
  dt_px4_control* vecct = (dt_px4_control*)(args);
  geometry_msgs::Twist vel;
  vel.linear.x = 0;
  vel.linear.y = 0;
  vel.linear.z = 0;
  vel.angular.z = 0;
  vel.angular.x = 0;
  vel.angular.y = 0;
  vecct->_target_velocity_pub.publish(vel);
  geometry_msgs::PoseStamped pos;
  pos.header.frame_id = "uav";
  pos.header.stamp = ros::Time::now();
  pos.pose.position.x = vecct->_ref_local_position_x;
  pos.pose.position.y = vecct->_ref_local_position_y;
  pos.pose.position.z = vecct->_ref_local_position_z;
  // pos.pose.orientation.x = 0;
  // pos.pose.orientation.y = 0;
  // pos.pose.orientation.z = -0.999880201542;
  // pos.pose.orientation.z = 0;
  // pos.pose.orientation.w = -0.0148436985771;
  // pos.pose.orientation.w = -1;
  mavros_msgs::GlobalPositionTarget targetPos;
  targetPos.coordinate_frame = 5;
  targetPos.type_mask = 8+16+32+64+128+256+512+1024+2048;
  ros::Rate rate(vecct->_run_frequency_hz);
  while(ros::ok())
  {
    if(vecct->_is_start_uav)
    {
      if(vecct->_control_start_type == 0)
      {
        if( !vecct->_px4_current_state.armed)
        {
          if( vecct->_px4_arming_client.call(vecct->_px4_arming) &&
              vecct->_px4_arming.response.success)
          {
            ROS_INFO("Vehicle armed");
          }
        }
        else
        {
          if( vecct->_px4_current_state.mode != "OFFBOARD")
          {
            if( vecct->_px4_set_mode_client.call(vecct->_px4_set_mode) &&
                vecct->_px4_set_mode.response.mode_sent)
            {
              ROS_INFO("Offboard enabled");
            }
          }
        }
      }
      else if(vecct->_control_start_type == 1)
      {
        if(vecct->_px4_current_state.armed)
        {
          if( vecct->_px4_current_state.mode != "OFFBOARD")
          {
            if( vecct->_px4_set_mode_client.call(vecct->_px4_set_mode) &&
                vecct->_px4_set_mode.response.mode_sent)
            {
              ROS_INFO("Offboard enabled");
            }
          }
        }
        else
        {
          ROS_INFO("Arm Manual Firstly!!!");
        }
      }
      else if(vecct->_control_start_type ==2)
      {
        if( !vecct->_px4_current_state.armed)
        {
          if( vecct->_px4_arming_client.call(vecct->_px4_arming) &&
              vecct->_px4_arming.response.success)
          {
            ROS_INFO("Vehicle armed, Offboard Enabled Secondly!!!");
          }
        }
      }
      else
      {
        // Manual Enable Offboard && Manual Arm
      }


      if(!vecct->_is_fist_run)
      {
        if(vecct->_control_type == 0||vecct->_control_type == 1)
        {
          vel.linear.x = vecct->_ref_velocity_x;
          vel.linear.y = vecct->_ref_velocity_y;
          vel.linear.z = vecct->_ref_velocity_z;
          vecct->_target_velocity_pub.publish(vel);
          rate.sleep();
        }
        else if(vecct->_control_type == 2)
        {
          if(vecct->_is_get_init_rotation)
          {
            pos.header.stamp = ros::Time::now();
            pos.pose.position.x = vecct->_ref_local_position_x;
            pos.pose.position.y = vecct->_ref_local_position_y;
            pos.pose.position.z = vecct->_ref_local_position_z;
            pos.pose.orientation.x = vecct->_ref_rotation_x;
            pos.pose.orientation.y = vecct->_ref_rotation_y;
            pos.pose.orientation.z = vecct->_ref_rotation_z;
            pos.pose.orientation.w = vecct->_ref_rotation_w;
            vecct->_target_local_position_pub.publish(pos);
            rate.sleep();
          }
          else
          {
            ROS_INFO("Wait Local Rotation ...");
          }

        }
        else if(vecct->_control_type == 3)
        {
          targetPos.header.stamp = ros::Time::now();
          targetPos.altitude = vecct->_ref_altitude;
          targetPos.longitude = vecct->_ref_longitude;
          targetPos.latitude = vecct->_ref_latitude;
          if(vecct->_is_use_gps)
          {
            vecct->_target_global_position_pub.publish(targetPos);
          }
          else
          {
            ROS_INFO("ERROR Target Global Position Command, No Use GPS !!!");
          }
          rate.sleep();
        }
      }
      else
      {
        if(vecct->_is_use_gps)
        {
          if(!vecct->_is_get_global_pos)
          {
            ROS_INFO("Wait GPS Data...");
          }
          else
          {
            ROS_INFO("Get GPS Home Global Position");
            std::cout<<"GPS Home Global Position (longitude,latitude,altitude): "<<"( "<<vecct->_home_longitude<<", "<<vecct->_home_latitude<<", "<<vecct->_home_altitude<<" )"<<std::endl;
            vecct->_ref_altitude = vecct->_home_altitude;
            vecct->_ref_latitude = vecct->_home_latitude;
            vecct->_ref_longitude = vecct->_home_longitude;
            vecct->_is_fist_run = false;
          }
        }
        else
        {
          vecct->_is_fist_run = false;
        }
      }

    }
  }
  pthread_join(vecct->_run_thread,NULL);

}

void dt_px4_control::rc_sub_cb(const mavros_msgs::RCInConstPtr &msg)
{
  if(_start_type == 0)
  {
    if(_control_type == 0)
    {
      if(msg.get()->channels[_rc_ref_cmd_channel]>1000&&msg.get()->channels[_rc_ref_cmd_channel]<1400&&_change_flag == 0)
      {
        _ref_velocity_z = 0.0f;
        _ref_velocity_x = 0.0f;
        _ref_velocity_y = 0.0f;
        _change_flag = 1;
        std::cout<<"rc_control_velocity = (0.0,0.0,0.0)"<<std::endl;
      }
      if(msg.get()->channels[_rc_ref_cmd_channel]>1400&&msg.get()->channels[_rc_ref_cmd_channel]<1800&&_change_flag == 1)
      {
        _ref_velocity_z = 0.6f;
        _ref_velocity_x = 0.0f;
        _ref_velocity_y = 0.0f;
        _change_flag = 2;
        std::cout<<"rc_control_velocity = (0.0,0.0,0.6)"<<std::endl;
      }
      if(msg.get()->channels[_rc_ref_cmd_channel]>1800&&msg.get()->channels[_rc_ref_cmd_channel]<2000&&_change_flag == 2)
      {
        _ref_velocity_x = 0.0f;
        _ref_velocity_y = 0.3f;
        _ref_velocity_z = 0;
        _change_flag = 4;
        std::cout<<"rc_control_velocity = (0.0,0.3,0.0)"<<std::endl;
      }
      if(msg.get()->channels[_rc_ref_cmd_channel]>1400&&msg.get()->channels[_rc_ref_cmd_channel]<1800&&_change_flag == 4)
      {
        _ref_velocity_x = 0.3f;
        _ref_velocity_y = 0.0f;
        _ref_velocity_z = 0.0;
        _change_flag = 5;
        std::cout<<"rc_control_velocity = (0.3,0.0,0.0)"<<std::endl;
      }

      if(msg.get()->channels[_rc_ref_cmd_channel]>1000&&msg.get()->channels[_rc_ref_cmd_channel]<1400&&_change_flag == 5)
      {
        _ref_velocity_x = 0.0f;
        _ref_velocity_y = 0.0f;
        _ref_velocity_z = -0.3;
        _change_flag = 6;
        std::cout<<"rc_control_velocity = (0.0,0.0,-0.3)"<<std::endl;
      }
    }

    if(msg.get()->channels[_rc_ref_cmd_channel]>1800&&msg.get()->channels[_rc_ref_cmd_channel]<2000)
    {
      _is_land = true;
      if(_control_type == 2)
      {
        _ref_local_position_z = -50;
        std::cout<<"land_control_position: "<<_ref_local_position_x<<" ,"<<_ref_local_position_y<<" ,"<<_ref_local_position_z<<std::endl;
      }
      else if(_control_type == 1 ||_control_type == 0 )
      {
        _ref_velocity_x = 0.0f;
        _ref_velocity_y = 0.0f;
        _ref_velocity_z = -0.3;
        std::cout<<"land_control_velocity = (0.0,0.0,-0.3)"<<std::endl;
      }
      else if(_control_type == 3)
      {
        _ref_altitude = -50;
        std::cout<<"land_control_global_position = (0.0,0.0,-50)"<<std::endl;
      }

    }
    if(msg.get()->channels[_rc_ref_cmd_channel]>1000&&msg.get()->channels[_rc_ref_cmd_channel]<1400&&_model_change_flag==0)
    {
      _control_type = 0;
      _model_change_flag = 1;
      ROS_INFO("Current Control Model Is Velocity By RC");
    }
    if(msg.get()->channels[_rc_ref_cmd_channel]>1400&&msg.get()->channels[_rc_ref_cmd_channel]<1800&&_model_change_flag==1)
    {
      _control_type = 1;
      _model_change_flag = 2;
      ROS_INFO("Current Control Model Is Velocity By Others");
    }
    if(msg.get()->channels[_rc_ref_cmd_channel]>1800&&msg.get()->channels[_rc_ref_cmd_channel]<2000&&_model_change_flag==2)
    {
      _control_type = 2;
      _model_change_flag = 3;
      _is_get_home_local_position = true;
      ROS_INFO("Current Control Model Is Local Position By Others");
    }
    if(msg.get()->channels[_rc_ref_cmd_channel]>1400&&msg.get()->channels[_rc_ref_cmd_channel]<1800&&_model_change_flag==3)
    {
      _control_type = 3;
      _model_change_flag = 4;
      ROS_INFO("Current Control Model Is Global Position By Others");
    }
    if(msg.get()->channels[_rc_ref_cmd_channel]>1000&&msg.get()->channels[_rc_ref_cmd_channel]<1400&&_model_change_flag==4)
    {
      _model_change_flag = 0;
    }
  }
}
void dt_px4_control::global_position_sub_cb(const sensor_msgs::NavSatFixConstPtr &msg)
{
  //std::cout<<"dddddd"<<std::endl;
  if(!_is_get_global_pos&&msg.get()->status.status == msg.get()->status.STATUS_FIX)
  {
    _home_altitude = msg.get()->altitude;
    _home_latitude = msg.get()->latitude;
    _home_longitude = msg.get()->longitude;
    _is_get_global_pos = true;
  }
  else
  {
    if(msg.get()->status.status == msg.get()->status.STATUS_FIX)
    {
      _cur_altitude = msg.get()->altitude;
      _cur_latitude = msg.get()->latitude;
      _cur_longitude = msg.get()->longitude;
    }

  }

}

void dt_px4_control::local_pose_sub_cb(const geometry_msgs::PoseStampedConstPtr &msg)
{
  if(!_is_get_init_rotation)
  {
    _ref_rotation_x = msg.get()->pose.orientation.x;
    _ref_rotation_y = msg.get()->pose.orientation.y;
    _ref_rotation_z = msg.get()->pose.orientation.z;
    _ref_rotation_w = msg.get()->pose.orientation.w;
    _is_get_init_rotation = true;
    ROS_INFO("Get the Local Rotation...");
  }
  else
  {
    _cur_local_position_x = msg.get()->pose.position.x;
    _cur_local_position_y = msg.get()->pose.position.y;
    _cur_local_position_z = msg.get()->pose.position.z;
  }
  /*
  if(is_getHomeLocalPosition&&!is_initHomeLocalPosition)
  {
    homeLocalPosition_x = msg.get()->pose.position.x;
    homeLocalPosition_y = msg.get()->pose.position.y;
    homeLocalPosition_z = msg.get()->pose.position.z;
    ROS_INFO("Init Local Position...");
    is_initHomeLocalPosition = true;
  }
  */
}

















