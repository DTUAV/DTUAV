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
#ifndef V_UAV_LOCAL_NETWORK_H
#define V_UAV_LOCAL_NETWORK_H

#include <QMainWindow>
#include <ros/ros.h>
#include "std_msgs/Bool.h"
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>
#include <iostream>
#include <QTimer>
#include <vector>
#include <string>
#include <sys/stat.h>
#include <iomanip>
#include <sstream>
#include "stdio.h"
#include "string.h"
#include "tf/tf.h"

#include "sensor_msgs/Imu.h"
#include "geometry_msgs/PoseStamped.h"
#include "std_msgs/Bool.h"

#include "sensor_msgs/CompressedImage.h"
#include "geometry_msgs/PoseStamped.h"
#include <geometry_msgs/Quaternion.h>
#include <nav_msgs/Path.h>
#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <cv_bridge/cv_bridge.h>

#include "dt_message_package/mission_msg.h"

namespace Ui {
class v_uav_local_network;
}

class v_uav_local_network : public QMainWindow
{
  Q_OBJECT

public:
  explicit v_uav_local_network(QWidget *parent = 0);
  ~v_uav_local_network();
public:
  void camera_sub_cb(const sensor_msgs::CompressedImage::ConstPtr &msg);
  void current_position_sub_cb(const geometry_msgs::PoseStamped::ConstPtr &msg);

  void init_ros();
  bool set_object_name(std::string objectName);
  bool set_network_name(std::string networkName);
    bool set_object_id(int id);

    int m_nTimerID;

 protected:
    void timerEvent(QTimerEvent *event);

public Q_SLOTS:
  void ui_update_timeout();

  void on_v_uav_0_link_button_clicked();

  void on_v_uav_0_disconnect_button_clicked();

  void on_v_uav_0_takeoff_button_clicked();

  void on_v_uav_0_land_button_clicked();

  void on_v_uav_0_ref_pub_button_clicked();

  void on_v_uav_0_init_button_clicked();

  void on_v_uav_0_mission_start_button_clicked();

  void on_v_uav_0_camera_open_button_clicked();

  void on_v_uav_0_camera_close_button_clicked();

  //---->iot

  //ros


private:
  Ui::v_uav_local_network *ui;

  std::string _link_network_pub_topic; // only this publish true, unpackage the message from cloud server or local server
  ros::Publisher _link_network_pub;

  std::string _target_position_pub_topic;
  ros::Publisher _target_position_pub;

  std::string _mission_start_pub_topic;
  ros::Publisher _mission_start_pub;

  std::string _current_pose_sub_topic;
  ros::Subscriber _current_pose_sub;

  std::string _movement_track_pub_topic;
  ros::Publisher _movement_track_pub;

  std::string _target_movement_track_pub_topic;
  ros::Publisher _target_movement_track_pub;

  std::string _current_camera_sub_topic;
  ros::Subscriber _current_camera_sub;

  std::string _request_camera_data_pub_topic;
  ros::Publisher _request_camera_data_pub;

  std::string _system_start_pub_topic;
  ros::Publisher _system_start_pub;

  nav_msgs::Path  _target_move_track_msg;
  nav_msgs::Path  _current_move_track_msg;

  std::string _object_name;
  std::string _network_name;


 geometry_msgs::PoseStamped _current_pose;
  cv::Mat _camera_data;

    int _object_id;
};

#endif // V_UAV_0_H
