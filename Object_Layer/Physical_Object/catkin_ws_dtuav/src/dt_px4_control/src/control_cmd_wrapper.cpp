#include "../include/dt_px4_control/control_cmd_wrapper.h"

control_cmd_wrapper::control_cmd_wrapper()
{
  ros::NodeHandle n("~");
  n.getParam("velocity_cmd_pub_topic",_velocity_cmd_pub_topic);
  n.getParam("local_position_cmd_pub_topic",_local_position_cmd_pub_topic);
  n.getParam("global_position_cmd_pub_topic",_global_position_cmd_pub_topic);

  n.getParam("cloud_server_local_position_sub_topic",_cloud_server_local_position_sub_topic);
  n.getParam("cloud_server_global_position_sub_topic",_cloud_server_global_position_sub_topic);
  n.getParam("cloud_server_velocity_sub_topic",_cloud_server_velocity_sub_topic);
  n.getParam("cloud_server_control_apply_sub_topic",_cloud_server_control_apply_sub_topic);
  n.getParam("cloud_server_target_cmd_type_sub_topic",_cloud_server_target_cmd_type_sub_topic);

  n.getParam("local_server_local_position_sub_topic",_local_server_local_position_sub_topic);
  n.getParam("local_server_global_position_sub_topic",_local_server_global_position_sub_topic);
  n.getParam("local_server_velocity_sub_topic",_local_server_velocity_sub_topic);
  n.getParam("local_server_control_apply_sub_topic",_local_server_control_apply_sub_topic);
  n.getParam("local_server_target_cmd_type_sub_topic",_local_server_target_cmd_type_sub_topic);

  n.getParam("vr_server_local_position_sub_topic",_vr_server_local_position_sub_topic);
  n.getParam("vr_server_global_position_sub_topic",_vr_server_global_position_sub_topic);
  n.getParam("vr_server_velocity_sub_topic",_vr_server_velocity_sub_topic);
  n.getParam("vr_server_control_apply_sub_topic",_vr_server_control_apply_sub_topic);
  n.getParam("vr_server_target_cmd_type_sub_topic",_vr_server_target_cmd_type_sub_topic);

  n.getParam("dt_object_local_position_sub_topic",_dt_object_local_position_sub_topic);
  n.getParam("dt_object_global_position_sub_topic",_dt_object_global_position_sub_topic);
  n.getParam("dt_object_velocity_sub_topic",_dt_object_velocity_sub_topic);
  n.getParam("dt_object_control_apply_sub_topic",_dt_object_control_apply_sub_topic);
  n.getParam("dt_object_target_cmd_type_sub_topic",_dt_object_target_cmd_type_sub_topic);

  n.getParam("local_machine_local_position_sub_topic",_local_machine_local_position_sub_topic);
  n.getParam("local_machine_global_position_sub_topic",_local_machine_global_position_sub_topic);
  n.getParam("local_machine_velocity_sub_topic",_local_machine_velocity_sub_topic);
  n.getParam("local_machine_control_apply_sub_topic",_local_machine_control_apply_sub_topic);
  n.getParam("local_machine_target_cmd_type_sub_topic",_local_machine_target_cmd_type_sub_topic);

  n.getParam("cur_control_type_pub_topic",_cur_control_type_pub_topic);
  n.getParam("control_type_pub_frequency",_control_type_pub_frequency);
  n.getParam("target_cmd_type_pub_topic",_target_cmd_type_pub_topic);

  _cloud_server_local_position_sub = n.subscribe(_cloud_server_local_position_sub_topic,1,&control_cmd_wrapper::cloud_server_local_position_sub_cb,this);
  _cloud_server_global_position_sub = n.subscribe(_cloud_server_global_position_sub_topic,1,&control_cmd_wrapper::cloud_server_global_position_sub_cb,this);
  _cloud_server_velocity_sub = n.subscribe(_cloud_server_velocity_sub_topic,1,&control_cmd_wrapper::cloud_server_velocity_sub_cb,this);
  _cloud_server_control_apply_sub = n.subscribe(_cloud_server_control_apply_sub_topic,1,&control_cmd_wrapper::cloud_server_control_apply_sub_cb,this);
  _cloud_server_target_cmd_type_sub = n.subscribe(_cloud_server_target_cmd_type_sub_topic,1,&control_cmd_wrapper::cloud_server_target_cmd_type_sub_cb,this);

  _local_server_local_position_sub = n.subscribe(_local_server_local_position_sub_topic,1,&control_cmd_wrapper::local_server_local_position_sub_cb,this);
  _local_server_global_position_sub = n.subscribe(_local_server_global_position_sub_topic,1,&control_cmd_wrapper::local_server_global_position_sub_cb,this);
  _local_server_velocity_sub = n.subscribe(_local_server_velocity_sub_topic,1,&control_cmd_wrapper::local_server_velocity_sub_cb,this);
  _local_server_control_apply_sub = n.subscribe(_local_server_control_apply_sub_topic,1,&control_cmd_wrapper::local_server_control_apply_sub_cb,this);
  _local_server_target_cmd_type_sub = n.subscribe(_local_server_target_cmd_type_sub_topic,1,&control_cmd_wrapper::local_server_target_cmd_type_sub_cb,this);

  _vr_server_local_position_sub = n.subscribe(_vr_server_local_position_sub_topic,1,&control_cmd_wrapper::vr_server_local_position_sub_cb,this);
  _vr_server_global_position_sub = n.subscribe(_vr_server_global_position_sub_topic,1,&control_cmd_wrapper::vr_server_global_position_sub_cb,this);
  _vr_server_velocity_sub = n.subscribe(_vr_server_velocity_sub_topic,1,&control_cmd_wrapper::vr_server_velocity_sub_cb,this);
  _vr_server_control_apply_sub = n.subscribe(_vr_server_control_apply_sub_topic,1,&control_cmd_wrapper::vr_server_control_apply_sub_cb,this);
  _vr_server_target_cmd_type_sub = n.subscribe(_vr_server_target_cmd_type_sub_topic,1,&control_cmd_wrapper::vr_server_target_cmd_type_sub_cb,this);


  _dt_object_local_position_sub = n.subscribe(_dt_object_local_position_sub_topic,1,&control_cmd_wrapper::dt_object_local_position_sub_cb,this);
  _dt_object_global_position_sub = n.subscribe(_dt_object_global_position_sub_topic,1,&control_cmd_wrapper::dt_object_global_position_sub_cb,this);
  _dt_object_velocity_sub = n.subscribe(_dt_object_velocity_sub_topic,1,&control_cmd_wrapper::dt_object_velocity_sub_cb,this);
  _dt_object_control_apply_sub = n.subscribe(_dt_object_control_apply_sub_topic,1,&control_cmd_wrapper::dt_object_control_apply_sub_cb,this);
  _dt_object_target_cmd_type_sub = n.subscribe(_dt_object_target_cmd_type_sub_topic,1,&control_cmd_wrapper::dt_object_target_cmd_type_sub_cb,this);

  _local_machine_local_position_sub = n.subscribe(_local_machine_local_position_sub_topic,1,&control_cmd_wrapper::local_machine_local_position_sub_cb,this);
  _local_machine_global_position_sub = n.subscribe(_local_machine_global_position_sub_topic,1,&control_cmd_wrapper::local_machine_global_position_sub_cb,this);
  _local_machine_velocity_sub = n.subscribe(_local_machine_velocity_sub_topic,1,&control_cmd_wrapper::local_machine_velocity_sub_cb,this);
  _local_machine_control_apply_sub = n.subscribe(_local_machine_control_apply_sub_topic,1,&control_cmd_wrapper::local_machine_control_apply_sub_cb,this);
  _local_machine_target_cmd_type_sub = n.subscribe(_local_machine_target_cmd_type_sub_topic,1,&control_cmd_wrapper::local_machine_target_cmd_type_sub_cb,this);


  _velocity_cmd_pub = n.advertise<geometry_msgs::TwistStamped>(_velocity_cmd_pub_topic,1);
  _local_position_cmd_pub = n.advertise<geometry_msgs::PoseStamped>(_local_position_cmd_pub_topic,1);
  _global_position_cmd_pub = n.advertise<mavros_msgs::GlobalPositionTarget>(_global_position_cmd_pub_topic,1);
  _cur_control_type_pub = n.advertise<std_msgs::Int8>(_cur_control_type_pub_topic,1);

  _target_cmd_type_pub = n.advertise<std_msgs::Int8>(_target_cmd_type_pub_topic,1);

  _cur_control_type = no_control_source;
  _cloud_server_target_cmd_type = 0;
  _local_server_target_cmd_type = 0;
  _vr_server_target_cmd_type = 0;
  _dt_object_target_cmd_type = 0;

  int flag_thread = pthread_create(&_run_thread,NULL,&control_cmd_wrapper::run,this);
  if (flag_thread < 0) {
    ROS_ERROR("pthread_create ros_process_thread failed: %d\n", flag_thread);
  }
}

void control_cmd_wrapper::update_control_type(int control_type,bool control_hold)
{
  if(control_hold)
  {
    if(_cur_control_type == no_control_source)
    {
      _cur_control_type = control_type;
    }
    else
    {
      if(_cur_control_type >= control_type)
      {
        _cur_control_type = control_type;
      }
    }
  }
  else
  {
    int temp_control_type = control_type;
    bool if_get_control_type = false;
    while(temp_control_type>=-1)
    {
      switch (temp_control_type) {
      case local_server:
      {
        if(_is_local_server_apply)
        {
          _cur_control_type = local_server;
          if_get_control_type = true;
        }
      }
        break;
      case vr_server:
      {
        if(_is_vr_server_apply)
        {
          _cur_control_type = vr_server;
          if_get_control_type = true;
        }
      }
        break;
      case cloud_server:
      {
        if(_is_cloud_server_apply)
        {
          _cur_control_type = cloud_server;
          if_get_control_type = true;
        }
      }
        break;
      case dt_object:
      {
        if(_is_dt_object_apply)
        {
          _cur_control_type = dt_object;
          if_get_control_type = true;
        }
      }
        break;
      case no_control_source:
      {
        _cur_control_type = no_control_source;
        if_get_control_type = true;
      }
      default:
        break;
      }

      temp_control_type--;
      if(if_get_control_type)
      {
        break;
      }
    }

  }

}

void control_cmd_wrapper::cloud_server_local_position_sub_cb(const geometry_msgs::PoseStampedConstPtr& msg)
{
  if(_cur_control_type == cloud_server&&_cloud_server_target_cmd_type==local_position_cmd)
  {
    geometry_msgs::PoseStamped local_position_msg;
    local_position_msg.pose.position.x = msg.get()->pose.position.x;
    local_position_msg.pose.position.y = msg.get()->pose.position.y;
    local_position_msg.pose.position.z = msg.get()->pose.position.z;
    _local_position_cmd_pub.publish(local_position_msg);
  }
}
void control_cmd_wrapper::cloud_server_global_position_sub_cb(const mavros_msgs::GlobalPositionTargetConstPtr& msg)
{
  if(_cur_control_type == cloud_server&&_cloud_server_target_cmd_type==global_position_cmd)
  {
    mavros_msgs::GlobalPositionTarget global_position_msg;
    global_position_msg.altitude = msg.get()->altitude;
    global_position_msg.latitude = msg.get()->latitude;
    global_position_msg.longitude = msg.get()->longitude;
    _global_position_cmd_pub.publish(global_position_msg);
  }
}
void control_cmd_wrapper::cloud_server_velocity_sub_cb(const geometry_msgs::TwistStampedConstPtr& msg)
{
  if(_cur_control_type == cloud_server&&_cloud_server_target_cmd_type==velocity_cmd)
  {
    geometry_msgs::TwistStamped velocity_msg;
    velocity_msg.twist.linear.x = msg.get()->twist.linear.x;
    velocity_msg.twist.linear.y = msg.get()->twist.linear.y;
    velocity_msg.twist.linear.z = msg.get()->twist.linear.z;
    _velocity_cmd_pub.publish(velocity_msg);
  }
}
void control_cmd_wrapper::cloud_server_control_apply_sub_cb(const std_msgs::BoolConstPtr& msg)
{
  _is_cloud_server_apply = msg.get()->data;
  update_control_type(cloud_server,_is_cloud_server_apply);

}
void control_cmd_wrapper::cloud_server_target_cmd_type_sub_cb(const std_msgs::Int8ConstPtr& msg)
{
  _cloud_server_target_cmd_type = msg.get()->data;
}

void control_cmd_wrapper::local_server_local_position_sub_cb(const geometry_msgs::PoseStampedConstPtr& msg)
{
  if(_cur_control_type == local_server&&_local_server_target_cmd_type==local_position_cmd)
  {
    geometry_msgs::PoseStamped local_position_msg;
    local_position_msg.pose.position.x = msg.get()->pose.position.x;
    local_position_msg.pose.position.y = msg.get()->pose.position.y;
    local_position_msg.pose.position.z = msg.get()->pose.position.z;
    _local_position_cmd_pub.publish(local_position_msg);
  }
}
void control_cmd_wrapper::local_server_global_position_sub_cb(const mavros_msgs::GlobalPositionTargetConstPtr& msg)
{
  if(_cur_control_type == local_server&&_local_server_target_cmd_type==global_position_cmd)
  {
    mavros_msgs::GlobalPositionTarget global_position_msg;
    global_position_msg.altitude = msg.get()->altitude;
    global_position_msg.latitude = msg.get()->latitude;
    global_position_msg.longitude = msg.get()->longitude;
    _global_position_cmd_pub.publish(global_position_msg);
  }
}
void control_cmd_wrapper::local_server_velocity_sub_cb(const geometry_msgs::TwistStampedConstPtr& msg)
{
  if(_cur_control_type == local_server&&_local_server_target_cmd_type==velocity_cmd)
  {
    geometry_msgs::TwistStamped velocity_msg;
    velocity_msg.twist.linear.x = msg.get()->twist.linear.x;
    velocity_msg.twist.linear.y = msg.get()->twist.linear.y;
    velocity_msg.twist.linear.z = msg.get()->twist.linear.z;
    _velocity_cmd_pub.publish(velocity_msg);
  }
}
void control_cmd_wrapper::local_server_control_apply_sub_cb(const std_msgs::BoolConstPtr& msg)
{
  _is_local_server_apply = msg.get()->data;
  update_control_type(local_server,_is_local_server_apply);
}
void control_cmd_wrapper::local_server_target_cmd_type_sub_cb(const std_msgs::Int8ConstPtr& msg)
{
  _local_server_target_cmd_type = msg.get()->data;
}

void control_cmd_wrapper::vr_server_local_position_sub_cb(const geometry_msgs::PoseStampedConstPtr& msg)
{
  if(_cur_control_type == vr_server&&_vr_server_target_cmd_type==local_position_cmd)
  {
    geometry_msgs::PoseStamped local_position_msg;
    local_position_msg.pose.position.x = msg.get()->pose.position.x;
    local_position_msg.pose.position.y = msg.get()->pose.position.y;
    local_position_msg.pose.position.z = msg.get()->pose.position.z;
    _local_position_cmd_pub.publish(local_position_msg);
  }
}
void control_cmd_wrapper::vr_server_global_position_sub_cb(const mavros_msgs::GlobalPositionTargetConstPtr& msg)
{
  if(_cur_control_type == vr_server&&_vr_server_target_cmd_type==global_position_cmd)
  {
    mavros_msgs::GlobalPositionTarget global_position_msg;
    global_position_msg.altitude = msg.get()->altitude;
    global_position_msg.latitude = msg.get()->latitude;
    global_position_msg.longitude = msg.get()->longitude;
    _global_position_cmd_pub.publish(global_position_msg);
  }
}
void control_cmd_wrapper::vr_server_velocity_sub_cb(const geometry_msgs::TwistStampedConstPtr& msg)
{
  if(_cur_control_type == vr_server&&_vr_server_target_cmd_type==velocity_cmd)
  {
    geometry_msgs::TwistStamped velocity_msg;
    velocity_msg.twist.linear.x = msg.get()->twist.linear.x;
    velocity_msg.twist.linear.y = msg.get()->twist.linear.y;
    velocity_msg.twist.linear.z = msg.get()->twist.linear.z;
    _velocity_cmd_pub.publish(velocity_msg);
  }
}
void control_cmd_wrapper::vr_server_control_apply_sub_cb(const std_msgs::BoolConstPtr& msg)
{
  _is_vr_server_apply = msg.get()->data;
  update_control_type(vr_server,_is_vr_server_apply);
}
void control_cmd_wrapper::vr_server_target_cmd_type_sub_cb(const std_msgs::Int8ConstPtr& msg)
{
  _vr_server_target_cmd_type = msg.get()->data;
}

void control_cmd_wrapper::dt_object_local_position_sub_cb(const geometry_msgs::PoseStampedConstPtr& msg)
{
  if(_cur_control_type == dt_object&&_dt_object_target_cmd_type==local_position_cmd)
  {
    geometry_msgs::PoseStamped local_position_msg;
    local_position_msg.pose.position.x = msg.get()->pose.position.x;
    local_position_msg.pose.position.y = msg.get()->pose.position.y;
    local_position_msg.pose.position.z = msg.get()->pose.position.z;
    _local_position_cmd_pub.publish(local_position_msg);
  }
}
void control_cmd_wrapper::dt_object_global_position_sub_cb(const mavros_msgs::GlobalPositionTargetConstPtr& msg)
{
  if(_cur_control_type == dt_object&&_dt_object_target_cmd_type==global_position_cmd)
  {
    mavros_msgs::GlobalPositionTarget global_position_msg;
    global_position_msg.altitude = msg.get()->altitude;
    global_position_msg.latitude = msg.get()->latitude;
    global_position_msg.longitude = msg.get()->longitude;
    _global_position_cmd_pub.publish(global_position_msg);
  }
}
void control_cmd_wrapper::dt_object_velocity_sub_cb(const geometry_msgs::TwistStampedConstPtr& msg)
{
  if(_cur_control_type == dt_object&&_dt_object_target_cmd_type==velocity_cmd)
  {
    geometry_msgs::TwistStamped velocity_msg;
    velocity_msg.twist.linear.x = msg.get()->twist.linear.x;
    velocity_msg.twist.linear.y = msg.get()->twist.linear.y;
    velocity_msg.twist.linear.z = msg.get()->twist.linear.z;
    _velocity_cmd_pub.publish(velocity_msg);
  }
}
void control_cmd_wrapper::dt_object_control_apply_sub_cb(const std_msgs::BoolConstPtr& msg)
{
  _is_dt_object_apply = msg.get()->data;
  update_control_type(dt_object,_is_dt_object_apply);
}
void control_cmd_wrapper::dt_object_target_cmd_type_sub_cb(const std_msgs::Int8ConstPtr& msg)
{
  _dt_object_target_cmd_type = msg.get()->data;
}

void control_cmd_wrapper::local_machine_local_position_sub_cb(const geometry_msgs::PoseStampedConstPtr& msg)
{
  if(_cur_control_type == local_machine&&_local_machine_target_cmd_type==local_position_cmd)
  {
    geometry_msgs::PoseStamped local_position_msg;
    local_position_msg.pose.position.x = msg.get()->pose.position.x;
    local_position_msg.pose.position.y = msg.get()->pose.position.y;
    local_position_msg.pose.position.z = msg.get()->pose.position.z;
    _local_position_cmd_pub.publish(local_position_msg);
  }
}
void control_cmd_wrapper::local_machine_global_position_sub_cb(const mavros_msgs::GlobalPositionTargetConstPtr& msg)
{
  if(_cur_control_type == local_machine&&_local_machine_target_cmd_type==global_position_cmd)
  {
    mavros_msgs::GlobalPositionTarget global_position_msg;
    global_position_msg.altitude = msg.get()->altitude;
    global_position_msg.latitude = msg.get()->latitude;
    global_position_msg.longitude = msg.get()->longitude;
    _global_position_cmd_pub.publish(global_position_msg);
  }
}
void control_cmd_wrapper::local_machine_velocity_sub_cb(const geometry_msgs::TwistStampedConstPtr& msg)
{
  if(_cur_control_type == local_machine&&_local_machine_target_cmd_type==velocity_cmd)
  {
    geometry_msgs::TwistStamped velocity_msg;
    velocity_msg.twist.linear.x = msg.get()->twist.linear.x;
    velocity_msg.twist.linear.y = msg.get()->twist.linear.y;
    velocity_msg.twist.linear.z = msg.get()->twist.linear.z;
    _velocity_cmd_pub.publish(velocity_msg);
  }
}
void control_cmd_wrapper::local_machine_control_apply_sub_cb(const std_msgs::BoolConstPtr& msg)
{
  _is_local_machine_apply = msg.get()->data;
  update_control_type(local_machine,_is_local_machine_apply);
}
void control_cmd_wrapper::local_machine_target_cmd_type_sub_cb(const std_msgs::Int8ConstPtr& msg)
{
  _local_machine_target_cmd_type = msg.get()->data;
}

void *control_cmd_wrapper::run(void *args)
{
  control_cmd_wrapper* cmd_wrapper = (control_cmd_wrapper*)(args);
  ros::Rate rate(cmd_wrapper->_control_type_pub_frequency);
  std_msgs::Int8 control_type_msg;
  while (ros::ok())
  {
    control_type_msg.data = cmd_wrapper->_cur_control_type;
    cmd_wrapper->_cur_control_type_pub.publish(control_type_msg);
    rate.sleep();
  }

}
