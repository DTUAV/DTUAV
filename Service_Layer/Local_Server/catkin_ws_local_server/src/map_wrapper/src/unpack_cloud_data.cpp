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
#include "../include/map_wrapper/unpack_cloud_data.h"
void iot_msg_ros_sub(const mavros_msgs::MavlinkConstPtr& recv_msg)
{
  std::cout<<"inini--------------"<<endl;
   mavlink_message_t msg;
   msg.checksum = recv_msg.get()->checksum;
   msg.compid   = recv_msg.get()->compid;
   msg.len      = recv_msg.get()->len;
   msg.magic    = recv_msg.get()->magic;
   msg.msgid    = recv_msg.get()->msgid;
   msg.seq      = recv_msg.get()->seq;
   msg.sysid    = recv_msg.get()->sysid;
   msg.payload64[recv_msg.get()->payload64.size()];
   for(int i =0; i<recv_msg.get()->payload64.size();i++)
   {
     msg.payload64[i] = recv_msg.get()->payload64.at(i);
   }
   std::cout<<"in-----------------------------------"<<endl;
  switch (msg.msgid) {
                      case MAVLINK_MSG_ID_HEARTBEAT://0
                           mavlink_heartbeat_t heartbeat;
                           mavlink_msg_heartbeat_decode(&msg, &heartbeat);
                           cout<<"---->recv heartbeat msg<----"<<endl;
                           break;
                      case MAVLINK_MSG_ID_SYS_STATUS://1
                           mavlink_sys_status_t sys_status;
                           mavlink_msg_sys_status_decode(&msg,&sys_status);
                           cout<<"---->recv sys status msg<----"<<endl;
                           break;
                      case MAVLINK_MSG_ID_SYSTEM_TIME://2
                           mavlink_system_time_t system_time;
                           mavlink_msg_system_time_decode(&msg,&system_time);
                           cout<<"---->recv system time msg<----"<<endl;
                           break;
                      case MAVLINK_MSG_ID_PING:// 4
                           mavlink_ping_t ping;
                           mavlink_msg_ping_decode(&msg,&ping);
                           cout<<"---->recv ping msg<----"<<endl;
                           break;
                      case MAVLINK_MSG_ID_CHANGE_OPERATOR_CONTROL://5
                           mavlink_change_operator_control_t change_operator_control;
                           mavlink_msg_change_operator_control_decode(&msg,&change_operator_control);
                           cout<<"---->recv change operator control msg<----"<<endl;
                           break;
                      case MAVLINK_MSG_ID_CHANGE_OPERATOR_CONTROL_ACK://6
                           mavlink_change_operator_control_ack_t change_operator_control_ack;
                           mavlink_msg_change_operator_control_ack_decode(&msg,&change_operator_control_ack);
                           cout<<"---->recv change operator control ack msg<----"<<endl;
                           break;
                      case MAVLINK_MSG_ID_AUTH_KEY://7
                           mavlink_auth_key_t auth_key;
                           mavlink_msg_auth_key_decode(&msg,&auth_key);
                           cout<<"---->recv auth key msg<----"<<endl;
                           break;
                      case MAVLINK_MSG_ID_LINK_NODE_STATUS://8
                           mavlink_link_node_status_t link_node_status;
                           mavlink_msg_link_node_status_decode(&msg,&link_node_status);
                           cout<<"---->recv link node status msg<----"<<endl;
                           break;
                      case MAVLINK_MSG_ID_SET_MODE://11
                           mavlink_set_mode_t set_mode;
                           mavlink_msg_set_mode_decode(&msg,&set_mode);
                           cout<<"---->recv set mode msg<----"<<endl;
                           break;
                      case MAVLINK_MSG_ID_PARAM_REQUEST_READ://20
                           mavlink_param_request_read_t param_request_read;
                           mavlink_msg_param_request_read_decode(&msg,&param_request_read);
                           cout<<"---->recv param request read msg<----"<<endl;
                           break;
                      case MAVLINK_MSG_ID_PARAM_REQUEST_LIST://21
                           mavlink_param_request_list_t param_request_list;
                           mavlink_msg_param_request_list_decode(&msg,&param_request_list);
                           cout<<"---->recv param request list msg<----"<<endl;
                           break;
                      case MAVLINK_MSG_ID_PARAM_VALUE:// 22
                           mavlink_param_value_t param_value;
                           mavlink_msg_param_value_decode(&msg,&param_value);
                           cout<<"---->recv param value msg<----"<<endl;
                           break;
                      case MAVLINK_MSG_ID_PARAM_SET://23
                           mavlink_param_set_t param_set;
                           mavlink_msg_param_set_decode(&msg,&param_set);
                           cout<<"---->recv param set msg<----"<<endl;
                           break;
                      case MAVLINK_MSG_ID_GPS_RAW_INT://24
                           mavlink_gps_raw_int_t gps_raw_int;
                           mavlink_msg_gps_raw_int_decode(&msg,&gps_raw_int);
                           cout<<"---->recv gps raw int msg<----"<<endl;
                           break;
                      case MAVLINK_MSG_ID_GPS_STATUS://25
                           mavlink_gps_status_t gps_status;
                           mavlink_msg_gps_status_decode(&msg,&gps_status);
                           cout<<"---->recv gps status msg<----"<<endl;
                           break;
                      case MAVLINK_MSG_ID_SCALED_IMU://26
                           mavlink_scaled_imu_t scaled_imu;
                           mavlink_msg_scaled_imu_decode(&msg,&scaled_imu);
                           cout<<"---->recv scaled imu msg<----"<<endl;
                           break;
                      case MAVLINK_MSG_ID_RAW_IMU://27
                           mavlink_raw_imu_t raw_imu;
                           mavlink_msg_raw_imu_decode(&msg,&raw_imu);
                           cout<<"---->recv raw imu msg<----"<<endl;
                           break;
                      case MAVLINK_MSG_ID_RAW_PRESSURE://28
                           mavlink_raw_pressure_t raw_pressure;
                           mavlink_msg_raw_pressure_decode(&msg,&raw_pressure);
                           cout<<"---->recv raw pressure msg<----"<<endl;
                           break;
                      case MAVLINK_MSG_ID_SCALED_PRESSURE://29
                           mavlink_scaled_pressure_t scaled_pressure;
                           mavlink_msg_scaled_pressure_decode(&msg,&scaled_pressure);
                           cout<<"---->recv scaled pressure msg<----"<<endl;
                           break;
                      case MAVLINK_MSG_ID_ATTITUDE://30
                           mavlink_attitude_t attitude;
                           mavlink_msg_attitude_decode(&msg,&attitude);
                           cout<<"---->recv attitude msg<----"<<endl;
                           break;
                      case MAVLINK_MSG_ID_ATTITUDE_QUATERNION://31
                           mavlink_attitude_quaternion_t attitude_quaternion;
                           mavlink_msg_attitude_quaternion_decode(&msg,&attitude_quaternion);
                           cout<<"---->recv attitude quaternion<----"<<endl;
                           break;
                      case MAVLINK_MSG_ID_LOCAL_POSITION_NED://32
                           mavlink_local_position_ned_t local_position_ned;
                           mavlink_msg_local_position_ned_decode(&msg,&local_position_ned);
                           cout<<"---->recv local position ned msg<----"<<endl;
                           break;
                      case MAVLINK_MSG_ID_GLOBAL_POSITION_INT://33
                           mavlink_global_position_int_t global_position_int;
                           mavlink_msg_global_position_int_decode(&msg,&global_position_int);
                           cout<<"---->recv global position int msg<----"<<endl;
                           break;
                      case MAVLINK_MSG_ID_RC_CHANNELS_SCALED://34
                           mavlink_rc_channels_scaled_t rc_channels_scaled;
                           mavlink_msg_rc_channels_scaled_decode(&msg,&rc_channels_scaled);
                           cout<<"---->recv rc channels scaled msg<----"<<endl;
                           break;
                      case MAVLINK_MSG_ID_RC_CHANNELS_RAW://35
                           mavlink_rc_channels_raw_t rc_channels_raw;
                           mavlink_msg_rc_channels_raw_decode(&msg,&rc_channels_raw);
                           cout<<"---->recv rc channels raw msg<----"<<endl;
                           break;
                      case MAVLINK_MSG_ID_SERVO_OUTPUT_RAW://36
                           mavlink_servo_output_raw_t servo_output_raw;
                           mavlink_msg_servo_output_raw_decode(&msg,&servo_output_raw);
                           cout<<"---->recv servo output raw msg<----"<<endl;
                           break;
                      case MAVLINK_MSG_ID_MISSION_REQUEST_PARTIAL_LIST://37
                           mavlink_mission_request_partial_list_t mission_request_partial_list;
                           mavlink_msg_mission_request_partial_list_decode(&msg,&mission_request_partial_list);
                           cout<<"---->recv mission request partial list msg<----"<<endl;
                           break;
                      case MAVLINK_MSG_ID_MISSION_WRITE_PARTIAL_LIST://38
                           mavlink_mission_write_partial_list_t mission_write_partial_list;
                           mavlink_msg_mission_write_partial_list_decode(&msg,&mission_write_partial_list);
                           cout<<"---->recv mission write partial list msg<----"<<endl;
                           break;
                      case MAVLINK_MSG_ID_MISSION_ITEM://39
                           mavlink_mission_item_t mission_item;
                           mavlink_msg_mission_item_decode(&msg,&mission_item);
                           cout<<"---->recv mission item msg<----"<<endl;
                           break;
                      case MAVLINK_MSG_ID_MISSION_REQUEST://40
                           mavlink_mission_request_t mission_request;
                           mavlink_msg_mission_request_decode(&msg,&mission_request);
                           cout<<"---->recv mission request msg<----"<<endl;
                           break;
                      case MAVLINK_MSG_ID_MISSION_SET_CURRENT://41
                           mavlink_mission_set_current_t mission_set_current;
                           mavlink_msg_mission_set_current_decode(&msg,&mission_set_current);
                           cout<<"---->recv mission set current msg<----"<<endl;
                           break;
                      case MAVLINK_MSG_ID_MISSION_CURRENT://42
                           mavlink_mission_current_t mission_current;
                           mavlink_msg_mission_current_decode(&msg,&mission_current);
                           cout<<"---->recv mission current msg<----"<<endl;
                           break;
                      case MAVLINK_MSG_ID_MISSION_REQUEST_LIST://43
                           mavlink_mission_request_list_t mission_request_list;
                           mavlink_msg_mission_request_list_decode(&msg,&mission_request_list);
                           cout<<"---->recv mission request list msg<----"<<endl;
                           break;
                      case MAVLINK_MSG_ID_MISSION_COUNT://44
                           mavlink_mission_count_t mission_count;
                           mavlink_msg_mission_count_decode(&msg, &mission_count);
                           cout<<"---->recv mission count msg<----"<<endl;
                           break;
                      case MAVLINK_MSG_ID_MISSION_CLEAR_ALL://45
                           mavlink_mission_clear_all_t mission_clear_all;
                           mavlink_msg_mission_clear_all_decode(&msg,&mission_clear_all);
                           cout<<"---->recv mission clear all msg<----"<<endl;
                           break;
                      case MAVLINK_MSG_ID_MISSION_ITEM_REACHED://46
                           mavlink_mission_item_reached_t mission_item_reached;
                           mavlink_msg_mission_item_reached_decode(&msg,&mission_item_reached);
                           cout<<"---->recv mission item reached msg<----"<<endl;
                           break;
                      case MAVLINK_MSG_ID_MISSION_ACK://47
                           mavlink_mission_ack_t mission_ack;
                           mavlink_msg_mission_ack_decode(&msg,&mission_ack);
                           cout<<"---->recv mission ack msg<----"<<endl;
                           break;
                      case MAVLINK_MSG_ID_SET_GPS_GLOBAL_ORIGIN://48
                           mavlink_set_gps_global_origin_t set_gps_global_origin;
                           mavlink_msg_set_gps_global_origin_decode(&msg,&set_gps_global_origin);
                           cout<<"---->recv set gps global origin msg<----"<<endl;
                           break;
                      case MAVLINK_MSG_ID_GPS_GLOBAL_ORIGIN://49
                           mavlink_gps_global_origin_t gps_global_origin;
                           mavlink_msg_gps_global_origin_decode(&msg,&gps_global_origin);
                           cout<<"---->recv gps global origin msg<----"<<endl;
                           break;
                      case MAVLINK_MSG_ID_PARAM_MAP_RC://50
                           mavlink_param_map_rc_t param_rc_t;
                           mavlink_msg_param_map_rc_decode(&msg,&param_rc_t);
                           cout<<"---->recv param map rc msg<----"<<endl;
                           break;
                      case MAVLINK_MSG_ID_MISSION_REQUEST_INT://51
                           mavlink_mission_request_int_t mission_request_int;
                           mavlink_msg_mission_request_int_decode(&msg,&mission_request_int);
                           cout<<"---->recv mission request int msg<----"<<endl;
                           break;
                      case MAVLINK_MSG_ID_MISSION_CHANGED://52
                           mavlink_mission_changed_t mission_changed;
                           mavlink_msg_mission_changed_decode(&msg,&mission_changed);
                           cout<<"---->recv mission changed msg<----"<<endl;
                           break;
                      case MAVLINK_MSG_ID_SAFETY_SET_ALLOWED_AREA://54
                           mavlink_safety_set_allowed_area_t safety_set_allowed_area;
                           mavlink_msg_safety_set_allowed_area_decode(&msg,&safety_set_allowed_area);
                           cout<<"---->recv safety set allowed area msg<----"<<endl;
                           break;
                      case MAVLINK_MSG_ID_SAFETY_ALLOWED_AREA://55
                           mavlink_safety_allowed_area_t safety_allowed_area;
                           mavlink_msg_safety_allowed_area_decode(&msg,&safety_allowed_area);
                           cout<<"---->recv safety allowed area msg<----"<<endl;
                           break;
                      case MAVLINK_MSG_ID_ATTITUDE_QUATERNION_COV://61
                           mavlink_attitude_quaternion_cov_t attitude_quaternion_cov;
                           mavlink_msg_attitude_quaternion_cov_decode(&msg,&attitude_quaternion_cov);
                           cout<<"---->recv attitude quaternion cov msg<----"<<endl;
                           break;
                      case MAVLINK_MSG_ID_NAV_CONTROLLER_OUTPUT:// 62
                           mavlink_nav_controller_output_t nav_controller_output;
                           mavlink_msg_nav_controller_output_decode(&msg,&nav_controller_output);
                           cout<<"---->recv nav controller output msg<----"<<endl;
                           break;
                      case MAVLINK_MSG_ID_GLOBAL_POSITION_INT_COV://63
                           mavlink_global_position_int_cov_t global_position_int_cov;
                           mavlink_msg_global_position_int_cov_decode(&msg,&global_position_int_cov);
                           cout<<"---->recv global position int cov msg<----"<<endl;
                           break;
                      case MAVLINK_MSG_ID_LOCAL_POSITION_NED_COV://64
                           mavlink_local_position_ned_cov_t local_position_ned_cov;
                           mavlink_msg_local_position_ned_cov_decode(&msg,&local_position_ned_cov);
                           cout<<"---->recv local position ned cov msg<----"<<endl;
                           break;
                      case MAVLINK_MSG_ID_RC_CHANNELS://65
                           mavlink_rc_channels_t rc_channels;
                           mavlink_msg_rc_channels_decode(&msg,&rc_channels);
                           cout<<"---->recv rc channels msg<----"<<endl;
                           break;
                      case MAVLINK_MSG_ID_REQUEST_DATA_STREAM://66
                           mavlink_request_data_stream_t request_data_stream;
                           mavlink_msg_request_data_stream_decode(&msg,&request_data_stream);
                           cout<<"---->recv request data stream msg<----"<<endl;
                           break;
                      case MAVLINK_MSG_ID_DATA_STREAM://67
                           mavlink_data_stream_t data_stream;
                           mavlink_msg_data_stream_decode(&msg,&data_stream);
                           cout<<"---->recv data stream msg<----"<<endl;
                           break;
                      case MAVLINK_MSG_ID_MANUAL_CONTROL://69
                           mavlink_manual_control_t manual_control;
                           mavlink_msg_manual_control_decode(&msg,&manual_control);
                           cout<<"---->recv manual control msg<----"<<endl;
                           break;
                      case MAVLINK_MSG_ID_RC_CHANNELS_OVERRIDE://70
                           mavlink_rc_channels_override_t rc_channels_override;
                           mavlink_msg_rc_channels_override_decode(&msg,&rc_channels_override);
                           cout<<"---->rc channels override msg<----"<<endl;
                           break;
                      case MAVLINK_MSG_ID_MISSION_ITEM_INT://73
                           mavlink_mission_item_int_t mission_item_int;
                           mavlink_msg_mission_item_int_decode(&msg,&mission_item_int);
                           cout<<"---->recv mission item int msg<----"<<endl;
                           break;
                      case MAVLINK_MSG_ID_VFR_HUD://74
                           mavlink_vfr_hud_t vfr_hud;
                           mavlink_msg_vfr_hud_decode(&msg,&vfr_hud);
                           cout<<"---->recv vfr hud msg<----"<<endl;
                           break;
                      case MAVLINK_MSG_ID_COMMAND_INT://75
                           mavlink_command_int_t command_int;
                           mavlink_msg_command_int_decode(&msg,&command_int);
                           cout<<"---->recv command int<----"<<endl;
                           break;
                      case MAVLINK_MSG_ID_COMMAND_LONG://76
                           mavlink_command_long_t command_long;
                           mavlink_msg_command_long_decode(&msg,&command_long);
                           cout<<"---->command long<----"<<endl;
                           break;
                      case MAVLINK_MSG_ID_COMMAND_ACK://77
                           mavlink_command_ack_t command_ack;
                           mavlink_msg_command_ack_decode(&msg,&command_ack);
                           cout<<"---->recv command ack<----"<<endl;
                           break;
                      case MAVLINK_MSG_ID_COMMAND_CANCEL://80
                           mavlink_command_cancel_t command_cancel;
                           mavlink_msg_command_cancel_decode(&msg,&command_cancel);
                           cout<<"---->recv command cancel msg<----"<<endl;
                           break;
                      case MAVLINK_MSG_ID_MANUAL_SETPOINT://81
                           mavlink_manual_setpoint_t manual_setpoint;
                           mavlink_msg_manual_setpoint_decode(&msg,&manual_setpoint);
                           cout<<"---->recv manual setpoint msg<----"<<endl;
                           break;
                      case MAVLINK_MSG_ID_SET_ATTITUDE_TARGET://82
                           mavlink_set_attitude_target_t set_attitude_target;
                           mavlink_msg_set_attitude_target_decode(&msg,&set_attitude_target);
                           cout<<"---->recv set attitude target msg<----"<<endl;
                           break;
                      case MAVLINK_MSG_ID_ATTITUDE_TARGET://83
                           mavlink_attitude_target_t attitude_target;
                           mavlink_msg_attitude_target_decode(&msg,&attitude_target);
                           cout<<"---->recv attitude target msg<----"<<endl;
                           break;
                      case MAVLINK_MSG_ID_SET_POSITION_TARGET_LOCAL_NED://84
                           mavlink_set_position_target_local_ned_t set_position_target_local_ned;
                           mavlink_msg_set_position_target_local_ned_decode(&msg,&set_position_target_local_ned);
                           cout<<"---->recv set postion target local ned msg<----"<<endl;
                           break;
                      case MAVLINK_MSG_ID_POSITION_TARGET_LOCAL_NED://85
                           mavlink_position_target_local_ned_t position_target_local_net;
                           mavlink_msg_position_target_local_ned_decode(&msg,&position_target_local_net);
                           cout<<"---->recv position target local ned msg<----"<<endl;
                           break;
                      case MAVLINK_MSG_ID_SET_POSITION_TARGET_GLOBAL_INT://86
                           mavlink_set_position_target_global_int_t set_position_target_global_int;
                           mavlink_msg_set_position_target_global_int_decode(&msg,&set_position_target_global_int);
                           cout<<"---->recv set position target global int msg<----"<<endl;
                           break;
                      case MAVLINK_MSG_ID_POSITION_TARGET_GLOBAL_INT://87
                           mavlink_position_target_global_int_t position_target_global_int;
                           mavlink_msg_position_target_global_int_decode(&msg,&position_target_global_int);
                           cout<<"---->recv position target global int msg<----"<<endl;
                           break;
                      case MAVLINK_MSG_ID_LOCAL_POSITION_NED_SYSTEM_GLOBAL_OFFSET://89
                           mavlink_local_position_ned_system_global_offset_t local_position_ned_system_global_offset;
                           mavlink_msg_local_position_ned_system_global_offset_decode(&msg,&local_position_ned_system_global_offset);
                           cout<<"---->recv local position ned system global offset msg<----"<<endl;
                           break;
                      case MAVLINK_MSG_ID_HIL_STATE://90
                           mavlink_hil_state_t hil_state;
                           mavlink_msg_hil_state_decode(&msg,&hil_state);
                           cout<<"---->recv hil state msg<----"<<endl;
                           break;
                      case MAVLINK_MSG_ID_HIL_CONTROLS://91
                           mavlink_hil_controls_t hil_controls;
                           mavlink_msg_hil_controls_decode(&msg,&hil_controls);
                           cout<<"---->recv hil controls msg<----"<<endl;
                           break;
                      case MAVLINK_MSG_ID_HIL_RC_INPUTS_RAW://92
                           mavlink_hil_rc_inputs_raw_t hil_rc_inputs_raw;
                           mavlink_msg_hil_rc_inputs_raw_decode(&msg,&hil_rc_inputs_raw);
                           cout<<"---->recv hil rc input raw msg<----"<<endl;
                           break;
                      case MAVLINK_MSG_ID_HIL_ACTUATOR_CONTROLS://93
                           mavlink_hil_actuator_controls_t hil_actuator_control;
                           mavlink_msg_hil_actuator_controls_decode(&msg,&hil_actuator_control);
                           cout<<"---->recv hil actuator controls msg<----"<<endl;
                           break;
                      case MAVLINK_MSG_ID_OPTICAL_FLOW://100
                           mavlink_optical_flow_t optical_flow;
                           mavlink_msg_optical_flow_decode(&msg,&optical_flow);
                           cout<<"---->recv optical flow msg<----"<<endl;
                           break;
                      case MAVLINK_MSG_ID_GLOBAL_VISION_POSITION_ESTIMATE://101
                           mavlink_global_vision_position_estimate_t global_vision_position_estimate;
                           mavlink_msg_global_vision_position_estimate_decode(&msg,&global_vision_position_estimate);
                           cout<<"---->recv global vision position estimate msg<----"<<endl;
                           break;
                      case MAVLINK_MSG_ID_VISION_POSITION_ESTIMATE://102
                           mavlink_vision_position_estimate_t vision_position_estimate;
                           mavlink_msg_vision_position_estimate_decode(&msg,&vision_position_estimate);
                           cout<<"---->recv vision position estimate msg<----"<<endl;
                           break;
                      case MAVLINK_MSG_ID_VISION_SPEED_ESTIMATE://103
                           mavlink_vision_speed_estimate_t vision_speed_estimate;
                           mavlink_msg_vision_speed_estimate_decode(&msg,&vision_speed_estimate);
                           cout<<"---->recv vision speed estimate msg<----"<<endl;
                           break;
                      case MAVLINK_MSG_ID_VICON_POSITION_ESTIMATE://104
                           mavlink_vicon_position_estimate_t vicon_position_estimate;
                           mavlink_msg_vicon_position_estimate_decode(&msg,&vicon_position_estimate);
                           cout<<"---->recv vicon position estimate msg<----"<<endl;
                           break;
                      case MAVLINK_MSG_ID_HIGHRES_IMU://105
                           mavlink_highres_imu_t highres_imu;
                           mavlink_msg_highres_imu_decode(&msg,&highres_imu);
                           cout<<"---->recv highres imu msg<----"<<endl;
                           break;
                      case MAVLINK_MSG_ID_OPTICAL_FLOW_RAD://106
                           mavlink_optical_flow_rad_t optical_flow_rad;
                           mavlink_msg_optical_flow_rad_decode(&msg,&optical_flow_rad);
                           cout<<"---->recv optical flow rad msg<----"<<endl;
                           break;
                      case MAVLINK_MSG_ID_HIL_SENSOR://107
                           mavlink_hil_sensor_t hil_sensor;
                           mavlink_msg_hil_sensor_decode(&msg,&hil_sensor);
                           cout<<"---->recv hil sensor msg<----"<<endl;
                           break;
                      case MAVLINK_MSG_ID_SIM_STATE://108
                           mavlink_sim_state_t sim_state;
                           mavlink_msg_sim_state_decode(&msg,&sim_state);
                           cout<<"---->recv sim state msg<----"<<endl;
                           break;
                      case MAVLINK_MSG_ID_RADIO_STATUS://109
                           mavlink_radio_status_t radio_status;
                           mavlink_msg_radio_status_decode(&msg,&radio_status);
                           cout<<"---->recv radio status msg<----"<<endl;
                           break;
                      case MAVLINK_MSG_ID_FILE_TRANSFER_PROTOCOL://110
                           mavlink_file_transfer_protocol_t file_transfer_protocol;
                           mavlink_msg_file_transfer_protocol_decode(&msg,&file_transfer_protocol);
                           cout<<"---->recv file transfer protocol msg<----"<<endl;
                           break;
                      case MAVLINK_MSG_ID_TIMESYNC://111
                           mavlink_timesync_t timesync;
                           mavlink_msg_timesync_decode(&msg,&timesync);
                           cout<<"---->recv timesync msg<----"<<endl;
                           break;
                      case MAVLINK_MSG_ID_CAMERA_TRIGGER://112
                           mavlink_camera_trigger_t camera_trigger;
                           mavlink_msg_camera_trigger_decode(&msg,&camera_trigger);
                           cout<<"---->recv camera trigger<----"<<endl;
                           break;
                      case MAVLINK_MSG_ID_HIL_GPS://113
                           mavlink_hil_gps_t hil_gps;
                           mavlink_msg_hil_gps_decode(&msg,&hil_gps);
                           cout<<"---->recv hil gps msg<----"<<endl;
                           break;
                      case MAVLINK_MSG_ID_HIL_OPTICAL_FLOW://114
                           mavlink_hil_optical_flow_t hil_optical_flow;
                           mavlink_msg_hil_optical_flow_decode(&msg,&hil_optical_flow);
                           cout<<"---->recv hil optical flow msg<----"<<endl;
                           break;
                      case MAVLINK_MSG_ID_HIL_STATE_QUATERNION://115
                           mavlink_hil_state_quaternion_t state_quaternion;
                           mavlink_msg_hil_state_quaternion_decode(&msg,&state_quaternion);
                           cout<<"---->recv hil state quaternion msg<----"<<endl;
                           break;
                      case MAVLINK_MSG_ID_SCALED_IMU2://116
                           mavlink_scaled_imu2_t scaled_imu2;
                           mavlink_msg_scaled_imu2_decode(&msg,&scaled_imu2);
                           cout<<"---->recv scaled imu2 msg<----"<<endl;
                           break;
                      case MAVLINK_MSG_ID_LOG_REQUEST_LIST://117
                           mavlink_log_request_list_t log_request_list;
                           mavlink_msg_log_request_list_decode(&msg,&log_request_list);
                           cout<<"---->recv log request list msg<----"<<endl;
                           break;
                      case MAVLINK_MSG_ID_LOG_ENTRY://118
                           mavlink_log_entry_t log_entry;
                           mavlink_msg_log_entry_decode(&msg,&log_entry);
                           cout<<"---->recv log entry msg<----"<<endl;
                           break;
                      case MAVLINK_MSG_ID_LOG_REQUEST_DATA://119
                           mavlink_log_request_data_t log_request_data;
                           mavlink_msg_log_request_data_decode(&msg,&log_request_data);
                           cout<<"---->recv log request data msg<----"<<endl;
                           break;
                      case MAVLINK_MSG_ID_LOG_DATA://120
                           mavlink_log_data_t log_data;
                           mavlink_msg_log_data_decode(&msg,&log_data);
                           cout<<"---->recv log data msg<----"<<endl;
                           break;
                      case MAVLINK_MSG_ID_LOG_ERASE://121
                           mavlink_log_erase_t log_erase;
                           mavlink_msg_log_erase_decode(&msg,&log_erase);
                           cout<<"---->recv log erase msg<----"<<endl;
                           break;
                      case MAVLINK_MSG_ID_LOG_REQUEST_END://122
                           mavlink_log_request_end_t log_request_end;
                           mavlink_msg_log_request_end_decode(&msg,&log_request_end);
                           cout<<"---->recv log request end msg<----"<<endl;
                           break;
                      case MAVLINK_MSG_ID_GPS_INJECT_DATA://123
                           mavlink_gps_inject_data_t gps_inject_data;
                           mavlink_msg_gps_inject_data_decode(&msg,&gps_inject_data);
                           cout<<"---->recv gps inject data msg<----"<<endl;
                           break;
                      case MAVLINK_MSG_ID_GPS2_RAW://124
                           mavlink_gps2_raw_t gps2_raw;
                           mavlink_msg_gps2_raw_decode(&msg,&gps2_raw);
                           cout<<"---->recv gps2 raw msg<----"<<endl;
                           break;
                      case MAVLINK_MSG_ID_POWER_STATUS://125
                           mavlink_power_status_t power_status;
                           mavlink_msg_power_status_decode(&msg,&power_status);
                           cout<<"---->recv power status msg<----"<<endl;
                           break;
                      case MAVLINK_MSG_ID_SERIAL_CONTROL://126
                           mavlink_serial_control_t serial_control;
                           mavlink_msg_serial_control_decode(&msg,&serial_control);
                           cout<<"---->recv serial control msg<----"<<endl;
                           break;
                      case MAVLINK_MSG_ID_GPS_RTK://127
                           mavlink_gps_rtk_t gps_rtk;
                           mavlink_msg_gps_rtk_decode(&msg,&gps_rtk);
                           cout<<"---->recv gps rtk msg<----"<<endl;
                           break;
                      case MAVLINK_MSG_ID_GPS2_RTK://128
                           mavlink_gps2_rtk_t gps2_rtk;
                           mavlink_msg_gps2_rtk_decode(&msg,&gps2_rtk);
                           cout<<"---->recv gps2 rtk msg<----"<<endl;
                           break;
                      case MAVLINK_MSG_ID_SCALED_IMU3://129
                           mavlink_scaled_imu3_t scaled_imu3;
                           mavlink_msg_scaled_imu3_decode(&msg,&scaled_imu3);
                           cout<<"---->recv scaled imu3 msg<----"<<endl;
                           break;
                      case MAVLINK_MSG_ID_DATA_TRANSMISSION_HANDSHAKE://130
                           mavlink_data_transmission_handshake_t data_transmission_handshake;
                           mavlink_msg_data_transmission_handshake_decode(&msg,&data_transmission_handshake);
                           cout<<"---->recv data transmission handshake msg<----"<<endl;
                           break;
                      case MAVLINK_MSG_ID_ENCAPSULATED_DATA://131
                           mavlink_encapsulated_data_t encapsulated_data;
                           mavlink_msg_encapsulated_data_decode(&msg,&encapsulated_data);
                           cout<<"---->recv encapsulated data msg<----"<<endl;
                           break;
                      case MAVLINK_MSG_ID_DISTANCE_SENSOR://132
                           mavlink_distance_sensor_t distance_sensor;
                           mavlink_msg_distance_sensor_decode(&msg,&distance_sensor);
                           cout<<"---->recv distance sensor msg<----"<<endl;
                           break;
                      case MAVLINK_MSG_ID_TERRAIN_DATA://134
                           mavlink_terrain_data_t terrain_data;
                           mavlink_msg_terrain_data_decode(&msg,&terrain_data);
                           cout<<"---->recv terrain data msg<----"<<endl;
                           break;
                      case MAVLINK_MSG_ID_TERRAIN_CHECK://135
                           mavlink_terrain_check_t terrain_check;
                           mavlink_msg_terrain_check_decode(&msg,&terrain_check);
                           cout<<"---->recv terrain check msg<----"<<endl;
                           break;
                      case MAVLINK_MSG_ID_TERRAIN_REPORT://136
                           mavlink_terrain_report_t terrain_report;
                           mavlink_msg_terrain_report_decode(&msg,&terrain_report);
                           cout<<"---->recv terrain report msg<----"<<endl;
                           break;
                      case MAVLINK_MSG_ID_SCALED_PRESSURE2://137
                           mavlink_scaled_pressure2_t scaled_pressure2;
                           mavlink_msg_scaled_pressure2_decode(&msg,&scaled_pressure2);
                           cout<<"---->recv scaled pressure2 msg<----"<<endl;
                           break;
                      case MAVLINK_MSG_ID_ATT_POS_MOCAP://138
                           mavlink_att_pos_mocap_t att_pos_mocap;
                           mavlink_msg_att_pos_mocap_decode(&msg,&att_pos_mocap);
                           cout<<"---->recv att pos mocap<----"<<endl;
                           break;
                      case MAVLINK_MSG_ID_SET_ACTUATOR_CONTROL_TARGET://139
                           mavlink_set_actuator_control_target_t set_actuator_control_target;
                           mavlink_msg_set_actuator_control_target_decode(&msg,&set_actuator_control_target);
                           cout<<"---->recv set actuator control target msg<----"<<endl;
                           break;
                      case MAVLINK_MSG_ID_ACTUATOR_CONTROL_TARGET://140
                           mavlink_actuator_control_target_t actuator_ctr_tagt;
                           mavlink_msg_actuator_control_target_decode(&msg,&actuator_ctr_tagt);
                           cout<<"---->recv actuator control target msg<-----"<<endl;
                           break;
                      case MAVLINK_MSG_ID_ALTITUDE://141
                           mavlink_altitude_t altitude;
                           mavlink_msg_altitude_decode(&msg,&altitude);
                           cout<<"---->recv altitude msg<----"<<endl;
                           break;
                      case MAVLINK_MSG_ID_RESOURCE_REQUEST://142
                           mavlink_resource_request_t resourse_request;
                           mavlink_msg_resource_request_decode(&msg,&resourse_request);
                           cout<<"---->recv resource request msg<----"<<endl;
                           break;
                      case MAVLINK_MSG_ID_SCALED_PRESSURE3://143
                           mavlink_scaled_pressure3_t scaled_pressure3;
                           mavlink_msg_scaled_pressure3_decode(&msg,&scaled_pressure3);
                           cout<<"---->recv scaled pressure3 msg<----"<<endl;
                           break;
                      case MAVLINK_MSG_ID_FOLLOW_TARGET://144
                           mavlink_follow_target_t follow_target;
                           mavlink_msg_follow_target_decode(&msg,&follow_target);
                           cout<<"----->recv follow target msg<----"<<endl;
                           break;
                      case MAVLINK_MSG_ID_CONTROL_SYSTEM_STATE://146
                           mavlink_control_system_state_t control_system_state;
                           mavlink_msg_control_system_state_decode(&msg,&control_system_state);
                           cout<<"---->control system state msg<----"<<endl;
                           break;
                      case MAVLINK_MSG_ID_BATTERY_STATUS://147
                           mavlink_battery_status_t battery_status;
                           mavlink_msg_battery_status_decode(&msg,&battery_status);
                           cout<<"---->recv battery status<----"<<endl;
                           break;
                      case MAVLINK_MSG_ID_AUTOPILOT_VERSION://148
                           mavlink_autopilot_version_t autopilot_version;
                           mavlink_msg_autopilot_version_decode(&msg,&autopilot_version);
                           cout<<"---->recv autopilot version<----"<<endl;
                           break;
                      case MAVLINK_MSG_ID_LANDING_TARGET://149
                           mavlink_landing_target_t landing_target;
                           mavlink_msg_landing_target_decode(&msg,&landing_target);
                           cout<<"---->recv landing target msg<----"<<endl;
                           break;
                      case MAVLINK_MSG_ID_FENCE_STATUS://162
                           mavlink_fence_status_t fence_status;
                           mavlink_msg_fence_status_decode(&msg,&fence_status);
                           cout<<"---->recv fence status msg<----"<<endl;
                           break;
                      case MAVLINK_MSG_ID_ESTIMATOR_STATUS://230
                           mavlink_estimator_status_t estimator_status;
                           mavlink_msg_estimator_status_decode(&msg,&estimator_status);
                           cout<<"---->recv estimator status msg<----"<<endl;
                           break;
                      case MAVLINK_MSG_ID_WIND_COV://231
                           mavlink_wind_cov_t wind_cov;
                           mavlink_msg_wind_cov_decode(&msg,&wind_cov);
                           cout<<"---->recv wind cov msg<----"<<endl;
                           break;
                      case MAVLINK_MSG_ID_GPS_INPUT://232
                           mavlink_gps_input_t gps_input;
                           mavlink_msg_gps_input_decode(&msg,&gps_input);
                           cout<<"---->recv gps input msg<----"<<endl;
                           break;
                      case MAVLINK_MSG_ID_GPS_RTCM_DATA://233
                           mavlink_gps_rtcm_data_t gps_rtcm_data;
                           mavlink_msg_gps_rtcm_data_decode(&msg,&gps_rtcm_data);
                           cout<<"---->recv gps rtcm data msg<----"<<endl;
                           break;
                      case MAVLINK_MSG_ID_HIGH_LATENCY://234
                           mavlink_high_latency_t high_latency;
                           mavlink_msg_high_latency_decode(&msg,&high_latency);
                           cout<<"---->recv high latency msg<----"<<endl;
                           break;
                      case MAVLINK_MSG_ID_HIGH_LATENCY2://235
                           mavlink_high_latency2_t high_latency2;
                           mavlink_msg_high_latency2_decode(&msg,&high_latency2);
                           cout<<"---->recv high latency2 msg<----"<<endl;
                           break;
                      case MAVLINK_MSG_ID_VIBRATION://241
                           mavlink_vibration_t vibration;
                           mavlink_msg_vibration_decode(&msg,&vibration);
                           cout<<"---->recv vibration msg<----"<<endl;
                           break;
                      case MAVLINK_MSG_ID_HOME_POSITION://242
                           mavlink_home_position_t home_position;
                           mavlink_msg_home_position_decode(&msg,&home_position);
                           cout<<"---->recv home position msg<----"<<endl;
                           break;
                      case MAVLINK_MSG_ID_SET_HOME_POSITION://243
                           mavlink_set_home_position_t set_home_position;
                           mavlink_msg_set_home_position_decode(&msg,&set_home_position);
                           cout<<"---->recv set home position msg<----"<<endl;
                           break;
                      case MAVLINK_MSG_ID_MESSAGE_INTERVAL://244
                           mavlink_message_interval_t message_interval;
                           mavlink_msg_message_interval_decode(&msg,&message_interval);
                           cout<<"---->recv message interval msg<----"<<endl;
                           break;
                      case MAVLINK_MSG_ID_EXTENDED_SYS_STATE://245
                           mavlink_extended_sys_state_t extended_sys_status;
                           mavlink_msg_extended_sys_state_decode(&msg,&extended_sys_status);
                           cout<<"---->recv extended sys state msg<----"<<endl;
                           break;
                      case MAVLINK_MSG_ID_ADSB_VEHICLE://246
                           mavlink_adsb_vehicle_t absb_vehicle;
                           mavlink_msg_adsb_vehicle_decode(&msg,&absb_vehicle);
                           cout<<"---->recv adsb vehicle msg<----"<<endl;
                           break;
                      case MAVLINK_MSG_ID_COLLISION://247
                           mavlink_collision_t collision;
                           mavlink_msg_collision_decode(&msg,&collision);
                           cout<<"---->recv collision msg<----"<<endl;
                           break;
                      case MAVLINK_MSG_ID_V2_EXTENSION://248
                           mavlink_v2_extension_t v2_extension;
                           mavlink_msg_v2_extension_decode(&msg,&v2_extension);
                           cout<<"---->recv v2 extension msg<----"<<endl;
                           break;
                      case MAVLINK_MSG_ID_MEMORY_VECT://249
                           mavlink_memory_vect_t memory_vect;
                           mavlink_msg_memory_vect_decode(&msg,&memory_vect);
                           cout<<"---->recv memory vect msg<----"<<endl;
                           break;
                      case MAVLINK_MSG_ID_DEBUG_VECT://250
                           mavlink_debug_vect_t debug_vect;
                           mavlink_msg_debug_vect_decode(&msg,&debug_vect);
                           cout<<"---->recv debug vect msg<----"<<endl;
                           break;
                      case MAVLINK_MSG_ID_NAMED_VALUE_FLOAT://251
                           mavlink_named_value_float_t named_value_float;
                           mavlink_msg_named_value_float_decode(&msg,&named_value_float);
                           cout<<"---->recv named value float msg<----"<<endl;
                           break;
                      case MAVLINK_MSG_ID_NAMED_VALUE_INT:// 252
                           mavlink_named_value_int_t named_value_int;
                           mavlink_msg_named_value_int_decode(&msg,&named_value_int);
                           cout<<"---->recv named value int<----"<<endl;
                           break;
                      case MAVLINK_MSG_ID_STATUSTEXT://253
                           mavlink_statustext_t statustext;
                           mavlink_msg_statustext_decode(&msg,&statustext);
                           cout<<"---->recv statustext msg<----"<<endl;
                           break;
                      case MAVLINK_MSG_ID_DEBUG://254
                           mavlink_debug_t debug;
                           mavlink_msg_debug_decode(&msg,&debug);
                           cout<<"---->recv debug msg<----"<<endl;
                           break;
              }
}

int main(int argc, char *argv[])
{
  ros::init(argc, argv, "unpack_cloud_data");
  ros::NodeHandle nh("~");
  nh.getParam("mavlink_msg_sub_topic",ros_sub_topic);

  nh.param("/ActuatorControlMsgName",ActuatorControlMsgName,ActuatorControlMsgName);
  nh.param("/AdsbSendMsgName",AdsbSendMsgName,AdsbSendMsgName);
  nh.param("/AdsbVehicleMsgName",AdsbVehicleMsgName,AdsbVehicleMsgName);
  nh.param("/AltitudeMsgName",AltitudeMsgName,AltitudeMsgName);
  nh.param("/CamImuStampMsgName",CamImuStampMsgName,CamImuStampMsgName);
  nh.param("/CompanionProcessStatusMsgName",CompanionProcessStatusMsgName,CompanionProcessStatusMsgName);
  nh.param("/DebugValueDebugMsgName",DebugValueDebugMsgName,DebugValueDebugMsgName);
  nh.param("/DebugValueDebugVectorMsgName",DebugValueDebugVectorMsgName,DebugValueDebugVectorMsgName);
  nh.param("/DebugValueNamedValueFloatMsgName",DebugValueNamedValueFloatMsgName,DebugValueNamedValueFloatMsgName);
  nh.param("/DebugValueNamedValueIntMsgName",DebugValueNamedValueIntMsgName,DebugValueNamedValueIntMsgName);
  nh.param("/DebugValueSendMsgName",DebugValueSendMsgName,DebugValueSendMsgName);
  nh.param("/EstimatorStatusMsgName",EstimatorStatusMsgName,EstimatorStatusMsgName);
  nh.param("/ExtendedStateMsgName",ExtendedStateMsgName,ExtendedStateMsgName);
  nh.param("/FakeGpsMocapTfMsgName",FakeGpsMocapTfMsgName,FakeGpsMocapTfMsgName);
  nh.param("/GlobalPositionCompassHdgMsgName",GlobalPositionCompassHdgMsgName,GlobalPositionCompassHdgMsgName);
  nh.param("/GlobalPositionGlobalMsgName",GlobalPositionGlobalMsgName,GlobalPositionGlobalMsgName);
  nh.param("/GlobalPositionGpLpOffsetMsgName",GlobalPositionGpLpOffsetMsgName,GlobalPositionGpLpOffsetMsgName);
  nh.param("/GlobalPositionGpOriginMsgName",GlobalPositionGpOriginMsgName,GlobalPositionGpOriginMsgName);
  nh.param("/GlobalPositionHomeMsgName",GlobalPositionHomeMsgName,GlobalPositionHomeMsgName);
  nh.param("/GlobalPositionLocalMsgName",GlobalPositionLocalMsgName,GlobalPositionLocalMsgName);
  nh.param("/GlobalPositionRawFixMsgName",GlobalPositionRawFixMsgName,GlobalPositionRawFixMsgName);
  nh.param("/GlobalPositionRawGpsVelMsgName",GlobalPositionRawGpsVelMsgName,GlobalPositionRawGpsVelMsgName);
  nh.param("/GlobalPositionRawSatellitesMsgName",GlobalPositionRawSatellitesMsgName,GlobalPositionRawSatellitesMsgName);
  nh.param("/GlobalPositionRelAltMsgName",GlobalPositionRelAltMsgName,GlobalPositionRelAltMsgName);
  nh.param("/GlobalPositionSetGpOriginMsgName",GlobalPositionSetGpOriginMsgName,GlobalPositionSetGpOriginMsgName);
  nh.param("/GpsRtkSendRtcmMsgName",GpsRtkSendRtcmMsgName,GpsRtkSendRtcmMsgName);
  nh.param("/HilActuatorControlsMsgName",HilActuatorControlsMsgName,HilActuatorControlsMsgName);
  nh.param("/HilControlsMsgName",HilControlsMsgName,HilControlsMsgName);
  nh.param("/HilGpsMsgName",HilGpsMsgName,HilGpsMsgName);
  nh.param("/HilImuNedMsgName",HilImuNedMsgName,HilImuNedMsgName);
  nh.param("/HilOpticalFlowMsgName",HilOpticalFlowMsgName,HilOpticalFlowMsgName);
  nh.param("/HilRcInputsMsgName",HilRcInputsMsgName,HilRcInputsMsgName);
  nh.param("/HilStateMsgName",HilStateMsgName,HilStateMsgName);
  nh.param("/HomePositionSetMsgName",HomePositionSetMsgName,HomePositionSetMsgName);
  nh.param("/ImuDataMsgName",ImuDataMsgName,ImuDataMsgName);
  nh.param("/ImuDataRawMsgName",ImuDataRawMsgName,ImuDataRawMsgName);
  nh.param("/ImuDiffPressureMsgName",ImuDiffPressureMsgName,ImuDiffPressureMsgName);
  nh.param("/ImuMagMsgName",ImuMagMsgName,ImuMagMsgName);
  nh.param("/ImuStaticPressureMsgName",ImuStaticPressureMsgName,ImuStaticPressureMsgName);
  nh.param("/ImuTemperatureBaroMsgName",ImuTemperatureBaroMsgName,ImuTemperatureBaroMsgName);
  nh.param("/ImuTemperatureImuMsgName",ImuTemperatureImuMsgName,ImuTemperatureImuMsgName);
  nh.param("/LandingTargetLtMarkerMsgName",LandingTargetLtMarkerMsgName,LandingTargetLtMarkerMsgName);
  nh.param("/LandingTargetPoseMsgName",LandingTargetPoseMsgName,LandingTargetPoseMsgName);
  nh.param("/LandingTargetPoseInMsgName",LandingTargetPoseInMsgName,LandingTargetPoseInMsgName);
  nh.param("/LocalPositionAccelMsgName",LocalPositionAccelMsgName,LocalPositionAccelMsgName);
  nh.param("/LocalPositionOdomMsgName",LocalPositionOdomMsgName,LocalPositionOdomMsgName);
  nh.param("/LocalPositionPoseMsgName",LocalPositionPoseMsgName,LocalPositionPoseMsgName);
  nh.param("/LocalPositionPoseCovMsgName",LocalPositionPoseCovMsgName,LocalPositionPoseCovMsgName);
  nh.param("/LocalPositionPoseVelocityBodyMsgName",LocalPositionPoseVelocityBodyMsgName,LocalPositionPoseVelocityBodyMsgName);
  nh.param("/LocalPositionPoseVelocityBodyCovMsgName",LocalPositionPoseVelocityBodyCovMsgName,LocalPositionPoseVelocityBodyCovMsgName);
  nh.param("/LocalPositionPoseVelocityLocalMsgName",LocalPositionPoseVelocityLocalMsgName,LocalPositionPoseVelocityLocalMsgName);
  nh.param("/LogTransferRawLogDataMsgName",LogTransferRawLogDataMsgName,LogTransferRawLogDataMsgName);
  nh.param("/LogTransferRawLogEntryMsgName",LogTransferRawLogEntryMsgName,LogTransferRawLogEntryMsgName);
  nh.param("/ManualControlControlMsgName",ManualControlControlMsgName,ManualControlControlMsgName);
  nh.param("/ManualControlSendMsgName",ManualControlSendMsgName,ManualControlSendMsgName);
  nh.param("/MissionReachedMsgName",MissionReachedMsgName,MissionReachedMsgName);
  nh.param("/MissionWaypointsMsgName",MissionWaypointsMsgName,MissionWaypointsMsgName);
  nh.param("/MocapPoseMsgName",MocapPoseMsgName,MocapPoseMsgName);
  nh.param("/MountControlCommandMsgName",MountControlCommandMsgName,MountControlCommandMsgName);
  nh.param("/MountControlOrientationMsgName",MountControlOrientationMsgName,MountControlOrientationMsgName);
  nh.param("/ObstacleSendMsgName",ObstacleSendMsgName,ObstacleSendMsgName);
  nh.param("/OdometryInMsgName",OdometryInMsgName,OdometryInMsgName);
  nh.param("/OdometryOutMsgName",OdometryOutMsgName,OdometryOutMsgName);
  nh.param("/OnboardComputerStatusMsgName",OnboardComputerStatusMsgName,OnboardComputerStatusMsgName);
  nh.param("/ParamParamValueMsgName",ParamParamValueMsgName,ParamParamValueMsgName);
  nh.param("/Px4flowGroundDistanceMsgName",Px4flowGroundDistanceMsgName,Px4flowGroundDistanceMsgName);
  nh.param("/Px4flowRawOpticalFlowRadMsgName",Px4flowRawOpticalFlowRadMsgName,Px4flowRawOpticalFlowRadMsgName);
  nh.param("/Px4flowRawSendMsgName",Px4flowRawSendMsgName,Px4flowRawSendMsgName);
  nh.param("/Px4flowTemperatureMsgName",Px4flowTemperatureMsgName,Px4flowTemperatureMsgName);
  nh.param("/RadioStatusMsgName",RadioStatusMsgName,RadioStatusMsgName);
  nh.param("/RcInMsgName",RcInMsgName,RcInMsgName);
  nh.param("/RcOutMsgName",RcOutMsgName,RcOutMsgName);
  nh.param("/RcOverrideMsgName",RcOverrideMsgName,RcOverrideMsgName);
  nh.param("/SetpointAccelAccelMsgName",SetpointAccelAccelMsgName,SetpointAccelAccelMsgName);
  nh.param("/SetpointAttitudeCmdVelMsgName",SetpointAttitudeCmdVelMsgName,SetpointAttitudeCmdVelMsgName);
  nh.param("/SetpointAttitudeThrustMsgName",SetpointAttitudeThrustMsgName,SetpointAttitudeThrustMsgName);
  nh.param("/SetpointPositionGlobalToLocalMsgName",SetpointPositionGlobalToLocalMsgName,SetpointPositionGlobalToLocalMsgName);
  nh.param("/SetpointPositionGlobalMsgName",SetpointPositionGlobalMsgName,SetpointPositionGlobalMsgName);
  nh.param("/SetpointPositionLocalMsgName",SetpointPositionLocalMsgName,SetpointPositionLocalMsgName);
  nh.param("/SetpointRawAttitudeMsgName",SetpointRawAttitudeMsgName,SetpointRawAttitudeMsgName);
  nh.param("/SetpointRawGlobalMsgName",SetpointRawGlobalMsgName,SetpointRawGlobalMsgName);
  nh.param("/SetpointRawLocalMsgName",SetpointRawLocalMsgName,SetpointRawLocalMsgName);
  nh.param("/SetpointRawTargetAttitudeMsgName",SetpointRawTargetAttitudeMsgName,SetpointRawTargetAttitudeMsgName);
  nh.param("/SetpointRawTargetGlobalMsgName",SetpointRawTargetGlobalMsgName,SetpointRawTargetGlobalMsgName);
  nh.param("/SetpointRawTargetLocalMsgName",SetpointRawTargetLocalMsgName,SetpointRawTargetLocalMsgName);
  nh.param("/SetpointTrajectoryDesiredMsgName",SetpointTrajectoryDesiredMsgName,SetpointTrajectoryDesiredMsgName);
  nh.param("/SetpointTrajectoryLocalMsgName",SetpointTrajectoryLocalMsgName,SetpointTrajectoryLocalMsgName);
  nh.param("/SetpointVelocityCmdVelMsgName",SetpointVelocityCmdVelMsgName,SetpointVelocityCmdVelMsgName);
  nh.param("/SetpointVelocityCmdVelUnstampedMsName",SetpointVelocityCmdVelUnstampedMsName,SetpointVelocityCmdVelUnstampedMsName);
  nh.param("/StateMsgName",StateMsgName,StateMsgName);
  nh.param("/StatustextRecvMsgName",StatustextRecvMsgName,StatustextRecvMsgName);
  nh.param("/StatustextSendMsgName",StatustextSendMsgName,StatustextSendMsgName);
  nh.param("/TargetActuatorControlMsgName",TargetActuatorControlMsgName,TargetActuatorControlMsgName);
  nh.param("/TimeReferenceMsgName",TimeReferenceMsgName,TimeReferenceMsgName);
  nh.param("/TimesyncStatusMsgName",TimesyncStatusMsgName,TimesyncStatusMsgName);
  nh.param("/TrajectoryDesiredMsgName",TrajectoryDesiredMsgName,TrajectoryDesiredMsgName);
  nh.param("/TrajectoryGeneratedMsgName",TrajectoryGeneratedMsgName,TrajectoryGeneratedMsgName);
  nh.param("/VfrHudMsgName",VfrHudMsgName,VfrHudMsgName);
  nh.param("/VisionPosePoseMsgName",VisionPosePoseMsgName,VisionPosePoseMsgName);
  nh.param("/VisionPosePoseCovMsgName",VisionPosePoseCovMsgName,VisionPosePoseCovMsgName);
  nh.param("/VisionSpeedSpeedTwistCovMsgName",VisionSpeedSpeedTwistCovMsgName,VisionSpeedSpeedTwistCovMsgName);
  nh.param("/WindEstimationMsgName",WindEstimationMsgName,WindEstimationMsgName);

  AdsbVehiclePub = nh.advertise<mavros_msgs::ADSBVehicle>(AdsbVehicleMsgName,10);
  AltitudePub = nh.advertise<mavros_msgs::Altitude>(AltitudeMsgName,10);
  CamImuStampPub = nh.advertise<mavros_msgs::CamIMUStamp>(CamImuStampMsgName,10);
  DebugValueDebugPub = nh.advertise<mavros_msgs::DebugValue>(DebugValueDebugMsgName,10);
  DebugValueDebugVectorPub = nh.advertise<mavros_msgs::DebugValue>(DebugValueDebugVectorMsgName,10);
  DebugValueNameValuedFloatPub = nh.advertise<mavros_msgs::DebugValue>(DebugValueNamedValueFloatMsgName,10);
  DebugValueNameValuedIntPub = nh.advertise<mavros_msgs::DebugValue>(DebugValueNamedValueIntMsgName,10);
  EstimatorStatusPub = nh.advertise<mavros_msgs::EstimatorStatus>(EstimatorStatusMsgName,10);
  ExtendedStatePub = nh.advertise<mavros_msgs::ExtendedState>(ExtendedStateMsgName,10);
  GlobalPositionCompassHdgPub = nh.advertise<std_msgs::Float64>(GlobalPositionCompassHdgMsgName,10);
  GlobalPositionGlobalPub = nh.advertise<sensor_msgs::NavSatFix>(GlobalPositionGlobalMsgName,10);
  GlobalPositionGpLpOffsetPub = nh.advertise<geometry_msgs::PoseStamped>(GlobalPositionGpLpOffsetMsgName,10);
  GlobalPositionGpOriginPub = nh.advertise<geographic_msgs::GeoPointStamped>(GlobalPositionGpOriginMsgName,10);
  GlobalPositionLocalPub = nh.advertise<nav_msgs::Odometry>(GlobalPositionLocalMsgName,10);
  GlobalPositionRawFixPub = nh.advertise<sensor_msgs::NavSatFix>(GlobalPositionRawFixMsgName,10);
  GlobalPositionRawGpsVelPub = nh.advertise<geometry_msgs::TwistStamped>(GlobalPositionRawGpsVelMsgName,10);
  GlobalPositionRawSatellitesPub = nh.advertise<std_msgs::UInt32>(GlobalPositionRawSatellitesMsgName,10);
  GlobalPositionRelAltPub = nh.advertise<std_msgs::Float64>(GlobalPositionRelAltMsgName,10);
  HilActuatorControlsPub = nh.advertise<mavros_msgs::HilActuatorControls>(HilActuatorControlsMsgName,10);
  HilControlsPub = nh.advertise<mavros_msgs::HilControls>(HilControlsMsgName,10);
  HomePositionHomePub = nh.advertise<mavros_msgs::HomePosition>(HomePositionSetMsgName,10);
  ImuDataPub = nh.advertise<sensor_msgs::Imu>(ImuDataMsgName,10);
  ImuDataRawPub = nh.advertise<sensor_msgs::Imu>(ImuDataRawMsgName,10);
  ImuDiffPressurePub = nh.advertise<sensor_msgs::FluidPressure>(ImuDiffPressureMsgName,10);
  ImuMagPub = nh.advertise<sensor_msgs::MagneticField>(ImuMagMsgName,10);
  ImuStaticPressurePub = nh.advertise<sensor_msgs::FluidPressure>(ImuStaticPressureMsgName,10);
  ImuTemperatureBaroPub = nh.advertise<sensor_msgs::Temperature>(ImuTemperatureBaroMsgName,10);
  ImuTemperatureImuPub = nh.advertise<sensor_msgs::Temperature>(ImuTemperatureImuMsgName,10);
  LandingTargetLtMarkerPub = nh.advertise<geometry_msgs::Vector3Stamped>(LandingTargetLtMarkerMsgName,10);
  LandingTargetPoseInPub = nh.advertise<geometry_msgs::PoseStamped>(LandingTargetPoseInMsgName,10);
  LocalPositionAccelPub = nh.advertise<geometry_msgs::AccelWithCovarianceStamped>(LocalPositionAccelMsgName,10);
  LocalPositionOdomPub = nh.advertise<nav_msgs::Odometry>(LocalPositionOdomMsgName,10);
  LocalPositionPosePub = nh.advertise<geometry_msgs::PoseStamped>(LocalPositionPoseMsgName,10);
  LocalPositionPoseCovPub = nh.advertise<geometry_msgs::PoseWithCovarianceStamped>(LocalPositionPoseCovMsgName,10);
  LocalPositionPoseVelocityBodyPub = nh.advertise<geometry_msgs::TwistStamped>(LocalPositionPoseVelocityBodyMsgName,10);
  LocalPositionPoseVelocityBodyCovPub = nh.advertise<geometry_msgs::TwistWithCovarianceStamped>(LocalPositionPoseVelocityBodyCovMsgName,10);
  LocalPositionPoseVelocityLocalPub = nh.advertise<geometry_msgs::TwistStamped>(LocalPositionPoseVelocityLocalMsgName,10);
  LogTransferRawLogDataPub = nh.advertise<mavros_msgs::LogData>(LogTransferRawLogDataMsgName,10);
  LogTransferRawLogEntryPub = nh.advertise<mavros_msgs::LogEntry>(LogTransferRawLogEntryMsgName,10);
  ManualControlControlPub = nh.advertise<mavros_msgs::ManualControl>(ManualControlControlMsgName,10);
  MissionReachedPub = nh.advertise<mavros_msgs::WaypointReached>(MissionReachedMsgName,10);
  MissionWaypointsPub = nh.advertise<mavros_msgs::WaypointList>(MissionWaypointsMsgName,10);
  MountControlOrientationPub = nh.advertise<geometry_msgs::Quaternion>(MountControlOrientationMsgName,10);
  OdometryInPub = nh.advertise<nav_msgs::Odometry>(OdometryInMsgName,10);
  ParamParamValuePub = nh.advertise<mavros_msgs::Param>(ParamParamValueMsgName,10);
  Px4flowGroundDistancePub = nh.advertise<sensor_msgs::Range>(Px4flowGroundDistanceMsgName,10);
  Px4flowRawOpticalFlowRadPub = nh.advertise<mavros_msgs::OpticalFlowRad>(Px4flowRawOpticalFlowRadMsgName,10);
  Px4flowTemperaturePub = nh.advertise<sensor_msgs::Temperature>(Px4flowTemperatureMsgName,10);
  RadioStatusPub = nh.advertise<mavros_msgs::RadioStatus>(RadioStatusMsgName,10);
  RcInPub = nh.advertise<mavros_msgs::RCIn>(RcInMsgName,10);
  RcOutPub = nh.advertise<mavros_msgs::RCOut>(RcOutMsgName,10);
  SetpointRawTargetAttitudePub = nh.advertise<mavros_msgs::AttitudeTarget>(SetpointRawAttitudeMsgName,10);
  SetpointRawTargetGlobalPub = nh.advertise<mavros_msgs::GlobalPositionTarget>(SetpointRawTargetGlobalMsgName,10);
  SetpointRawTargetLocalPub = nh.advertise<mavros_msgs::PositionTarget>(SetpointRawTargetLocalMsgName,10);
  SetpointTrajectoryDesiredPub = nh.advertise<nav_msgs::Path>(SetpointTrajectoryDesiredMsgName,10);
  StatePub = nh.advertise<mavros_msgs::State>(StateMsgName,10);
  StatustextRecvPub = nh.advertise<mavros_msgs::StatusText>(StatustextRecvMsgName,10);
  TargetActuatorControlPub = nh.advertise<mavros_msgs::ActuatorControl>(TargetActuatorControlMsgName,10);
  TimeReferencePub = nh.advertise<sensor_msgs::TimeReference>(TimeReferenceMsgName,10);
  TimesyncStatusPub = nh.advertise<mavros_msgs::TimesyncStatus>(TimesyncStatusMsgName,10);
  TrajectoryDesiredPub = nh.advertise<mavros_msgs::Trajectory>(TrajectoryDesiredMsgName,10);
  VfrHudPub = nh.advertise<mavros_msgs::VFR_HUD>(VfrHudMsgName,10);
  WindEstimationPub = nh.advertise<geometry_msgs::TwistWithCovarianceStamped>(WindEstimationMsgName,10);

  iot_msg_sub = nh.subscribe(ros_sub_topic, 100, iot_msg_ros_sub);

  ros::spin();
  return 0;

}

