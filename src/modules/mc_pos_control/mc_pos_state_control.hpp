
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
#include <Takeoff/Takeoff.hpp>


/* Serialization routines */
void start_mc_pos_serialization();
void ser_takeoff_state(TakeoffState t_state);
void ser_vehicle_local_position_setpoint( vehicle_local_position_setpoint_s * vehicle_local_position_setpoint);
void ser_vehicle_control_mode( vehicle_control_mode_s * vehicle_control_mode_s);
void ser_timestamp_last_loop(uint64_t timestamp_last_loop);
void stop_mc_pos_serialization();


/* Deserialization routines */
void start_mc_pos_deserialization();
void deser_takeoff_state(TakeoffState *t_state);
void deser_vehicle_local_position_setpoint(vehicle_local_position_setpoint_s * vehicle_local_position_setpoint);
void deser_vehicle_control_mode(vehicle_control_mode_s * vehicle_control_mode);
void deser_timestamp_last_loop(uint64_t *timestamp_last_loop);
void stop_mc_pos_deserialization();



