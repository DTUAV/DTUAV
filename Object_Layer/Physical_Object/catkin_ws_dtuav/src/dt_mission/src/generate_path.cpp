#include "../include/dt_mission/generate_path.h"

generate_path::~generate_path()
{
  delete  RML         ;
  delete  IP          ;
  delete  OP          ;
}


generate_path::generate_path()
{
  ros::NodeHandle n("~");
  n.getParam("init_x",_init_x);
  n.getParam("init_y",_init_y);
  n.getParam("init_z",_init_z);
  n.getParam("init_velocity_x",_init_velocity_x);
  n.getParam("init_velocity_y",_init_velocity_y);
  n.getParam("init_velocity_z",_init_velocity_z);
  n.getParam("max_velocity_x",_max_velocity_x);
  n.getParam("max_velocity_y",_max_velocity_y);
  n.getParam("max_velocity_z",_max_velocity_z);
  n.getParam("max_acc_x",_max_acc_x);
  n.getParam("max_acc_y",_max_acc_y);
  n.getParam("max_acc_z",_max_acc_z);
  n.getParam("max_jerk_x",_max_jerk_x);
  n.getParam("max_jerk_y",_max_jerk_y);
  n.getParam("max_jerk_z",_max_jerk_z);
  n.getParam("TargetPosSubTopic",_targetPosSubTopic);
  n.getParam("RefPosPubTopic",_refPosPubTopic);
  n.getParam("UpdateHz",_updatehz);
  n.getParam("curPositionSubTopic",_curPositionSubTopic);
  n.getParam("curVelocitySubTopic",_curVelocitySubTopic);
  _refPosPub = n.advertise<geometry_msgs::PoseStamped>(_refPosPubTopic,1);
  _targetPosSub = n.subscribe(_targetPosSubTopic,1,&generate_path::TargetPositionSubCallback,this);
  _curPositionSub = n.subscribe(_curPositionSubTopic,1,&generate_path::CurPositionSubCallback,this);
  _curVelocitySub = n.subscribe(_curVelocitySubTopic,1,&generate_path::CurVelocitySubCallback,this);
  RML =   new ReflexxesAPI(                   NUMBER_OF_DOFS
                                              ,   CYCLE_TIME_IN_SECONDS   );

  IP  =   new RMLPositionInputParameters(     NUMBER_OF_DOFS          );

  OP  =   new RMLPositionOutputParameters(    NUMBER_OF_DOFS          );


  int flag_thread = pthread_create(&run_thread,NULL,&generate_path::run,this);
  if (flag_thread < 0) {
    ROS_ERROR("pthread_create ros_process_thread failed: %d\n", flag_thread);
  }
  _cur_position_x = _init_x;
  _cur_position_y = _init_y;
  _cur_position_z = _init_z;
  _cur_velocity_x = _init_velocity_x;
  _cur_velocity_y = _init_velocity_y;
  _cur_velocity_z = _init_velocity_z;
  _target_position_x = _init_x;
  _target_position_y = _init_y;
  _target_position_z = _init_z;

}

void *generate_path::run(void *args)
{
  generate_path* path = (generate_path*)(args);
  geometry_msgs::PoseStamped refPositionMsg;
  ros::Rate rate(path->_updatehz);
  while(ros::ok())
  {
    if(path->_is_start)
    {
      path->_is_start = false;
     // std::cout<<"current_position: "<<path->_cur_position_x<<" "<<path->_cur_position_y<<" "<<path->_cur_position_z<<std::endl;
     // std::cout<<"max_velocity: "<<path->_max_velocity_x<<" "<<path.
      path->IP->CurrentPositionVector->VecData      [0] =   path->_cur_position_x;
      path->IP->CurrentPositionVector->VecData      [1] =   path->_cur_position_y;
      path->IP->CurrentPositionVector->VecData      [2] =   path->_cur_position_z;

      path->IP->CurrentVelocityVector->VecData      [0] =   0;//path->_cur_velocity_x;
      path->IP->CurrentVelocityVector->VecData      [1] =   0;//path->_cur_velocity_y;
      path->IP->CurrentVelocityVector->VecData      [2] =   0;//path->_cur_velocity_z;

      path->IP->CurrentAccelerationVector->VecData  [0] =    0.0;
      path->IP->CurrentAccelerationVector->VecData  [1] =    0.0;
      path->IP->CurrentAccelerationVector->VecData  [2] =    0.0;

      path->IP->MaxVelocityVector->VecData          [0] =   2.0;// path->_max_velocity_x;
      path->IP->MaxVelocityVector->VecData          [1] =   2.0;// path->_max_velocity_y;
      path->IP->MaxVelocityVector->VecData          [2] =   2.0;// path->_max_velocity_z;

      path->IP->MaxAccelerationVector->VecData      [0] =   0.8;// path->_max_acc_x;
      path->IP->MaxAccelerationVector->VecData      [1] =   0.8;// path->_max_acc_y;
      path->IP->MaxAccelerationVector->VecData      [2] =   0.8;// path->_max_acc_z;

      path->IP->MaxJerkVector->VecData              [0] =    1.8;//path->_max_jerk_x;
      path->IP->MaxJerkVector->VecData              [1] =    1.8;//path->_max_jerk_y;
      path->IP->MaxJerkVector->VecData              [2] =    1.5;//path->_max_jerk_z;

      path->IP->TargetPositionVector->VecData       [0] =  path->_target_position_x;
      path->IP->TargetPositionVector->VecData       [1] =  path->_target_position_y;
      path->IP->TargetPositionVector->VecData       [2] =  path->_target_position_z;

      path->IP->TargetVelocityVector->VecData       [0] =   0.0;
      path->IP->TargetVelocityVector->VecData       [1] =   0.0;
      path->IP->TargetVelocityVector->VecData       [2] =   0.0;

      path->IP->SelectionVector->VecData            [0] =   true;
      path->IP->SelectionVector->VecData            [1] =   true;
      path->IP->SelectionVector->VecData            [2] =   true;
      path->ResultValue = 0;

      // ********************************************************************
      // Starting the control loop

      while (path->ResultValue != ReflexxesAPI::RML_FINAL_STATE_REACHED)
      {

        // ****************************************************************
        // Wait for the next timer tick
        // (not implemented in this example in order to keep it simple)
        // ****************************************************************

        // Calling the Reflexxes OTG algorithm
        path->ResultValue =   path->RML->RMLPosition(       *(path->IP)
                                                ,   path->OP
                                                ,   path->Flags       );
        std::cout<<"target_position: x: "<<path->_target_position_x<<" y:"<<path->_target_position_y<<" z:"<<path->_target_position_z<<std::endl;

        if (path->ResultValue < 0)
        {
          printf("An error occurred (%d).\n", path->ResultValue );
          path->ResultValue = 0;
          break;
        }

        // ****************************************************************
        // Here, the new state of motion, that is
        //
        // - OP->NewPositionVector
        // - OP->NewVelocityVector
        // - OP->NewAccelerationVector
        //
        // can be used as input values for lower level controllers. In the
        // most simple case, a position controller in actuator space is
        // used, but the computed state can be applied to many other
        // controllers (e.g., Cartesian impedance controllers,
        // operational space controllers).
        // ****************************************************************

        // ****************************************************************
        // Feed the output values of the current control cycle back to
        // input values of the next control cycle

        *(path->IP)->CurrentPositionVector      =   *(path->OP)->NewPositionVector      ;
        *(path->IP)->CurrentVelocityVector      =   *(path->OP)->NewVelocityVector      ;
        *(path->IP)->CurrentAccelerationVector  =   *(path->OP)->NewAccelerationVector  ;
        refPositionMsg.pose.position.x = path->IP->CurrentPositionVector->VecData[0];
        refPositionMsg.pose.position.y = path->IP->CurrentPositionVector->VecData[1];
        refPositionMsg.pose.position.z = path->IP->CurrentPositionVector->VecData[2];
        refPositionMsg.header.stamp = ros::Time::now();
        path->_refPosPub.publish(refPositionMsg);
        std::cout<<"position_x: "<<path->IP->CurrentPositionVector->VecData[0]<<",position_y: "<<path->IP->CurrentPositionVector->VecData[1]<<",position_z: "<<path->IP->CurrentPositionVector->VecData[2]<<std::endl;
        rate.sleep();
      }

    }
  }
  pthread_join(path->run_thread,NULL);


}

void generate_path::CurVelocitySubCallback(const geometry_msgs::TwistStampedConstPtr &msg)
{
  _cur_velocity_x = msg.get()->twist.linear.x;
  _cur_velocity_y = msg.get()->twist.linear.y;
  _cur_velocity_z = msg.get()->twist.linear.z;
}

void generate_path::CurPositionSubCallback(const geometry_msgs::PoseStampedConstPtr &msg)
{
  _cur_position_x = msg.get()->pose.position.x;
  _cur_position_y = msg.get()->pose.position.y;
  _cur_position_z = msg.get()->pose.position.z;
}

void generate_path::TargetPositionSubCallback(const geometry_msgs::PoseStamped::ConstPtr &msg)
{
  _target_position_x = msg.get()->pose.position.x;
  _target_position_y = msg.get()->pose.position.y;
  _target_position_z = msg.get()->pose.position.z;
  _is_start = true;
}

