#include <bitsery/bitsery.h>
//in order to work with streams include stream adapter
#include <bitsery/adapter/stream.h>
#include <fstream>
#include <iostream>


#include <vehicle_control_mode.h>
#include <vehicle_local_position_setpoint.h>
#include "mc_pos_state_control.hpp"

auto mc_pos_state_file_name = "mc_pos_control.bin";
static std::fstream * s_ptr;
static bitsery::Serializer<bitsery::OutputBufferedStreamAdapter> * ser_ptr;
static bitsery::Deserializer<bitsery::InputStreamAdapter> *des_ptr;


template <typename S>
void serialize(S& s, vehicle_local_position_setpoint_s & o) {
    s.value4b(o.x);
    s.value4b(o.y);
    s.value4b(o.z);
    s.value4b(o.yaw);
    s.value4b(o.yawspeed);
    s.value4b(o.vx);
    s.value4b(o.vy);
    s.value4b(o.vz);
    s.value4b(o.acceleration[0]);
    s.value4b(o.acceleration[1]);
    s.value4b(o.acceleration[2]);
    s.value4b(o.jerk[0]);
    s.value4b(o.jerk[1]);
    s.value4b(o.jerk[2]);
    s.value4b(o.thrust[0]);
    s.value4b(o.thrust[1]);
    s.value4b(o.thrust[2]);
    s.value1b(o._padding0[0]);
    s.value1b(o._padding0[1]);
    s.value1b(o._padding0[2]);
    s.value1b(o._padding0[3]);
}

template <typename S>
void serialize(S& s, vehicle_control_mode_s & o) {
    s.value8b(o.timestamp);
    s.value1b(o.flag_armed);
    s.value1b(o.flag_multicopter_position_control_enabled);
    s.value1b(o.flag_control_manual_enabled);
    s.value1b(o.flag_control_auto_enabled);
    s.value1b(o.flag_control_offboard_enabled);
    s.value1b(o.flag_control_rates_enabled);
    s.value1b(o.flag_control_attitude_enabled);
    s.value1b(o.flag_control_acceleration_enabled);
    s.value1b(o.flag_control_velocity_enabled);
    s.value1b(o.flag_control_position_enabled);
    s.value1b(o.flag_control_altitude_enabled);
    s.value1b(o.flag_control_climb_rate_enabled);
    s.value1b(o.flag_control_termination_enabled);
    s.value1b(o._padding0[0]);
    s.value1b(o._padding0[1]);
    s.value1b(o._padding0[2]);
}



void start_mc_pos_serialization(){
    s_ptr = new std::fstream {mc_pos_state_file_name, s_ptr->binary | s_ptr->trunc | s_ptr->out};
    ser_ptr = new bitsery::Serializer<bitsery::OutputBufferedStreamAdapter> (*s_ptr);
}

void ser_takeoff_state(TakeoffState t_state){
    ser_ptr->value4b(t_state);
    std::cout << "t_state: " << (int)t_state <<  std::endl;
}

void ser_vehicle_local_position_setpoint( vehicle_local_position_setpoint_s * vehicle_local_position_setpoint){
   ser_ptr->object(*vehicle_local_position_setpoint);
   std::cout << "_setpoint: " << vehicle_local_position_setpoint->x <<  " " << vehicle_local_position_setpoint->y << " "
             <<  vehicle_local_position_setpoint->z << " " << vehicle_local_position_setpoint->yaw << std::endl;
}


void ser_vehicle_control_mode( vehicle_control_mode_s * vehicle_control_mode){
   ser_ptr->object(*vehicle_control_mode);
   std::cout << "_vehicle_control_mode : " << vehicle_control_mode->flag_armed <<  " " << vehicle_control_mode->flag_multicopter_position_control_enabled
               <<  " " <<   vehicle_control_mode->flag_control_manual_enabled <<  " " <<  vehicle_control_mode->flag_control_auto_enabled << std::endl;
}

void ser_timestamp_last_loop(uint64_t timestamp_last_loop){
    ser_ptr->value8b(timestamp_last_loop);
    std::cout << "ser_timestamp_last_loop: " << timestamp_last_loop <<  std::endl;
}

void stop_mc_pos_serialization(){
    ser_ptr->adapter().flush();
    s_ptr->close();
    delete(ser_ptr);
    delete(s_ptr);
}

/* Deserialization routines */
void start_mc_pos_deserialization(){
   s_ptr = new std::fstream {mc_pos_state_file_name, s_ptr->binary | s_ptr->in};
   des_ptr = new bitsery::Deserializer<bitsery::InputStreamAdapter>(*s_ptr);
}

void deser_takeoff_state(TakeoffState *t_state){
    des_ptr->value4b(*t_state);
    std::cout << "t_state: " << (int) *t_state <<  std::endl;
}

void deser_vehicle_local_position_setpoint(vehicle_local_position_setpoint_s * vehicle_local_position_setpoint){
    bitsery::quickDeserialization<bitsery::InputStreamAdapter>(*s_ptr, *vehicle_local_position_setpoint);
   std::cout << "_setpoint: " << vehicle_local_position_setpoint->x <<  " " << vehicle_local_position_setpoint->y << " "
             <<  vehicle_local_position_setpoint->z << " " << vehicle_local_position_setpoint->yaw << std::endl;
}

void deser_vehicle_control_mode(vehicle_control_mode_s * vehicle_control_mode){
    bitsery::quickDeserialization<bitsery::InputStreamAdapter>(*s_ptr, *vehicle_control_mode);
    std::cout << "_vehicle_control_mode : " << vehicle_control_mode->flag_armed <<  " " << vehicle_control_mode->flag_multicopter_position_control_enabled
               <<  " " <<   vehicle_control_mode->flag_control_manual_enabled <<  " " <<  vehicle_control_mode->flag_control_auto_enabled << std::endl;
}

void deser_timestamp_last_loop(uint64_t *timestamp_last_loop){
    des_ptr->value8b(*timestamp_last_loop);
    std::cout << "deser_timestamp_last_loop: " << *timestamp_last_loop <<  std::endl;
}


void stop_mc_pos_deserialization(){
   delete(des_ptr);
   delete(s_ptr);
}
