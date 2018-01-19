#ifndef newclient_client_h
#define newclient_client_h

#include "robocup_ssl_client.h"

#include "messages_robocup_ssl_detection.pb.h"
#include "messages_robocup_ssl_geometry.pb.h"
#include "messages_robocup_ssl_wrapper.pb.h"

  class Client {
   void printRobotInfo(const SSL_DetectionRobot & robot);
  public:
   Client();
   
   void run();
  };

#endif