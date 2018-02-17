#ifndef newclient_vision_h
#define newclient_vision_h

#include <iostream>
#include <atomic>

#include "field.h"

#include "timer.h"
#include "robocup_ssl_client.h"

#include "messages_robocup_ssl_detection.pb.h"
#include "messages_robocup_ssl_geometry.pb.h"
#include "messages_robocup_ssl_wrapper.pb.h"

namespace newclient
{

    class Vision
    {
        Field &field;

        void printRobotInfo(const SSL_DetectionRobot &robot);

    public:
        Vision(Field &field) : field(field)
        {};

        Vision(const Vision &vis) : field(vis.field)
        {};

        void operator()(atomic<bool> *run, bool print = false);
    };
}

#endif