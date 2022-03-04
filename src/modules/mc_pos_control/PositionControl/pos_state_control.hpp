
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
void ser_pos(matrix::Vector3f * pos);
void ser_vel(matrix::Vector3f * vel);
void ser_vel_dot(matrix::Vector3f * vel_dot);
void ser_vel_int(matrix::Vector3f * vel_int);
void ser_yaw(float yaw);
void stop_pos_serialization();


/* Deserialization routines */
void start_pos_deserialization();
void deser_pos(matrix::Vector3f * pos);
void deser_vel(matrix::Vector3f * vel);
void deser_vel_dot(matrix::Vector3f * vel_dot);
void deser_vel_int(matrix::Vector3f * vel_int);
void deser_yaw(float * yaw);
void stop_pos_deserialization();



void test_bitsery();
