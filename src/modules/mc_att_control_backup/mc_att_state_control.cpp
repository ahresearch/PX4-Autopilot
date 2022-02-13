#include <bitsery/bitsery.h>
//in order to work with streams include stream adapter
#include <bitsery/adapter/stream.h>
#include <fstream>
#include <iostream>

#include "mc_att_state_control.hpp"

auto mc_att_file_name = "mc_att_state.bin";
std::fstream * s_ptr;
bitsery::Serializer<bitsery::OutputBufferedStreamAdapter> * ser_ptr;
bitsery::Deserializer<bitsery::InputStreamAdapter> *des_ptr;




enum class MyEnum:uint16_t { V1,V2,V3 };
struct MyStruct {
    uint32_t i;
    MyEnum e;
    double f;
};


struct OtherStruct {
    double f;
};

//define how object should be serialized/deserialized
template <typename S>
void serialize(S& s, MyStruct& o) {
    s.value4b(o.i);
    s.value2b(o.e);
    s.value8b(o.f);
}


template <typename S>
void serialize(S& s, OtherStruct & o) {
    s.value8b(o.f);
}



template <typename S>
void serialize(S& s, manual_control_setpoint_s & o) {
    s.value8b(o.timestamp);
    s.value8b(o.timestamp_sample);
    s.value4b(o.x);
    s.value4b(o.y);
    s.value4b(o.z);
    s.value4b(o.r);
    s.value4b(o.flaps);
    s.value4b(o.aux1);
    s.value4b(o.aux2);
    s.value4b(o.aux3);
    s.value4b(o.aux4);
    s.value4b(o.aux5);
    s.value4b(o.aux6);
    s.value1b(o.valid);
    s.value1b(o.data_source);
    s.value1b(o.sticks_moving);
    s.value1b(o._padding0[0]);
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




void start_serialization(){
    s_ptr = new std::fstream {mc_att_file_name, s_ptr->binary | s_ptr->trunc | s_ptr->out};
    ser_ptr = new bitsery::Serializer<bitsery::OutputBufferedStreamAdapter> (*s_ptr);
}

void ser_manual_control_setpoint( manual_control_setpoint_s * manual_control_setpoint){
   ser_ptr->object(*manual_control_setpoint);
}

void ser_v_control_mode(vehicle_control_mode_s * vechicle_control_mode){
    ser_ptr->object(*vechicle_control_mode);
}

void ser_loop_perf(perf_counter_t perf_counter){
       /* No need to serialize */
}

void ser_thrust_setpoint_body(matrix::Vector3f * thrust_setpoint_body){
   float arr[3];
   thrust_setpoint_body->copyTo(arr);
   ser_ptr->value4b(arr[0]);
   ser_ptr->value4b(arr[1]);
   ser_ptr->value4b(arr[2]);
}

void ser_man_yaw_sp(float man_yaw_sp){
    ser_ptr->value4b(man_yaw_sp);
}

void ser_man_tilt_max(float man_tilt_max){
    ser_ptr->value4b(man_tilt_max);
}

void ser_man_x_input_filter(AlphaFilter<float> man_x_input_filter){
     /* No need to serialize */
}

void ser_man_y_input_filter(AlphaFilter<float> man_y_input_filter){
     /* No need to serialize */
}

void ser_last_run(hrt_abstime last_run){
    ser_ptr->value8b(last_run);
}

void ser_landed( bool landed){
    ser_ptr->value1b(landed);
}

void ser_reset_yaw_sp(bool reset_yaw_sp){
    ser_ptr->value1b(reset_yaw_sp);
}

void ser_vehicle_type_rotary_wing(bool vehicle_type_rotary_wing){
    ser_ptr->value1b(vehicle_type_rotary_wing);
}

void ser_vtol(bool vtol){
   ser_ptr->value1b(vtol);
}

void ser_vtol_tailsitter(bool vtol_tailsitter){
   ser_ptr->value1b(vtol_tailsitter);
}

void ser_vtol_in_transition_mode(bool vtol_in_transition_mode){
    ser_ptr->value1b(vtol_in_transition_mode);
}

void ser_quat_reset_counter(uint8_t quat_reset_counter){
   ser_ptr->value1b(quat_reset_counter);
}

void stop_serialization(){
    ser_ptr->adapter().flush();
    s_ptr->close();
    delete(ser_ptr);
    delete(s_ptr);
}



/* Deserialization routines */
void start_deserialization(){
   s_ptr = new std::fstream {mc_att_file_name, s_ptr->binary | s_ptr->in};
   des_ptr = new bitsery::Deserializer<bitsery::InputStreamAdapter>(*s_ptr);
}

void deser_manual_control_setpoint(manual_control_setpoint_s * manual_control_setpoint){
    bitsery::quickDeserialization<bitsery::InputStreamAdapter>(*s_ptr, *manual_control_setpoint);
}

void deser_v_control_mode(vehicle_control_mode_s * v_control_mode){
    bitsery::quickDeserialization<bitsery::InputStreamAdapter>(*s_ptr, *v_control_mode);
}

void deser_loop_perf(perf_counter_t  *loop_perf){
     /* No need to deserialize */
}

void deser_thrust_setpoint_body(matrix::Vector3f * thrust_setpoint_body){
   float arr[3];
   des_ptr->value4b(arr[0]);
   des_ptr->value4b(arr[1]);
   des_ptr->value4b(arr[2]);
   matrix::Vector3f m(arr[0],arr[1],arr[2]);
   *thrust_setpoint_body = m;
}

void deser_man_yaw_sp(float * man_yaw_sp){
    des_ptr->value4b(*man_yaw_sp);
}

void deser_man_tilt_max(float * man_tilt_max){
    des_ptr->value4b(*man_tilt_max);
}

void deser_man_x_input_filter(AlphaFilter<float> * man_x_input_filter){
     /* No need to deserialize */
}

void deser_man_y_input_filter(AlphaFilter<float> * man_y_input_filter){
     /* No need to deserialize */
}

void deser_last_run(hrt_abstime *last_run){
    des_ptr->value8b(*last_run);
}

void deser_landed( bool * landed){
   des_ptr->value1b(*landed);
}

void deser_reset_yaw_sp( bool * reset_yaw_sp){
   des_ptr->value1b(*reset_yaw_sp);
}

void deser_vehicle_type_rotary_wing( bool * vehicle_type_rotary_wing){
   des_ptr->value1b(*vehicle_type_rotary_wing);
}

void deser_vtol( bool * vtol){
    des_ptr->value1b(*vtol);
}

void deser_vtol_tailsitter( bool * vtol_tailsitter){
    des_ptr->value1b(*vtol_tailsitter);
}

void deser_vtol_in_transition_mode( bool * vtol_in_transition_mode){
    des_ptr->value1b(*vtol_in_transition_mode);
}

void deser_quat_reset_counter(uint8_t * quat_reset_counter){
    des_ptr->value1b(*quat_reset_counter);
}

void stop_deserialization(){
   delete(des_ptr);
   delete(s_ptr);
}






void test_bitsery() {
    //set some random data
    MyStruct data1{8941, MyEnum::V2, 0.045};
    MyStruct data2{8942, MyEnum::V3, 0.046};
    OtherStruct other;
    other.f = 3.14;
    MyStruct res1{};
    MyStruct res2{};
    OtherStruct fres;
    fres.f = 0.0;
    double d = 5.18;
    double dres;

    //open file stream for writing and reading
    auto fileName = "test_file.bin";
    std::fstream s{fileName, s.binary | s.trunc | s.out};
    if (!s.is_open()) {
        std::cout << "cannot open " << fileName << " for writing\n";
        return ;
    }

    //we cannot use quick serialization function, because streams cannot use writtenBytesCount method
    bitsery::Serializer<bitsery::OutputBufferedStreamAdapter> ser{s};
    ser.object(data1);
    ser.object(data2);
    ser.object(other);
    ser.value8b(d);
    //flush to writer
    ser.adapter().flush();
    s.close();
    //reopen for reading

    s.open(fileName, s.binary | s.in);
    if (!s.is_open()) {
        std::cout << "cannot open " << fileName << " for reading\n";
        return ;
    }

    //same as serialization, but returns deserialization state as a pair
    //first = error code, second = is buffer was successfully read from begin to the end.
    bitsery::quickDeserialization<bitsery::InputStreamAdapter>(s, res1);
    bitsery::quickDeserialization<bitsery::InputStreamAdapter>(s, res2);
    bitsery::quickDeserialization<bitsery::InputStreamAdapter>(s, fres);
    bitsery::Deserializer<bitsery::InputStreamAdapter> des{s};
    des.value8b(dres);
    assert(state.first == bitsery::ReaderError::NoError);
    assert(data1.f == res1.f && data1.i == res1.i && data1.e == res1.e);
    assert(data2.f == res2.f && data2.i == res2.i && data2.e == res2.e);
    assert(other.f == fres.f);
    assert(d == dres);
    std::cout << std::endl << "test_bitsery finished" << std::endl << std::endl;
}
