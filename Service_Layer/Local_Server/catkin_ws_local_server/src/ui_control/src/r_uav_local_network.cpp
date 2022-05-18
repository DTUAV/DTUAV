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
#include "r_uav_local_network.h"
#include "ui_r_uav_local_network.h"
bool r_uav_local_network::set_object_id(int id)
{
    _object_id = id;
    return true;
}


void r_uav_local_network::camera_sub_cb(const sensor_msgs::CompressedImage::ConstPtr &msg)
{
  cv_bridge::CvImagePtr cv_ptr_compressed = cv_bridge::toCvCopy(msg,sensor_msgs::image_encodings::BGR8);
  _camera_data = cv_ptr_compressed->image;
}

void r_uav_local_network::current_position_sub_cb(const geometry_msgs::PoseStamped::ConstPtr &msg)
{
  _current_pose.pose = msg.get()->pose;
  _current_move_track_msg.header.frame_id="r_uav_local";
  geometry_msgs::PoseStamped this_pose_stamped;
  this_pose_stamped.pose.position.x = msg.get()->pose.position.x;
  this_pose_stamped.pose.position.y = msg.get()->pose.position.y;
  this_pose_stamped.pose.position.z = msg.get()->pose.position.z;
  this_pose_stamped.header.frame_id="r_uav_local";
  _current_move_track_msg.poses.push_back(this_pose_stamped);
  _movement_track_pub.publish(_current_move_track_msg);
}

bool r_uav_local_network::set_network_name(std::string networkName)
{
_network_name = networkName;
return true;
}

bool r_uav_local_network::set_object_name(std::string objectName)
{
    _object_name = objectName;
    return true;
}

void r_uav_local_network::init_ros()
{
    ros::NodeHandle n("~");
    std::string tempString;
    n.getParam("link_network_pub_topic",tempString);
    _link_network_pub_topic = "/"+_object_name+"/"+_network_name+tempString;
     n.getParam("target_position_pub_topic",tempString);
     _target_position_pub_topic = "/"+_object_name+"/"+_network_name+tempString;
     n.getParam("mission_start_pub_topic",tempString);
     _mission_start_pub_topic = "/"+_object_name+"/"+_network_name+tempString;

     n.getParam("current_pose_sub_topic",tempString);
     _current_pose_sub_topic = "/"+_object_name+"/"+_network_name+tempString;

     n.getParam("current_camera_sub_topic",tempString);
     _current_camera_sub_topic = "/"+_object_name+"/"+_network_name+tempString;

     n.getParam("movement_track_pub_topic",tempString);
     _movement_track_pub_topic = "/"+_object_name+"/"+_network_name+tempString;

     n.getParam("request_camera_data_pub_topic",tempString);
     _request_camera_data_pub_topic =  "/"+_object_name+"/"+_network_name+tempString;

     n.getParam("target_movement_track_pub_topic",tempString);
     _target_movement_track_pub_topic = "/"+_object_name+"/"+_network_name+tempString;

     n.getParam("system_start_pub_topic",tempString);
     _system_start_pub_topic = "/"+_object_name+"/"+_network_name+tempString;

     _link_network_pub = n.advertise<std_msgs::Bool>(_link_network_pub_topic,1);
     _target_position_pub = n.advertise<geometry_msgs::PoseStamped>(_target_position_pub_topic,1);
     _mission_start_pub = n.advertise<dt_message_package::mission_msg>(_mission_start_pub_topic,1);
     _current_pose_sub = n.subscribe(_current_pose_sub_topic,1,&r_uav_local_network::current_position_sub_cb,this);
     _movement_track_pub = n.advertise<nav_msgs::Path>(_movement_track_pub_topic,1);
     _current_camera_sub = n.subscribe(_current_camera_sub_topic,1,&r_uav_local_network::camera_sub_cb,this);
     _request_camera_data_pub = n.advertise<std_msgs::Bool>(_request_camera_data_pub_topic,1);
     _target_movement_track_pub = n.advertise<nav_msgs::Path>(_target_movement_track_pub_topic,1);
     _system_start_pub = n.advertise<std_msgs::Bool>(_system_start_pub_topic,1);

     std::string label_uav = "R_UAV_"+std::to_string(_object_id);
     QString label_uav_qt = QString::fromLocal8Bit(label_uav.data());
     ui->v_uav_0_label_3->setText(label_uav_qt);
     QPalette pe;
     pe.setColor(QPalette::WindowText,Qt::green);
      ui->v_uav_0_label_3->setPalette(pe);

}

r_uav_local_network::r_uav_local_network(QWidget *parent) :
  QMainWindow(parent),
  ui(new Ui::r_uav_local_network)
{
  ui->setupUi(this);
  m_nTimerID = this->startTimer(500);

  _current_pose.pose.position.x = 0.0;
  _current_pose.pose.position.y = 0.0;
  _current_pose.pose.position.z = 0.0;
}

r_uav_local_network::~r_uav_local_network()
{
  this->killTimer(m_nTimerID);
  delete ui;
}

void r_uav_local_network::timerEvent(QTimerEvent *event)
{
  if(event->timerId() == m_nTimerID){
    ui_update_timeout();
  }
}
void r_uav_local_network::ui_update_timeout()
{
  ui->v_uav_0_current_x->setText(QString::number(_current_pose.pose.position.x,10,4));
  ui->v_uav_0_current_y->setText(QString::number(_current_pose.pose.position.y,10,4));
  ui->v_uav_0_current_z->setText(QString::number(_current_pose.pose.position.z,10,4));
  if(!_camera_data.empty())
  {
    QImage r_uav_0_Img;
    cv::Mat r_uav_0_Rgb;
    if (_camera_data.channels() == 3)//RGB Img
    {
      cv::cvtColor(_camera_data, r_uav_0_Rgb, CV_BGR2RGB);//颜色空间转换
      r_uav_0_Img = QImage((const uchar*)(r_uav_0_Rgb.data), r_uav_0_Rgb.cols, r_uav_0_Rgb.rows, r_uav_0_Rgb.cols * r_uav_0_Rgb.channels(), QImage::Format_RGB888);
    }
    else//Gray Img
    {
      r_uav_0_Img = QImage((const uchar*)(_camera_data.data),_camera_data.cols, _camera_data.rows, _camera_data.cols*_camera_data.channels(), QImage::Format_Indexed8);
    }
    ui->v_uav_0_camera_image->setPixmap(QPixmap::fromImage(r_uav_0_Img));
  }
}

void r_uav_local_network::on_v_uav_0_takeoff_button_clicked()
{
  geometry_msgs::PoseStamped ref_msg;
  ref_msg.pose.position.x = _current_pose.pose.position.x;
  ref_msg.pose.position.y = _current_pose.pose.position.y;
  ref_msg.pose.position.z = ui->v_uav_0_ref_height_edit->text().toFloat();
  _target_position_pub.publish(ref_msg);

}

void r_uav_local_network::on_v_uav_0_land_button_clicked()
{
    geometry_msgs::PoseStamped ref_msg;
    ref_msg.pose.position.x = _current_pose.pose.position.x;
    ref_msg.pose.position.y = _current_pose.pose.position.y;
    ref_msg.pose.position.z = -50.0;
    _target_position_pub.publish(ref_msg);

}

void r_uav_local_network::on_v_uav_0_ref_pub_button_clicked()
{

  geometry_msgs::PoseStamped ref_msg;
  ref_msg.pose.position.x = ui->v_uav_0_ref_x_edit->text().toFloat();
  ref_msg.pose.position.y = ui->v_uav_0_ref_y_edit->text().toFloat();
  ref_msg.pose.position.z = ui->v_uav_0_ref_z_edit->text().toFloat();
  _target_position_pub.publish(ref_msg);

  _target_move_track_msg.header.frame_id="r_uav_local";
  geometry_msgs::PoseStamped this_pose_stamped;
  this_pose_stamped.pose.position.x = ui->v_uav_0_ref_x_edit->text().toFloat();
  this_pose_stamped.pose.position.y = ui->v_uav_0_ref_y_edit->text().toFloat();
  this_pose_stamped.pose.position.z = ui->v_uav_0_ref_z_edit->text().toFloat();
  this_pose_stamped.header.frame_id="r_uav_local";
  _target_move_track_msg.poses.push_back(this_pose_stamped);
  _target_movement_track_pub.publish(_target_move_track_msg);

}

void r_uav_local_network::on_v_uav_0_mission_start_button_clicked()
{
    bool is_mission = true;
    uint32_t mission_id = ui->v_uav_0_mission_id_edit->text().toInt();
    dt_message_package::mission_msg mission_msg;
    mission_msg.mission_id = mission_id;
    mission_msg.mission_state = is_mission;
   _mission_start_pub.publish(mission_msg);

}

void r_uav_local_network::on_v_uav_0_init_button_clicked()
{
    std_msgs::Bool system_start_msg;
    system_start_msg.data = true;
    _system_start_pub.publish(system_start_msg);
}
void r_uav_local_network::on_v_uav_0_link_button_clicked()
{

    std_msgs::Bool link_msg;
    link_msg.data = true;
    _link_network_pub.publish(link_msg);

}

void r_uav_local_network::on_v_uav_0_disconnect_button_clicked()
{

    std_msgs::Bool link_msg;
    link_msg.data = false;
    _link_network_pub.publish(link_msg);
    _system_start_pub.publish(link_msg);
}
void r_uav_local_network::on_v_uav_0_camera_open_button_clicked()
{
    std_msgs::Bool request_camera_data_msg;
    request_camera_data_msg.data = true;
    _request_camera_data_pub.publish(request_camera_data_msg);
}

void r_uav_local_network::on_v_uav_0_camera_close_button_clicked()
{
    std_msgs::Bool request_camera_data_msg;
    request_camera_data_msg.data = false;
    _request_camera_data_pub.publish(request_camera_data_msg);
}

