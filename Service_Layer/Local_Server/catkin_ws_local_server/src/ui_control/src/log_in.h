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
#ifndef LOG_IN_H
#define LOG_IN_H

#include <QMainWindow>
#include "r_uav_global_network.h"
#include "r_uav_local_network.h"
#include "v_uav_global_network.h"
#include "v_uav_local_network.h"
#include "vr_server_info.h"
#include <QButtonGroup>
#include <string>
namespace Ui {
class log_in;
}

class log_in : public QMainWindow
{
    Q_OBJECT

public:
    explicit log_in(QWidget *parent = 0);
    ~log_in();

public Q_SLOTS:
    void on_local_network_radioButton_clicked();

    void on_global_network_radioButton_clicked();

    void on_log_in_pushButton_clicked();

private:
    Ui::log_in *ui;
    int _object_id;
    int _network_type;//0:global_network 1:local_network
    QButtonGroup *_network_group;
};

#endif // LOG_IN_H
