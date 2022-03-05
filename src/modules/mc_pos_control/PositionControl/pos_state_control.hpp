
#include <uORB/Publication.hpp>
#include <uORB/Subscription.hpp>
#include <uORB/SubscriptionCallback.hpp>
#include <uORB/topics/manual_control_setpoint.h>
#include <uORB/topics/parameter_update.h>
#include <uORB/topics/autotune_attitude_control_status.h>
#include <uORB/topics/vehicle_attitude.h>
#include <uORB/topics/vehicle_attitude_setpoint.h>
#include <uORB/topics/vehicle_control_mode.h>
#include <uORB/topics/vehicle_rates_setpoint.h>
#include <uORB/topics/vehicle_status.h>
#include <uORB/topics/vehicle_land_detected.h>
#include <vtol_att_control/vtol_type.h>
#include <lib/mathlib/math/filter/AlphaFilter.hpp>


/* Serialization routines */
void start_pos_serialization();
void ser_hover_thrust(float hover_thrust);
void ser_pos(matrix::Vector3f * pos);
void ser_vel(matrix::Vector3f * vel);
void ser_vel_dot(matrix::Vector3f * vel_dot);
void ser_vel_int(matrix::Vector3f * vel_int);
void ser_yaw(float yaw);
void ser_pos_sp(matrix::Vector3f * pos_sp);
void ser_vel_sp(matrix::Vector3f * vel_sp);
void ser_acc_sp(matrix::Vector3f * acc_sp);
void ser_thr_sp(matrix::Vector3f * thr_sp);
void ser_yaw_sp(float yaw_sp);
void ser_yaw_speed_sp(float yaw_speed_sp);
void stop_pos_serialization();


/* Deserialization routines */
void start_pos_deserialization();
void deser_hover_thrust(float * hover_thrust);
void deser_pos(matrix::Vector3f * pos);
void deser_vel(matrix::Vector3f * vel);
void deser_vel_dot(matrix::Vector3f * vel_dot);
void deser_vel_int(matrix::Vector3f * vel_int);
void deser_yaw(float * yaw);
void deser_pos_sp(matrix::Vector3f * pos_sp);
void deser_vel_sp(matrix::Vector3f * vel_sp);
void deser_acc_sp(matrix::Vector3f * acc_sp);
void deser_thr_sp(matrix::Vector3f * thr_sp);
void deser_yaw_sp(float * yaw_sp);
void deser_yaw_speed_sp(float * yaw_speed_sp);
void stop_pos_deserialization();


void test_bitsery();
