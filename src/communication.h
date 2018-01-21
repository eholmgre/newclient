#ifndef newclient_communication_h
#define newclient_communication_h

#include <iostream>
#include "nRF24L01P.h"
#include "stream.h"
#include "csuRobocup_radioDef.h"

namespace newclient
{
 class Communication
 {
 public:
   virtual void sendCommand(std::string payload) = 0;
 }
 
 class Radio : Communication
 {
   nRF24L01P my_nrf24l01p;
   char rxBuffer[TRANSFER_SIZE];
   char txBuffer[TRANSFER_SIZE];// = "012345678912345";
   float kp, ki, kd, maxSum, maxITerm, xVel, yVel, wVel;
   int mtrV1, mtrV2, mtrV3, mtrV4;
 public:
   Radio();
   void init();
   void sendCommand(std::string payload);
 }
 
 class Simulator : Communication
 {
 public:
   void sendCommand(std::string payload);
 }
}

#endif