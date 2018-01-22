#ifndef newclient_communication_h
#define newclient_communication_h

#include <iostream>
#include <unistd.h>
#include "nRF24L01P.h"
#include "stream.h"
#include "csuRobocup_radioDef.h"

namespace newclient
{
 class Communication
 {
 public:
   Communication() {};
   class Payload
   {
   public:
     int id;
     float kp, ki, kd, vel;
     Payload(float kp, float ki, float kd, float vel) : kp(kp), ki(ki), kd(kd), vel(vel) {};
   };
   
   virtual void sendCommand(Payload payload);
 };
 
 class Radio// : public Communication
 {
   nRF24L01P my_nrf24l01p;
   char rxBuffer[TRANSFER_SIZE];
   char txBuffer[TRANSFER_SIZE];// = "012345678912345";
   float kp, ki, kd;
 public:
   
   class Payload
   {
   public:
     int id;
     float x_vel, y_vel, omega;
     Payload(int id, float x_vel, float y_vel, float omega) :
	id(id), x_vel(x_vel), y_vel(y_vel), omega(omega) {};
   };
   
   Radio() {}
   void init();
   void sendCommand(Payload &payload);
   

 };
 
 class Simulator : public Communication
 {
 public:
   Simulator() {};
   void sendCommand(Payload payload) override;
 };
 
}

#endif