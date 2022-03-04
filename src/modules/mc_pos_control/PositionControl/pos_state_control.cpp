#include <bitsery/bitsery.h>
//in order to work with streams include stream adapter
#include <bitsery/adapter/stream.h>
#include <fstream>
#include <iostream>

#include "pos_state_control.hpp"

auto pos_state_file_name = "pos_control.bin";
static std::fstream * s_ptr;
static bitsery::Serializer<bitsery::OutputBufferedStreamAdapter> * ser_ptr;
static bitsery::Deserializer<bitsery::InputStreamAdapter> *des_ptr;

void start_pos_serialization(){
    s_ptr = new std::fstream {pos_state_file_name, s_ptr->binary | s_ptr->trunc | s_ptr->out};
    ser_ptr = new bitsery::Serializer<bitsery::OutputBufferedStreamAdapter> (*s_ptr);
}

void ser_pos(matrix::Vector3f * pos){
   float arr[3];
   pos->copyTo(arr);
   ser_ptr->value4b(arr[0]);
   ser_ptr->value4b(arr[1]);
   ser_ptr->value4b(arr[2]);
}


void ser_vel(matrix::Vector3f * vel){
   float arr[3];
   vel->copyTo(arr);
   ser_ptr->value4b(arr[0]);
   ser_ptr->value4b(arr[1]);
   ser_ptr->value4b(arr[2]);
}


void ser_vel_dot(matrix::Vector3f * vel_dot){
   float arr[3];
   vel_dot->copyTo(arr);
   ser_ptr->value4b(arr[0]);
   ser_ptr->value4b(arr[1]);
   ser_ptr->value4b(arr[2]);
}


void ser_vel_int(matrix::Vector3f * vel_int){
   float arr[3];
   vel_int->copyTo(arr);
   ser_ptr->value4b(arr[0]);
   ser_ptr->value4b(arr[1]);
   ser_ptr->value4b(arr[2]);
}


void ser_yaw(float yaw){
    ser_ptr->value4b(yaw);
}

void stop_pos_serialization(){
    ser_ptr->adapter().flush();
    s_ptr->close();
    delete(ser_ptr);
    delete(s_ptr);
}

/* Deserialization routines */
void start_pos_deserialization(){
   s_ptr = new std::fstream {pos_state_file_name, s_ptr->binary | s_ptr->in};
   des_ptr = new bitsery::Deserializer<bitsery::InputStreamAdapter>(*s_ptr);
}

void deser_pos(matrix::Vector3f * pos){
   float arr[3];
   des_ptr->value4b(arr[0]);
   des_ptr->value4b(arr[1]);
   des_ptr->value4b(arr[2]);
   matrix::Vector3f m(arr[0],arr[1],arr[2]);
   *pos = m;
}

void deser_vel(matrix::Vector3f * vel){
   float arr[3];
   des_ptr->value4b(arr[0]);
   des_ptr->value4b(arr[1]);
   des_ptr->value4b(arr[2]);
   matrix::Vector3f m(arr[0],arr[1],arr[2]);
   *vel = m;
}

void deser_vel_dot(matrix::Vector3f * vel_dot){
   float arr[3];
   des_ptr->value4b(arr[0]);
   des_ptr->value4b(arr[1]);
   des_ptr->value4b(arr[2]);
   matrix::Vector3f m(arr[0],arr[1],arr[2]);
   *vel_dot = m;
}

void deser_vel_int(matrix::Vector3f * vel_int){
   float arr[3];
   des_ptr->value4b(arr[0]);
   des_ptr->value4b(arr[1]);
   des_ptr->value4b(arr[2]);
   matrix::Vector3f m(arr[0],arr[1],arr[2]);
   *vel_int = m;
}

void deser_yaw(float * yaw){
    des_ptr->value4b(*yaw);
}

void stop_pos_deserialization(){
   delete(des_ptr);
   delete(s_ptr);
}
