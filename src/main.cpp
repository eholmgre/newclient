#include <iostream>
#include <thread>
#include <atomic>
#include <vector>
#include <string>
#include <cmath>
#include <ctime>
#include <csignal>
#include <cstdlib>
#include <unistd.h>


#include "vision.h"
#include "field.h"
#include "robot.h"
#include "communication.h"


int main(int argc, char **argv)
{
    std::cout << "Initalizing\n";

    newclient::Simulator radio;
    radio.init();
    newclient::Field field;
    newclient::Vision vis(field);
    std::atomic<bool> run(true);
    std::thread receive(vis, &run);
    std::cout << "main continuing\n";

    time_t start;
    start = time(NULL);
    while (run)
    {


        auto robots = field.getIDs();
        auto ball = field.getBall();

        if (robots.size())
        {
            newclient::Robot robot = field.getRobot(robots[0]);

            double dif = atan2(ball.y_pos - robot.y_pos, ball.x_pos - robot.x_pos) - robot.alpha;
	    
	    if (dif < 0)
	      dif += 2 * 3.14;

            newclient::Radio::Payload payload(3, 0, 0, 0);

            std::cout << "dif: " << dif << '\n';


            if (abs(dif) > .4)
            {
                if (abs(dif) > .2)
                {
                    std::cout << "turning to face, dif: " << dif << "\n";

                    double omega = (dif < 3.14) ? 1 : -1;

                    std::cout << "omega: " << omega <<'\n';

                    payload.omega = omega;
                }

            } else if (sqrt(pow(robot.x_pos - ball.x_pos, 2) + pow(robot.y_pos - ball.y_pos, 2)) > 250)
            {
                //std::cout << "forward to meet ball: " << sqrt(pow(robot.x_pos - ball.x_pos,2) + pow(robot.y_pos - ball.y_pos, 2)) << "\n";
                payload.y_vel = .42;
            } else
            {
                //std::cout << "ball in range!\n";
            }
            radio.sendCommand(payload);


        }
    }
    sleep(1);
    newclient::Radio::Payload stop(3, 0, 0, 0);
    radio.sendCommand(stop);
    sleep(1);


    run.store(false);
    std::cout << "bool changed to " << run.load() << "\n";

    receive.join();

    return 0;
}

