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
#include "PID.h"

using std::cout;
using std::cin;
using std::string;

using newclient::PID;

int main(int argc, char **argv)
{
    bool is_yellow = true; // Playing as yellow is default
    if (argc > 1)
    {
        string color = *(argv + 1);
        if (color == "Blue" or color == "blue" or color == "B" or color == "b")
        {
            is_yellow = false;
        }
    }
    cout << "Initalizing\n";

    newclient::Simulator radio;
    //newclient::Radio radio;
    radio.init(is_yellow);
    newclient::Field field;
    newclient::Vision vis(field);
    std::atomic<bool> run(true);
    std::thread receive(vis, &run);
    std::cout << "main continuing\n";

    const int goal_neg_x = -4500;
    const int goal_neg_y = -600;

    const int goal_pos_x = -4500;
    const int goal_pos_y = 600;

    PID aPID(1, 0, 6, -2, 2);

    PID xPID(2, 0, 8, -2, 2);
    PID yPID(2, 0, 8, -2, 2);

    sleep(1);
    time_t start;
    start = time(NULL);
    while (run)
    {
        auto robots = field.getIDs();
        auto ball = field.getBall();


        if (robots.size() >= 2)
        {
            const double circ_inlf = 500;

            newclient::Robot yellow = field.getRobot('y', 3);
            newclient::Robot blue = field.getRobot('b', 2);

            //std::cout << "yellow: (" << yellow.x_pos << ", " << yellow.y_pos << ").\n";
            //std::cout << "blue: (" << blue.x_pos << ", " << blue.y_pos << ").\n";
            //std::cout << "ball: (" << ball.x_pos << ", " << ball.y_pos << ").\n";



            if (is_yellow) // yellow will be offense
            {


            }
            else    // blue will be defence
            {
                /*
                 * Strategy: We want to say in a box in front of the goal, and position ourself such that
                 * we are blocking the point
                 */

                newclient::Radio::Payload pld(2);

                // we want to be facing towards center field



                pld.omega = aPID(blue.alpha + 3.14, 3.14);

                //pld.x_vel = xPID(blue.x_pos, 0); // * std::fmax(std::abs(std::cos(blue.alpha + 3.14)), .2);
                //pld.y_vel = yPID(blue.y_pos, 0); // * std::fmax(std::abs(std::sin(blue.alpha + 3.14)), .2);



                if (blue.y_pos < goal_neg_y - 600)
                {
                    double dir = atan2(goal_neg_y - blue.y_pos, goal_neg_x - blue.x_pos) - blue.alpha;
                    pld.omega = aPID(blue.alpha + 3.14, dir + 3.14);
                    pld.y_vel = yPID(blue.y_pos * sin(blue.alpha - dir), goal_neg_y);
                }
                else if (blue.y_pos > goal_pos_y + 600)
                {
                    double dir = atan2(goal_pos_y - blue.y_pos, goal_pos_x - blue.x_pos) - blue.alpha;
                    pld.omega = aPID(blue.alpha + 3.14, dir + 3.14);
                    pld.y_vel = yPID(blue.y_pos * sin(blue.alpha - dir), goal_pos_y);
                }


                if (blue.x_pos < goal_neg_x or blue.x_pos > goal_neg_x + 600)
                {
                    pld.x_vel = xPID(blue.x_pos, goal_neg_x + 300);
                }

                // solve point slope for the yellow bot and ball

                double slope = (yellow.y_pos - ball.y_pos) / (yellow.x_pos - ball.x_pos);

                // y - ball.y_pos = slope * (x - ball.x_pos) + ball.y_point

                double intersection = slope * (goal_neg_x + 100 - ball.x_pos) + ball.y_pos;

                if (intersection < goal_pos_y && intersection > goal_neg_y)
                {
                    double dir = atan2(intersection - blue.y_pos, goal_pos_x + 100 - blue.x_pos) - blue.alpha;
                    pld.y_vel = yPID(blue.y_pos * sin(blue.alpha - dir), intersection);
                    pld.x_vel = xPID(blue.x_pos * cos(blue.alpha - dir), goal_neg_x + 100);
                    pld.omega = aPID(blue.alpha + 3.14, dir + 3.14);
                }


                radio.sendCommand(pld);

                usleep(500);


            }
            /*

            // check to see if there is an obstical in the box between yellow and ball
            if (blue.x_pos > min(yellow.x_pos, ball.x_pos) && blue.x_pos < max(yellow.x_pos, ball.x_pos) &&
            blue.y_pos > min(yellow.y_pos, ball.y_pos) && blue.y_pos < max(yellow.y_pos, ball.y_pos))
            {

              std::cout << "turning to avoid robot at ";
              std::cout << blue.x_pos << ", " << blue.y_pos << '\n';

              /* need to find the line orthoganol to robot's differance slope and solve the two points on the
                 sphere of infulance of the obstical and choose the one closet to out line assuming our line
                 goes through the two points.



              double bee_line_slope = atan2(blue.y_pos - yellow.y_pos, blue.x_pos - yellow.x_pos) - yellow.alpha;
              if (bee_line_slope < 0)
            bee_line_slope += 2 * 3.14;

              double perp_slope = (-1) * (1.0 / bee_line_slope);

              // perp_line := y - (blue.y_pos) = perp_slope * (x - blue.x_pos)
              //		y = perp_slope * (x - blue.x_pos) + blue.y_pos

              // cirlcle of influence = (x - blue.x_pos) ^ 2 + (y - blue.y_pos) ^ 2 = r ^ 2

              // (x - blue.x_pos) ^ 2 + (perp_slope * x) ^ 2 = r ^ 2
              // (perp_slope ^ 2 + 1) * x ^ 2 + 2 * blue.x_pos * x + (blue.y_pos ^ 2 - r ^ 2 + blue.x_pos ^ 2 - 2 * blue.y_pos ^ 2 + blue.y_pos ^ 2) = 0
              //	A = perp_slope ^ 2 + 1
              //	B = 2 * blue.x_pos
              //	C = blue.y_pos ^ 2 - r ^ 2 + blue.x_pos ^ 2 - 2 * blue.y_pos ^ 2 + blue.y_pos ^ 2

              // p1_x = (-B - sqrt(B ^ 2 - 4 * A * C)) / 2 A
              // p1_y = perp_slope * p1_x + blue.x_pos

              // p2_x = p1_x = (-B + sqrt(B ^ 2 - 4 * A * C)) / 2 A
              // p1_y = perp_slope * p1_x + blue.x_pos

              double A = std::pow(perp_slope, 2) + 1;
              double B = 2 * blue.x_pos;
              double C = std::pow(blue.y_pos, 2) - std::pow(circ_inlf, 2) + std::pow(blue.x_pos, 2)
                 - std::pow(blue.y_pos, 2);

              double p1_x = ((-1) * B - std::sqrt(std::pow(B, 2) - 4 * A * C)) / 2 * A;
              double p1_y = perp_slope * p1_x + blue.x_pos;

              double p2_x = ((-1) * B + std::sqrt(std::pow(B, 2) - 4 * A * C)) / 2 * A;
              double p2_y = perp_slope * p2_x + blue.x_pos;

              std::cout << "p1: (" << p1_x << ", " << p1_y << ")\n";
              std::cout << "p2: (" << p2_x << ", " << p2_y << ")\n";



              double dif = atan2(p1_y - yellow.y_pos, p1_x - yellow.x_pos) - yellow.alpha;


              double dif = atan2(blue.y_pos - yellow.y_pos + 500, blue.x_pos - yellow.x_pos) - yellow.alpha;


              std::cout << "dif: " << dif << '\n';

              newclient::Radio::Payload payload(3, 0, 0, 0);

              if (abs(dif) > .4)
              {
              if (abs(dif) > .1)
              {
                  double omega = (dif < 3.14) ? 1 : -1;
                  payload.omega = omega;
              }
              }
              else
              {
              payload.y_vel = 1;
              }
              radio.sendCommand(payload);
            }
            else  // take the straight line between the yellow robot and ball
            {
              double dif = atan2(ball.y_pos - yellow.y_pos, ball.x_pos - yellow.x_pos) - yellow.alpha;

              if (dif < 0)
            dif += 2 * 3.14;

              newclient::Radio::Payload payload(3, 0, 0, 0);

              std::cout << "going to get the ball\n";
              std::cout << "dif: " << dif << '\n';


              if (abs(dif) > .4)
              {
              if (abs(dif) > .1)
              {
                  //std::cout << "turning to face, dif: " << dif << "\n";

                  double omega = (dif < 3.14) ? 1 : -1;

                  //std::cout << "omega: " << omega <<'\n';

                  payload.omega = omega;
              }

              } else if (sqrt(pow(yellow.x_pos - ball.x_pos, 2) + pow(yellow.y_pos - ball.y_pos, 2)) > 250)
              {
              //std::cout << "forward to meet ball: " << sqrt(pow(robot.x_pos - ball.x_pos,2) + pow(robot.y_pos - ball.y_pos, 2)) << "\n";
              payload.y_vel = 1;
              } else
              {
              std::cout << "ball in range!\n";
              break;
              }


              radio.sendCommand(payload);

          }
          */
        }
        else
        {
            std::cerr << "Could not locate two robots (" << robots.size() << ")\n";
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

