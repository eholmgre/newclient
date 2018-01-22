#include <iostream>
#include <thread>
#include <atomic>
#include <vector>
#include <cmath>

#include "vision.h"
#include "field.h"
#include "robot.h"
#include "communication.h"


int main(int argc, char **argv)
{
  std::cout << "Initalizing\n";
  
  newclient::Radio radio;
  radio.init();
  newclient::Field field;
  newclient::Vision vis(field);
  std::atomic<bool> run(true);
  std::thread receive(vis, &run);
  std::cout << "main continuing\n";
  
  while (true)
  {
   auto robots = field.getIDs();
   auto ball = field.getBall();
   
   if (robots.size())
   {
     newclient::Robot robot = field.getRobot(robots[0]);
     //std::cout << robot.getID() << ' ' << robot.x_pos << ' ' << robot.y_pos << ' ' << robot.alpha << '\n';
   
   
   //double dir = atan2(std::get<1>(robot.getCords()) - ball.y_pos, std::get<0>(robot.getCords()) - ball.x_pos);   
   double dif = (atan2(ball.x_pos - robot.x_pos , ball.y_pos - robot.y_pos) + (3.1415 / 2) - 3.14 - robot.alpha) * -1;
   
   newclient::Radio::Payload payload(3, 0, 0 ,0);

   if (abs(dif) > 1)
   {
     std::cout << "turning to face, dif: " << dif << "\n";
     payload.omega = min(dif * .5, .4);
     radio.sendCommand(payload);
   }
   
   else if (abs(robot.x_pos - ball.x_pos) > 5 && abs(robot.y_pos - ball.y_pos) > 5)
   {
     std::cout << "forward to meet ball: " << sqrt(pow(robot.x_pos - ball.x_pos,2) + pow(robot.y_pos - ball.y_pos, 2)) << "\n";
     payload.x_vel = .4;
     radio.sendCommand(payload);
   }
   else
     radio.sendCommand(payload);
     std::cout << "ball in range!\n";
   
   //std::cout << dif << '\n';
    
    
   }
  }
  
  
  run.store(false);
  std::cout << "bool changed to " << run.load() << "\n";

  receive.join();
  
  return 0; 
}

