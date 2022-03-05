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

void ser_hover_thrust(float hover_thrust){
    ser_ptr->value4b(hover_thrust);
    std::cout << "ser_hover_thrust: " << hover_thrust <<  std::endl;
}

void ser_pos(matrix::Vector3f * pos){
   float arr[3];
   pos->copyTo(arr);
   ser_ptr->value4b(arr[0]);
   ser_ptr->value4b(arr[1]);
   ser_ptr->value4b(arr[2]);
   std::cout << "ser_pos: " << arr[0] << " " << arr[1] << " " << arr[2] <<  std::endl;
}


void ser_vel(matrix::Vector3f * vel){
   float arr[3];
   vel->copyTo(arr);
   ser_ptr->value4b(arr[0]);
   ser_ptr->value4b(arr[1]);
   ser_ptr->value4b(arr[2]);
   std::cout << "ser_vel: " << arr[0] << " "  << arr[1] << " "  << arr[2] <<  std::endl;
}


void ser_vel_dot(matrix::Vector3f * vel_dot){
   float arr[3];
   vel_dot->copyTo(arr);
   ser_ptr->value4b(arr[0]);
   ser_ptr->value4b(arr[1]);
   ser_ptr->value4b(arr[2]);
   std::cout << "ser_vel_dot: " << arr[0] << " "  << arr[1] << " "  << arr[2] <<  std::endl;
}


void ser_vel_int(matrix::Vector3f * vel_int){
   float arr[3];
   vel_int->copyTo(arr);
   ser_ptr->value4b(arr[0]);
   ser_ptr->value4b(arr[1]);
   ser_ptr->value4b(arr[2]);
   std::cout << "ser_vel_int: " << arr[0] << " "  << arr[1] << " "  << arr[2] <<  std::endl;
}


void ser_yaw(float yaw){
    ser_ptr->value4b(yaw);
    std::cout << "ser_yaw: " << yaw <<  std::endl;
}

void ser_pos_sp(matrix::Vector3f * pos_sp){
   float arr[3];
   pos_sp->copyTo(arr);
   ser_ptr->value4b(arr[0]);
   ser_ptr->value4b(arr[1]);
   ser_ptr->value4b(arr[2]);
   std::cout << "ser_pos_sp: " << arr[0] << " " << arr[1] << " " << arr[2] <<  std::endl;
}

void ser_vel_sp(matrix::Vector3f * vel_sp){
   float arr[3];
   vel_sp->copyTo(arr);
   ser_ptr->value4b(arr[0]);
   ser_ptr->value4b(arr[1]);
   ser_ptr->value4b(arr[2]);
   std::cout << "ser_vel_sp: " << arr[0] << " " << arr[1] << " " << arr[2] <<  std::endl;
}

void ser_acc_sp(matrix::Vector3f * acc_sp){
   float arr[3];
   acc_sp->copyTo(arr);
   ser_ptr->value4b(arr[0]);
   ser_ptr->value4b(arr[1]);
   ser_ptr->value4b(arr[2]);
   std::cout << "ser_acc_sp: " << arr[0] << " " << arr[1] << " " << arr[2] <<  std::endl;
}

void ser_thr_sp(matrix::Vector3f * thr_sp){
   float arr[3];
   thr_sp->copyTo(arr);
   ser_ptr->value4b(arr[0]);
   ser_ptr->value4b(arr[1]);
   ser_ptr->value4b(arr[2]);
   std::cout << "ser_thr_sp: " << arr[0] << " " << arr[1] << " " << arr[2] <<  std::endl;
}

void ser_yaw_sp(float yaw_sp){
    ser_ptr->value4b(yaw_sp);
    std::cout << "ser_yaw_sp: " << yaw_sp <<  std::endl;
}

void ser_yaw_speed_sp(float yaw_speed_sp){
    ser_ptr->value4b(yaw_speed_sp);
    std::cout << "ser_yaw_sp: " << yaw_speed_sp <<  std::endl;
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


void deser_hover_thrust(float * hover_thrust){
    des_ptr->value4b(*hover_thrust);
    std::cout << "deser_hover_thrust: " << *hover_thrust <<  std::endl;
}

void deser_pos(matrix::Vector3f * pos){
   float arr[3];
   des_ptr->value4b(arr[0]);
   des_ptr->value4b(arr[1]);
   des_ptr->value4b(arr[2]);
   std::cout << "deser_pos: " << arr[0] << " "  << arr[1] << " " << arr[2] <<  std::endl;
   matrix::Vector3f m(arr[0],arr[1],arr[2]);
   *pos = m;
}

void deser_vel(matrix::Vector3f * vel){
   float arr[3];
   des_ptr->value4b(arr[0]);
   des_ptr->value4b(arr[1]);
   des_ptr->value4b(arr[2]);
   std::cout << "deser_vel: " << arr[0] << " " << arr[1] << " " << arr[2] <<  std::endl;
   matrix::Vector3f m(arr[0],arr[1],arr[2]);
   *vel = m;
}

void deser_vel_dot(matrix::Vector3f * vel_dot){
   float arr[3];
   des_ptr->value4b(arr[0]);
   des_ptr->value4b(arr[1]);
   des_ptr->value4b(arr[2]);
   std::cout << "deser_vel_dot: " << arr[0] << " " << arr[1] << " " << arr[2] <<  std::endl;
   matrix::Vector3f m(arr[0],arr[1],arr[2]);
   *vel_dot = m;
}

void deser_vel_int(matrix::Vector3f * vel_int){
   float arr[3];
   des_ptr->value4b(arr[0]);
   des_ptr->value4b(arr[1]);
   des_ptr->value4b(arr[2]);
   std::cout << "deser_vel_int: " << arr[0] << " " << arr[1] << " " << arr[2] <<  std::endl;
   matrix::Vector3f m(arr[0],arr[1],arr[2]);
   *vel_int = m;
}

void deser_yaw(float * yaw){
    des_ptr->value4b(*yaw);
    std::cout << "deser_yaw: " << *yaw <<  std::endl;
}


void deser_pos_sp(matrix::Vector3f * pos_sp){
   float arr[3];
   des_ptr->value4b(arr[0]);
   des_ptr->value4b(arr[1]);
   des_ptr->value4b(arr[2]);
   std::cout << "deser_pos_sp: " << arr[0] << " "  << arr[1] << " " << arr[2] <<  std::endl;
   matrix::Vector3f m(arr[0],arr[1],arr[2]);
   *pos_sp = m;
}

void deser_vel_sp(matrix::Vector3f * vel_sp){
   float arr[3];
   des_ptr->value4b(arr[0]);
   des_ptr->value4b(arr[1]);
   des_ptr->value4b(arr[2]);
   std::cout << "deser_vel_sp: " << arr[0] << " "  << arr[1] << " " << arr[2] <<  std::endl;
   matrix::Vector3f m(arr[0],arr[1],arr[2]);
   *vel_sp = m;
}

void deser_acc_sp(matrix::Vector3f * acc_sp){
   float arr[3];
   des_ptr->value4b(arr[0]);
   des_ptr->value4b(arr[1]);
   des_ptr->value4b(arr[2]);
   std::cout << "deser_acc_sp: " << arr[0] << " "  << arr[1] << " " << arr[2] <<  std::endl;
   matrix::Vector3f m(arr[0],arr[1],arr[2]);
   *acc_sp = m;
}

void deser_thr_sp(matrix::Vector3f * thr_sp){
   float arr[3];
   des_ptr->value4b(arr[0]);
   des_ptr->value4b(arr[1]);
   des_ptr->value4b(arr[2]);
   std::cout << "deser_thr_sp: " << arr[0] << " "  << arr[1] << " " << arr[2] <<  std::endl;
   matrix::Vector3f m(arr[0],arr[1],arr[2]);
   *thr_sp = m;
}


void deser_yaw_sp(float * yaw_sp){
    des_ptr->value4b(*yaw_sp);
    std::cout << "deser_yaw_sp: " << *yaw_sp <<  std::endl;
}

void deser_yaw_speed_sp(float * yaw_speed_sp){
    des_ptr->value4b(*yaw_speed_sp);
    std::cout << "deser_yaw_speed_sp: " << *yaw_speed_sp <<  std::endl;
}


void stop_pos_deserialization(){
   delete(des_ptr);
   delete(s_ptr);
}
