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
#include "log_in.h"
#include "ui_log_in.h"
#include <QMainWindow>
log_in::log_in(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::log_in)
{
    ui->setupUi(this);
    _network_group = new QButtonGroup(this);
    _network_group->addButton(ui->local_network_radioButton,0);
    _network_group->addButton(ui->global_network_radioButton,1);
    ui->global_network_radioButton->setChecked(1);
    _network_type = 0;
}

log_in::~log_in()
{
    delete ui;
}

void log_in::on_local_network_radioButton_clicked()
{
    _network_type = 1;
}

void log_in::on_global_network_radioButton_clicked()
{
    _network_type = 0;
}

void log_in::on_log_in_pushButton_clicked()
{
  _object_id = ui->object_id_lineEdit->text().toInt();
  std::string object_id_string = ui->object_id_lineEdit->text().toStdString();
  if(_object_id<=100)
  {
      if(_network_type == 0)//global
      {
         r_uav_global_network* g_r_uav = new r_uav_global_network;
         g_r_uav->set_network_name("global_network");
         std::string object_name = "r_uav_"+ object_id_string;
         g_r_uav->set_object_name(object_name);
         g_r_uav->set_object_id(_object_id);
         g_r_uav->init_ros();
        // std::cout<<_object_id<<std::endl;
         g_r_uav->show();
      }
      else if(_network_type == 1)//local
      {
          r_uav_local_network* l_r_uav = new r_uav_local_network;
          l_r_uav->set_network_name("local_network");
          std::string object_name = "r_uav_"+ object_id_string;
          l_r_uav->set_object_name(object_name);
          l_r_uav->set_object_id(_object_id);
          l_r_uav->init_ros();

          l_r_uav->show();
      }
  }
  else if(_object_id>100&&_object_id<=200)
  {
      if(_network_type == 0)
      {

      }
      else if(_network_type == 1)
      {

      }
  }
  else if(_object_id>200&&_object_id<=300)
  {
      if(_network_type == 0)
      {
          v_uav_global_network* g_v_uav = new v_uav_global_network;
          g_v_uav->set_network_name("global_network");
          std::string object_name = "v_uav_"+ std::to_string(_object_id-100);
          g_v_uav->set_object_name(object_name);
                    g_v_uav->set_object_id(_object_id-100);
          g_v_uav->init_ros();

          g_v_uav->show();
      }
      else if(_network_type == 1)
      {
          v_uav_local_network* l_v_uav = new v_uav_local_network;
          l_v_uav->set_network_name("local_network");
          std::string object_name = "v_uav_"+ std::to_string(_object_id-100);
          l_v_uav->set_object_name(object_name);
                    l_v_uav->set_object_id(_object_id-100);
          l_v_uav->init_ros();

          l_v_uav->show();
      }
  }
  else if(_object_id>300&&_object_id<=400)
  {
      if(_network_type == 0)
      {
          vr_server_info* g_vr_info = new vr_server_info;
      ////    g_vr_info->set_network_name("global_network");
        //  std::string object_name = "/v_uav_"+ (_object_id-100);
       //   g_v_uav->set_object_name(object_name);
      }
      else if(_network_type == 1)
      {

      }
  }
  else
  {
      if(_network_type == 0)
      {

      }
      else if(_network_type == 1)
      {

      }
  }


}
