#ifndef newclient_communication_h
#define newclient_communication_h

#include <iostream>
#include <unistd.h>

#include "nRF24L01P.h"
#include "stream.h"
#include "csuRobocup_radioDef.h"

#include "grSim_Packet.pb.h"
#include "grSim_Commands.pb.h"
#include "grSim_Replacement.pb.h"
#include "netraw.h"


namespace newclient
{
    class Communication
    {
    public:

        class Payload
        {
        public:
            int id;
            float x_vel, y_vel, omega;

            Payload(int id, float x_vel, float y_vel, float omega) :
                    id(id), x_vel(x_vel), y_vel(y_vel), omega(omega)
            {};
        };

        virtual void sendCommand(const Payload &payload) = 0;

        virtual void init(bool _=false) = 0;
    };

    class Radio : public Communication
    {
        nRF24L01P my_nrf24l01p;
        char rxBuffer[TRANSFER_SIZE];
        char txBuffer[TRANSFER_SIZE];
        float kp, ki, kd;
    public:

        void init(bool _=false) override;

        void sendCommand(const Payload &payload) override;


    };

    class Simulator : public Communication
    {
        Net::UDP udpsoc;
        Net::Address addr;
        const int _port = 20011;
        const char *_addr = "127.0.0.1";
	bool is_yellow;
    public:
        void sendCommand(const Payload &payload) override;

        void init(bool yellow=true) override;

        ~Simulator()
        { udpsoc.close(); };
    };

}

#endif