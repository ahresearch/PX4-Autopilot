
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

#include <AttitudeControl.hpp>

/* Serialization routines */

void start_serialization();
void ser_manual_control_setpoint( manual_control_setpoint_s * manual_control_setpoint);
void ser_v_control_mode(vehicle_control_mode_s * vechicle_control_mode);
void ser_loop_perf(perf_counter_t perf_counter);
void ser_thrust_setpoint_body(matrix::Vector3f * thrust_setpoint_body);
void ser_man_yaw_sp(float man_yaw_sp);
void ser_man_tilt_max(float man_tilt_max);
void ser_man_x_input_filter(AlphaFilter<float> man_x_input_filter);
void ser_man_y_input_filter(AlphaFilter<float> man_y_input_filter);
void ser_last_run(hrt_abstime last_run);
void ser_landed( bool landed);
void ser_reset_yaw_sp(bool reset_yaw_sp);
void ser_vehicle_type_rotary_wing(bool vehicle_type_rotary_wing);
void ser_vtol(bool vtol);
void ser_vtol_tailsitter(bool vtol_tailsitter);
void ser_vtol_in_transition_mode(bool vtol_in_transition_mode);
void ser_quat_reset_counter(uint8_t quat_reset_counter);
void stop_serialization();


/* Deserialization routines */
void start_deserialization();
void deser_manual_control_setpoint(manual_control_setpoint_s * manual_control_setpoint);
void deser_v_control_mode(vehicle_control_mode_s * v_control_mode);
void deser_loop_perf(perf_counter_t  *loop_perf);
void deser_thrust_setpoint_body(matrix::Vector3f * thrust_setpoint_body);
void deser_man_yaw_sp(float * man_yaw_sp);
void deser_man_tilt_max(float * man_tilt_max);
void deser_man_x_input_filter(AlphaFilter<float> * man_x_input_filter);
void deser_man_y_input_filter(AlphaFilter<float> * man_y_input_filter);
void deser_last_run(hrt_abstime *last_run);
void deser_landed( bool * landed);
void deser_reset_yaw_sp( bool * reset_yaw_sp);
void deser_vehicle_type_rotary_wing( bool * vehicle_type_rotary_wing);
void deser_vtol( bool * vtol);
void deser_vtol_tailsitter( bool * vtol_tailsitter);
void deser_vtol_in_transition_mode( bool * vtol_in_transition_mode);
void deser_quat_reset_counter(uint8_t * quat_reset_counter);
void stop_deserialization();



void test_bitsery();
