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
#ifndef UNPACK_CLOUD_DATA_H
#define UNPACK_CLOUD_DATA_H
#include "ros/ros.h"
#include "geometry_msgs/TransformStamped.h"
#include "geometry_msgs/PoseStamped.h"
#include "geometry_msgs/PoseWithCovarianceStamped.h"
#include "geometry_msgs/TwistStamped.h"
#include "geometry_msgs/TwistWithCovarianceStamped.h"
#include "geometry_msgs/Vector3Stamped.h"
#include "geometry_msgs/AccelWithCovarianceStamped.h"
#include "geometry_msgs/Quaternion.h"
#include "std_msgs/Float64.h"
#include "std_msgs/UInt32.h"
#include "sensor_msgs/NavSatFix.h"
#include "sensor_msgs/Imu.h"
#include "sensor_msgs/FluidPressure.h"
#include "sensor_msgs/MagneticField.h"
#include "sensor_msgs/Temperature.h"
#include "sensor_msgs/LaserScan.h"
#include "sensor_msgs/Range.h"
#include "sensor_msgs/TimeReference.h"
#include "trajectory_msgs/MultiDOFJointTrajectory.h"
#include "geographic_msgs/GeoPointStamped.h"
#include "nav_msgs/Odometry.h"
#include "nav_msgs/Path.h"
#include "iostream"
#include "../include/mavros_msgs/Mavlink.h"
#include "../include/cloud_connection/mavros_msgs/ActuatorControl.h"
#include "../include/cloud_connection/mavros_msgs/ADSBVehicle.h"
#include "../include/cloud_connection/mavros_msgs/Altitude.h"
#include "../include/cloud_connection/mavros_msgs/CamIMUStamp.h"
#include "../include/cloud_connection/mavros_msgs/CompanionProcessStatus.h"
#include "../include/cloud_connection/mavros_msgs/DebugValue.h"
#include "../include/cloud_connection/mavros_msgs/EstimatorStatus.h"
#include "../include/cloud_connection/mavros_msgs/ExtendedState.h"
#include "../include/cloud_connection/mavros_msgs/HomePosition.h"
#include "../include/cloud_connection/mavros_msgs/RTCM.h"
#include "../include/cloud_connection/mavros_msgs/HilActuatorControls.h"
#include "../include/cloud_connection/mavros_msgs/HilControls.h"
#include "../include/cloud_connection/mavros_msgs/HilGPS.h"
#include "../include/cloud_connection/mavros_msgs/HilSensor.h"
#include "../include/cloud_connection/mavros_msgs/OpticalFlowRad.h"
#include "../include/cloud_connection/mavros_msgs/RCIn.h"
#include "../include/cloud_connection/mavros_msgs/HilStateQuaternion.h"
#include "../include/cloud_connection/mavros_msgs/HomePosition.h"
#include "../include/cloud_connection/mavros_msgs/LogData.h"
#include "../include/cloud_connection/mavros_msgs/LogEntry.h"
#include "../include/cloud_connection/mavros_msgs/ManualControl.h"
#include "../include/cloud_connection/mavros_msgs/WaypointReached.h"
#include "../include/cloud_connection/mavros_msgs/WaypointList.h"
#include "../include/cloud_connection/mavros_msgs/MountControl.h"
#include "../include/cloud_connection/mavros_msgs/OnboardComputerStatus.h"
#include "../include/cloud_connection/mavros_msgs/Param.h"
#include "../include/cloud_connection/mavros_msgs/RadioStatus.h"
#include "../include/cloud_connection/mavros_msgs/RCOut.h"
#include "../include/cloud_connection/mavros_msgs/OverrideRCIn.h"
#include "../include/cloud_connection/mavros_msgs/Thrust.h"
#include "../include/cloud_connection/mavros_msgs/AttitudeTarget.h"
#include "../include/cloud_connection/mavros_msgs/GlobalPositionTarget.h"
#include "../include/cloud_connection/mavros_msgs/PositionTarget.h"
#include "../include/cloud_connection/mavros_msgs/State.h"
#include "../include/cloud_connection/mavros_msgs/StatusText.h"
#include "../include/cloud_connection/mavros_msgs/TimesyncStatus.h"
#include "../include/cloud_connection/mavros_msgs/Trajectory.h"
#include "../include/cloud_connection/mavros_msgs/VFR_HUD.h"
#include <../include/cloud_connection/mavlink/v1.0/common/mavlink.h>
using namespace std;
//------> ros subscriber and call back function<------
ros::Subscriber ActuatorControlSub;
void ActuatorControlSubCallback(const mavros_msgs::ActuatorControl::ConstPtr& msg);
ros::Subscriber AdsbSendSub;
void AdsbSendSubCallback(const mavros_msgs::ADSBVehicle::ConstPtr& msg);
ros::Subscriber CompanionProcessStatusSub;
void CompanionProcessStatusSubCallback(const mavros_msgs::CompanionProcessStatus::ConstPtr& msg);
ros::Subscriber DebugValueSendSub;
void DebugValueSendSubCallback(const mavros_msgs::DebugValue::ConstPtr& msg);
ros::Subscriber FakeGpsMocapTfSub;
void FakeGpsMocapTfSubCallback(const geometry_msgs::TransformStamped::ConstPtr& msg);
ros::Subscriber GlobalPositionGlobalSub;
void GlobalPositionGlobalSubCallback(const sensor_msgs::NavSatFix::ConstPtr& msg );
ros::Subscriber GlobalPositionHomeSub;
void GlobalPositionHomeSubCallback(const mavros_msgs::HomePosition::ConstPtr& msg);
ros::Subscriber GlobalPositionSetGpOriginSub;
void GlobalPositionSetGpOriginSubCallback(const geographic_msgs::GeoPointStamped::ConstPtr& msg);
ros::Subscriber GpsRtkSendRtcmSub;
void GpsRtkSendRtcmSubCallback(const mavros_msgs::RTCM::ConstPtr& msg);
ros::Subscriber HilGpsSub;
void HilGpsSubCallback(const mavros_msgs::HilGPS::ConstPtr& msg);
ros::Subscriber HilImuNedSub;
void HilImuNedSubCallback(const mavros_msgs::HilSensor::ConstPtr& msg);
ros::Subscriber HilOpticalFlowSub;
void HilOpticalFlowSubCallback(const mavros_msgs::OpticalFlowRad& msg);
ros::Subscriber HilRcInputsSub;
void HilRcInputsSubCallback(const mavros_msgs::RCIn::ConstPtr& msg);
ros::Subscriber HilStateSub;
void HilStateSubCallback(const mavros_msgs::HilStateQuaternion::ConstPtr& msg);
ros::Subscriber HomePositionSetSub;
void HomePositionSetSubCallback(const mavros_msgs::HomePosition::ConstPtr& msg);
ros::Subscriber LandingTargetPoseSub;
void LandingTargetPoseSubCallback(const geometry_msgs::PoseStamped::ConstPtr& msg);
ros::Subscriber LocalPositionPoseSub;
void LocalPositionPoseSubCallback(const geometry_msgs::PoseStamped::ConstPtr& msg);
ros::Subscriber ManualControlSendSub;
void ManualControlSendSubCallback(const mavros_msgs::ManualControl::ConstPtr& msg);
ros::Subscriber MocapPoseSub;
void MocapPoseSubCallback(const geometry_msgs::PoseStamped::ConstPtr& msg);
ros::Subscriber MountControlCommandSub;
void MountControlCommandSubCallback(const mavros_msgs::MountControl::ConstPtr& msg);
ros::Subscriber ObstacleSendSub;
void ObstacleSendSubCallback(const sensor_msgs::LaserScan::ConstPtr& msg);
ros::Subscriber OdometryOutSub;
void OdometryOutSubCallback(const nav_msgs::Odometry::ConstPtr& msg);
ros::Subscriber OnboardComputerStatusSub;
void OnboardComputerStatusSubCallback(const mavros_msgs::OnboardComputerStatus::ConstPtr& msg);
ros::Subscriber Px4flowRawSendSub;
void Px4flowRawSendSubCallback(const mavros_msgs::OpticalFlowRad::ConstPtr& msg);
ros::Subscriber RcOverrideSub;
void RcOverrideSubCallback(const mavros_msgs::OverrideRCIn::ConstPtr& msg);
ros::Subscriber SetpointAccelAccelSub;
void SetpointAccelAccelSubCallback(const geometry_msgs::Vector3Stamped::ConstPtr& msg);
ros::Subscriber SetpointAttitudeCmdVelSub;
void SetpointAttitudeCmdVelSubCallback(const geometry_msgs::TwistStamped::ConstPtr& msg);
ros::Subscriber SetpointAttitudeThrustSub;
void SetpointAttitudeThrustSubCallback(const mavros_msgs::Thrust::ConstPtr& msg);
ros::Subscriber SetpointPositionGlobalSub;
void SetpointPositionGlobalSubCallback(const geographic_msgs::GeoPointStamped::ConstPtr& msg);
ros::Subscriber SetpointPositionGlobalToLocalSub;
void SetpointPositionGlobalToLocalSubCallback(const geographic_msgs::GeoPointStamped::ConstPtr& msg);
ros::Subscriber SetpointPositionLocalSub;
void SetpointPositionLocalSubCallback(const geometry_msgs::PoseStamped::ConstPtr& msg);
ros::Subscriber SetpointRawAttitudeSub;
void SetpointRawAttitudeSubCallback(const mavros_msgs::AttitudeTarget::ConstPtr& msg);
ros::Subscriber SetpointRawGlobalSub;
void SetpointRawGlobalSubCallback(const mavros_msgs::GlobalPositionTarget::ConstPtr& msg);
ros::Subscriber SetpointRawLocalSub;
void SetpointRawLocalSubCallback(const mavros_msgs::PositionTarget::ConstPtr& msg);
ros::Subscriber SetpointTrajectoryLocalSub;
void SetpointTrajectoryLocalSubCallback(const trajectory_msgs::MultiDOFJointTrajectory::ConstPtr& msg);
ros::Subscriber SetpointVelocityCmdVelSub;
void SetpointVelocityCmdVelSubCallback(const geometry_msgs::TwistStamped::ConstPtr& msg);
ros::Subscriber SetpointVelocityCmdVelUnstampedSub;
void SetpointVelocityCmdVelUnstampedSubCallback(const geometry_msgs::Twist::ConstPtr& msg);
ros::Subscriber StatustextSendSub;
void StatustextSendSubCallback(const mavros_msgs::StatusText::ConstPtr& msg);
ros::Subscriber TrajectoryGeneratedSub;
void TrajectoryGeneratedSubCallback(const mavros_msgs::Trajectory::ConstPtr& msg);
ros::Subscriber VisionPosePoseSub;
void VisionPosePoseSubCallback(const geometry_msgs::PoseStamped::ConstPtr& msg);
ros::Subscriber VisionPosePoseCovSub;
void VisionPosePoseCovSubCallback(const geometry_msgs::PoseWithCovarianceStamped::ConstPtr& msg);
ros::Subscriber VisionSpeedSpeedTwistCovSub;
void VisionSpeedSpeedTwistCovSubCallback(const geometry_msgs::TwistWithCovarianceStamped::ConstPtr& msg);

//------> ros publisher <------

ros::Publisher AdsbVehiclePub;
ros::Publisher AltitudePub;
ros::Publisher CamImuStampPub;
ros::Publisher DebugValueDebugPub;
ros::Publisher DebugValueDebugVectorPub;
ros::Publisher DebugValueNameValuedFloatPub;
ros::Publisher DebugValueNameValuedIntPub;
ros::Publisher EstimatorStatusPub;
ros::Publisher ExtendedStatePub;
ros::Publisher GlobalPositionCompassHdgPub;
ros::Publisher GlobalPositionGlobalPub;
ros::Publisher GlobalPositionGpLpOffsetPub;
ros::Publisher GlobalPositionGpOriginPub;
ros::Publisher GlobalPositionLocalPub;
ros::Publisher GlobalPositionRawFixPub;
ros::Publisher GlobalPositionRawGpsVelPub;
ros::Publisher GlobalPositionRawSatellitesPub;
ros::Publisher GlobalPositionRelAltPub;
ros::Publisher HilActuatorControlsPub;
ros::Publisher HilControlsPub;
ros::Publisher HomePositionHomePub;
ros::Publisher ImuDataPub;
ros::Publisher ImuDataRawPub;
ros::Publisher ImuDiffPressurePub;
ros::Publisher ImuMagPub;
ros::Publisher ImuStaticPressurePub;
ros::Publisher ImuTemperatureBaroPub;
ros::Publisher ImuTemperatureImuPub;
ros::Publisher LandingTargetLtMarkerPub;
ros::Publisher LandingTargetPoseInPub;
ros::Publisher LocalPositionAccelPub;
ros::Publisher LocalPositionOdomPub;
ros::Publisher LocalPositionPosePub;
ros::Publisher LocalPositionPoseCovPub;
ros::Publisher LocalPositionPoseVelocityBodyPub;
ros::Publisher LocalPositionPoseVelocityBodyCovPub;
ros::Publisher LocalPositionPoseVelocityLocalPub;
ros::Publisher LogTransferRawLogDataPub;
ros::Publisher LogTransferRawLogEntryPub;
ros::Publisher ManualControlControlPub;
ros::Publisher MissionReachedPub;
ros::Publisher MissionWaypointsPub;
ros::Publisher MountControlOrientationPub;
ros::Publisher OdometryInPub;
ros::Publisher ParamParamValuePub;
ros::Publisher Px4flowGroundDistancePub;
ros::Publisher Px4flowRawOpticalFlowRadPub;
ros::Publisher Px4flowTemperaturePub;
ros::Publisher RadioStatusPub;
ros::Publisher RcInPub;
ros::Publisher RcOutPub;
ros::Publisher SetpointRawTargetAttitudePub;
ros::Publisher SetpointRawTargetGlobalPub;
ros::Publisher SetpointRawTargetLocalPub;
ros::Publisher SetpointTrajectoryDesiredPub;
ros::Publisher StatePub;
ros::Publisher StatustextRecvPub;
ros::Publisher TargetActuatorControlPub;
ros::Publisher TimeReferencePub;
ros::Publisher TimesyncStatusPub;
ros::Publisher TrajectoryDesiredPub;
ros::Publisher VfrHudPub;
ros::Publisher WindEstimationPub;

//------> ros topic <------
geometry_msgs::TransformStamped FakeGpsMocapTfMsg;
geometry_msgs::PoseStamped GlobalPositionGpLpOffsetMsg;
geometry_msgs::PoseStamped LandingTargetPoseMsg;
geometry_msgs::PoseStamped LandingTargetPoseInMsg;
geometry_msgs::PoseStamped LocalPositionPoseMsg;
geometry_msgs::PoseStamped MocapPoseMsg;
geometry_msgs::Quaternion MountControlOrientationMsg;
geometry_msgs::TwistStamped GlobalPositionRawGpsVelMsg;
geometry_msgs::TwistStamped LocalPositionPoseVelocityBodyMsg;
geometry_msgs::TwistStamped LocalPositionPoseVelocityLocalMsg;
geometry_msgs::TwistWithCovarianceStamped LocalPositionPoseVelocityBodyCovMsg;
geometry_msgs::Vector3Stamped LandingTargetLtMarkerMsg;
geometry_msgs::Vector3Stamped SetpointAccelAccelMsg;
geometry_msgs::TwistStamped SetpointAttitudeCmdVelMsg;
geometry_msgs::PoseStamped SetpointPositionLocalMsg;
geometry_msgs::AccelWithCovarianceStamped LocalPositionAccelMsg;
geometry_msgs::PoseWithCovarianceStamped LocalPositionPoseCovMsg;
geometry_msgs::TwistStamped SetpointVelocityCmdVelMsg;
geometry_msgs::Twist SetpointVelocityCmdVelUnstampedMsg;
geometry_msgs::PoseStamped VisionPosePoseMsg;
geometry_msgs::PoseWithCovarianceStamped VisionPosePoseCovMsg;
geometry_msgs::TwistWithCovarianceStamped VisionSpeedSpeedTwistCovMsg;
geometry_msgs::TwistWithCovarianceStamped WindEstimationMsg;
std_msgs::Float64 GlobalPositionCompassHdgMsg;
std_msgs::Float64 GlobalPositionRelAltMsg;
std_msgs::UInt32 GlobalPositionRawSatellitesMsg;
sensor_msgs::NavSatFix GlobalPositionGlobalMsg;
sensor_msgs::NavSatFix GlobalPositionRawFixMsg;
sensor_msgs::Imu ImuDataMsg;
sensor_msgs::Imu ImuDataRawMsg;
sensor_msgs::FluidPressure ImuDiffPressureMsg;
sensor_msgs::FluidPressure ImuStaticPressureMsg;
sensor_msgs::MagneticField ImuMagMsg;
sensor_msgs::Temperature ImuTemperatureBaroMsg;
sensor_msgs::Temperature ImuTemperatureImuMsg;
sensor_msgs::LaserScan ObstacleSendMsg;
sensor_msgs::Range Px4flowGroundDistanceMsg;
sensor_msgs::Temperature Px4flowTemperatureMsg;
sensor_msgs::TimeReference TimeReferenceMsg;
geographic_msgs::GeoPointStamped GlobalPositionGpOriginMsg;
geographic_msgs::GeoPointStamped GlobalPositionSetGpOriginMsg;
geographic_msgs::GeoPointStamped SetpointPositionGlobalMsg;
geographic_msgs::GeoPointStamped SetpointPositionGlobalToLocalMsg;
nav_msgs::Odometry GlobalPositionLocalMsg;
nav_msgs::Odometry LocalPositionOdomMsg;
nav_msgs::Odometry OdometryInMsg;
nav_msgs::Odometry OdometryOutMsg;
nav_msgs::Path SetpointTrajectoryDesiredMsg;
trajectory_msgs::MultiDOFJointTrajectory SetpointTrajectoryLocalMsg;
mavros_msgs::ActuatorControl ActuatorControlMsg;
mavros_msgs::ADSBVehicle AdsbSendMsg;
mavros_msgs::ADSBVehicle AdsbVehicleMsg;
mavros_msgs::Altitude AltitudeMsg;
mavros_msgs::CamIMUStamp CamImuStampMsg;
mavros_msgs::CompanionProcessStatus CompanionProcessStatusMsg;
mavros_msgs::DebugValue DebugValueDebugMsg;
mavros_msgs::DebugValue DebugValueDebugVectorMsg;
mavros_msgs::DebugValue DebugValueNamedValueFloatMsg;
mavros_msgs::DebugValue DebugValueNamedValueIntMsg;
mavros_msgs::DebugValue DebugValueSendMsg;
mavros_msgs::EstimatorStatus EstimatorStatusMsg;
mavros_msgs::ExtendedState ExtendedStateMsg;
mavros_msgs::HomePosition GlobalPositionHomeMsg;
mavros_msgs::RTCM GpsRtkSendRtcmMsg;
mavros_msgs::HilActuatorControls HilActuatorControlsMsg;
mavros_msgs::HilControls HilControlsMsg;
mavros_msgs::HilGPS HilGpsMsg;
mavros_msgs::HilSensor HilImuNedMsg;
mavros_msgs::OpticalFlowRad HilOpticalFlowMsg;
mavros_msgs::RCIn HilRcInputsMsg;
mavros_msgs::HilStateQuaternion HilStateMsg;
mavros_msgs::HomePosition HomePositionHomeMsg;
mavros_msgs::HomePosition HomePositionSetMsg;
mavros_msgs::LogData LogTransferRawLogDataMsg;
mavros_msgs::LogEntry LogTransferRawLogEntryMsg;
mavros_msgs::ManualControl ManualControlControlMsg;
mavros_msgs::ManualControl ManualControlSendMsg;
mavros_msgs::WaypointReached MissionReachedMsg;
mavros_msgs::WaypointList MissionWaypointsMsg;
mavros_msgs::MountControl MountControlCommandMsg;
mavros_msgs::OnboardComputerStatus OnboardComputerStatusMsg;
mavros_msgs::Param ParamParamValueMsg;
mavros_msgs::OpticalFlowRad Px4flowRawOpticalFlowRadMsg;
mavros_msgs::OpticalFlowRad Px4flowRawSendMsg;
mavros_msgs::RadioStatus RadioStatusMsg;
mavros_msgs::RCIn RcInMsg;
mavros_msgs::RCOut RcOutMsg;
mavros_msgs::OverrideRCIn RcOverrideMsg;
mavros_msgs::Thrust SetpointAttitudeThrustMsg;
mavros_msgs::AttitudeTarget SetpointRawAttitudeMsg;
mavros_msgs::GlobalPositionTarget SetpointRawGlobalMsg;
mavros_msgs::PositionTarget SetpointRawLocalMsg;
mavros_msgs::GlobalPositionTarget SetpointRawTargetGlobalMsg;
mavros_msgs::AttitudeTarget SetpointRawTargetAttitudeMsg;
mavros_msgs::PositionTarget SetpointRawTargetLocalMsg;
mavros_msgs::State StateMsg;
mavros_msgs::StatusText StatustextRecvMsg;
mavros_msgs::StatusText StatustextSendMsg;
mavros_msgs::ActuatorControl TargetActuatorControlMsg;
mavros_msgs::TimesyncStatus TimesyncStatusMsg;
mavros_msgs::Trajectory TrajectoryDesiredMsg;
mavros_msgs::Trajectory TrajectoryGeneratedMsg;
mavros_msgs::VFR_HUD VfrHudMsg;


//------> ros topic name <------
string ActuatorControlMsgName = "/mavunity/actuator_control";
string AdsbSendMsgName = "/mavunity/adsb/send";
string AdsbVehicleMsgName ="/mavunity/adsb/vehicle";
string AltitudeMsgName = "/mavunity/battery";
string CamImuStampMsgName = "/mavunity/cam_imu_sync/cam_imu_stamp";
string CompanionProcessStatusMsgName = "/mavunity/companion_process/status";
string DebugValueDebugMsgName = "/mavunity/debug_value/debug";
string DebugValueDebugVectorMsgName = "/mavunity/debug_value/debug_vector";
string DebugValueNamedValueFloatMsgName ="/mavunity/debug_value/named_value_float";
string DebugValueNamedValueIntMsgName ="/mavunity/debug_value/named_value_int";
string DebugValueSendMsgName = "/mavunity/debug_value/send";
string EstimatorStatusMsgName = "/mavunity/estimator_status";
string ExtendedStateMsgName = "/mavunity/extended_state";
string FakeGpsMocapTfMsgName = "mavunity/fake_gps/mocap/tf";
string GlobalPositionCompassHdgMsgName = "/mavunity/global_position/compass_hdg";
string GlobalPositionGlobalMsgName = "/mavunity/global_position/global";
string GlobalPositionGpLpOffsetMsgName = "/mavunity/global_position/gp_lp_offset";
string GlobalPositionGpOriginMsgName = "/mavunity/global_position/gp_origin";
string GlobalPositionHomeMsgName = "/mavunity/global_position/home";
string GlobalPositionLocalMsgName = "/mavunity/global_position/local";
string GlobalPositionRawFixMsgName = "/mavunity/global_position/raw/fix";
string GlobalPositionRawGpsVelMsgName = "/mavunity/global_position/raw/gps/vel";
string GlobalPositionRawSatellitesMsgName = "/mavunity/global_position/raw/satellites";
string GlobalPositionRelAltMsgName = "/mavunity/global_position/rel_alt";
string GlobalPositionSetGpOriginMsgName = "/mavunity/global_position/set_gp_origin";
string GpsRtkSendRtcmMsgName = "/mavunity/gps_rtk/send_rtcm";
string HilActuatorControlsMsgName = "/mavunity/hil/actuator_controls";
string HilControlsMsgName = "/mavunity/hil/controls";
string HilGpsMsgName = "/mavunity/hil/gps";
string HilImuNedMsgName = "/mavunity/hil/imu_ned";
string HilOpticalFlowMsgName = "/mavunity/hil/optical_flow";
string HilRcInputsMsgName = "/mavunity/hil/rc_inputs";
string HilStateMsgName = "/mavunity/hil/state";
string HomePositionSetMsgName = "/mavunity/home_position/set";
string ImuDataMsgName = "/mavunity/imu/data";
string ImuDataRawMsgName = "/mavunity/imu/data_raw";
string ImuDiffPressureMsgName = "/mavunity/imu/diff_pressure";
string ImuMagMsgName = "/mavunity/imu/mag";
string ImuStaticPressureMsgName = "/mavunity/imu/static_pressure";
string ImuTemperatureBaroMsgName = "/mavunity/imu/temperature_barp";
string ImuTemperatureImuMsgName = "/mavunity/imu/temperature_imu";
string LandingTargetLtMarkerMsgName = "/mavunity/landing_target/lt_marker";
string LandingTargetPoseMsgName = "/mavunity/landing_target/pose";
string LandingTargetPoseInMsgName = "/mavunity/landing_target/pose_in";
string LocalPositionAccelMsgName = "/mavunity/local_position/accel";
string LocalPositionOdomMsgName = "/mavunity/local_position/odom";
string LocalPositionPoseMsgName = "/mavunity/local_position/pose";
string LocalPositionPoseCovMsgName = "mavunity/local_position/pose_cov";
string LocalPositionPoseVelocityBodyMsgName ="mavunity/local_position/velocity_body";
string LocalPositionPoseVelocityBodyCovMsgName = "mavunity/local_position/velocity_body_cov";
string LocalPositionPoseVelocityLocalMsgName = "/mavunity/local_position/velocity_local";
string LogTransferRawLogDataMsgName = "/mavunity/log_transfer/raw/log_data";
string LogTransferRawLogEntryMsgName = "/mavunity/log_transfer/raw/log_entry";
string ManualControlControlMsgName = "/mavunity/manual_control/control";
string ManualControlSendMsgName = "/mavunity/manual_control/send";
string MissionReachedMsgName = "/mavunity/reached";
string MissionWaypointsMsgName = "/mavunity/waypoints";
string MocapPoseMsgName = "/mavunity/mocap/pose";
string MountControlCommandMsgName = "/mavunity/mount_control/command";
string MountControlOrientationMsgName = "/mavunity/mount_control/orientation";
string ObstacleSendMsgName ="/mavunity/obstacle/send";
string OdometryInMsgName = "/mavunity/odometry/in";
string OdometryOutMsgName = "/mavunity/odometry/out";
string OnboardComputerStatusMsgName = "/mavunity/onboard_computer/status";
string ParamParamValueMsgName = "/mavunity/param/param_value";
string Px4flowGroundDistanceMsgName = "/mavunity/px4flow/ground_distance";
string Px4flowRawOpticalFlowRadMsgName = "/mavunity/px4flow/raw/optical_flow_rad";
string Px4flowRawSendMsgName = "/mavunity/px4flow/raw/send";
string Px4flowTemperatureMsgName = "/mavunity/px4flow/temperature";
string RadioStatusMsgName = "/mavunity/radio_status";
string RcInMsgName = "/mavunity/rc/in";
string RcOutMsgName ="/mavunity/rc/out";
string RcOverrideMsgName = "/mavunity/rc/override";
string SetpointAccelAccelMsgName = "/mavunity/setpoint_accel/accel";
string SetpointAttitudeCmdVelMsgName = "/mavunity/setpoint_attitude/cmd_vel";
string SetpointAttitudeThrustMsgName = "/mavunity/setpoint_attitude/thrust";
string SetpointPositionGlobalToLocalMsgName = "/mavunity/setpoint_position/global_to_local";
string SetpointPositionGlobalMsgName = "/mavunity/setpoint_position/global";
string SetpointPositionLocalMsgName = "/mavunity/setpoint_position/local";
string SetpointRawAttitudeMsgName= "/mavunity/setpoint_raw/attitude";
string SetpointRawGlobalMsgName= "/mavunity/setpoint_raw/global";
string SetpointRawLocalMsgName= "/mavunity/setpoint_raw/local";
string SetpointRawTargetAttitudeMsgName = "/mavunity/setpoint_raw/target_attitude";
string SetpointRawTargetGlobalMsgName = "/mavunity/setpoint_raw/target_global";
string SetpointRawTargetLocalMsgName = "/mavunity/setpoint_raw/target_local";
string SetpointTrajectoryDesiredMsgName = "/mavunity/setpoint_trajectory/desired";
string SetpointTrajectoryLocalMsgName = "/mavunity/setpoint_trajectory/local";
string SetpointVelocityCmdVelMsgName = "/mavunity/setpoint_velocity/cmd_vel";
string SetpointVelocityCmdVelUnstampedMsName = "/mavunity/setpoint_velocity/cmd_vel_unstamped";
string StateMsgName = "/mavunity/state";
string StatustextRecvMsgName = "/mavunity/statustext/recv";
string StatustextSendMsgName = "/mavunity/statustext/send";
string TargetActuatorControlMsgName = "/mavunity/target_actuator_control";
string TimeReferenceMsgName = "/mavunity/time_reference";
string TimesyncStatusMsgName = "/mavunity/timesync_status";
string TrajectoryDesiredMsgName = "/mavunity/trajectory/desired";
string TrajectoryGeneratedMsgName = "/mavunity/trajectory/generated";
string VfrHudMsgName = "/mavunity/vfr_hud";
string VisionPosePoseMsgName = "/mavunity/vision_pose/pose";
string VisionPosePoseCovMsgName = "/mavunity/vision_pose/pose_cov";
string VisionSpeedSpeedTwistCovMsgName = "/mavunity/vision_speed/speed_twist_cov";
string WindEstimationMsgName = "/mavunity/wind_estimation";

string ros_sub_topic = "/sub";
string ros_pub_topic = "/pub";

ros::Publisher iot_msg_pub;
ros::Subscriber iot_msg_sub;
#endif // UNPACK_CLOUD_DATA_H
