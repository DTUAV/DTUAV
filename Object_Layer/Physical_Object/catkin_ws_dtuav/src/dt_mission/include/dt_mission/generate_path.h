#ifndef GENERATE_PATH_H
#define GENERATE_PATH_H
#include "iostream"
#include "ros/ros.h"
#include "geometry_msgs/PoseStamped.h"
#include "geometry_msgs/TwistStamped.h"
#include "ros/time.h"
#include "pthread.h"
#include <../TypeIVRML/include/ReflexxesAPI.h>
#include <../TypeIVRML/include/RMLPositionFlags.h>
#include <../TypeIVRML/include/RMLPositionInputParameters.h>
#include <../TypeIVRML/include/RMLPositionOutputParameters.h>
#include "iostream"
#define CYCLE_TIME_IN_SECONDS                   0.01
#define NUMBER_OF_DOFS                          3
class generate_path
{
public:
  generate_path();
  ~generate_path();
  static void *run(void *args);
  void TargetPositionSubCallback(const geometry_msgs::PoseStamped::ConstPtr& msg);
  void CurPositionSubCallback(const geometry_msgs::PoseStampedConstPtr& msg);
  void CurVelocitySubCallback(const geometry_msgs::TwistStampedConstPtr& msg);

private:
  std::string _targetPosSubTopic;
  std::string _refPosPubTopic;
  std::string _curPositionSubTopic;
  std::string _curVelocitySubTopic;

  float _init_x;
  float _init_y;
  float _init_z;
  float _init_velocity_x;
  float _init_velocity_y;
  float _init_velocity_z;

  bool  _is_start;
  float _updatehz;

  float _cur_position_x;
  float _cur_position_y;
  float _cur_position_z;

  float _cur_velocity_x;
  float _cur_velocity_y;
  float _cur_velocity_z;

  float _cur_acc_x;
  float _cur_acc_y;
  float _cur_acc_z;

  float _max_velocity_x;
  float _max_velocity_y;
  float _max_velocity_z;

  float _max_acc_x;
  float _max_acc_y;
  float _max_acc_z;

  float _max_jerk_x;
  float _max_jerk_y;
  float _max_jerk_z;

  float _target_position_x;
  float _target_position_y;
  float _target_position_z;

  float _target_velocity_x;
  float _target_velocity_y;
  float _target_velocity_z;

  ros::Subscriber _targetPosSub;
  ros::Subscriber _curPositionSub;
  ros::Subscriber _curVelocitySub;

  ros::Publisher _refPosPub;
  int                         ResultValue                 =   0       ;

  ReflexxesAPI                *RML                        =   NULL    ;

  RMLPositionInputParameters  *IP                         =   NULL    ;

  RMLPositionOutputParameters *OP                         =   NULL    ;

  RMLPositionFlags            Flags                                   ;

  pthread_t run_thread;

};

#endif // GENERATE_PATH_H
