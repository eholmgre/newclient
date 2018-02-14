#include <iostream>
#include <thread>
#include <atomic>
#include <vector>
#include <string>
#include <cmath>
#include <ctime>

#include "vision.h"
#include "field.h"
#include "robot.h"
#include "communication.h"


int main(int argc, char **argv)
{
  std::cout << "Initalizing\n";
  
  newclient::Simulator radio;
  //radio.init();
  newclient::Field field;
  newclient::Vision vis(field);
  std::atomic<bool> run(true);
  std::thread receive(vis, &run);
  std::cout << "main continuing\n";
  
  time_t start;
  start = time(NULL);
  while (true)
  {
   
    std::string line;
    if (std::getline(std::cin, line))
    {
      if (!std::strcmp(line.c_str(), "stop"))
      {
	break;
      }
    }
    
   auto robots = field.getIDs();
   auto ball = field.getBall();
   
   if (robots.size())
   {
     newclient::Robot robot = field.getRobot(robots[0]);
     //std::cout << robot.getID() << ' ' << robot.x_pos << ' ' << robot.y_pos << ' ' << robot.alpha << '\n';
   
   
   //double dir = atan2(std::get<1>(robot.getCords()) - ball.y_pos, std::get<0>(robot.getCords()) - ball.x_pos);   
   double dif = ( atan2(ball.x_pos - robot.x_pos , ball.y_pos - robot.y_pos) + 3.14 + 1.57 - robot.alpha);
   
   newclient::Radio::Payload payload(3, 0, 0 ,0);
   
   if (dif > 3.15)
   {
     dif = -1 * (6.28 - dif); 
   }
   
   dif *= -1;
   
   std::cout << "dif: " << dif << '\n';
   
   
   if (abs(dif) > .6)
   {
     if (abs(dif) > .5)
     {
      std::cout << "turning to face, dif: " << dif << "\n";
      
      double omega = max(min(dif * .5, .25), -.25);
      
      std::cout << "omega: " << omega <<'\n';
      
      payload.omega = omega;
     }

   }
   
   else if (sqrt(pow(robot.x_pos - ball.x_pos,2) + pow(robot.y_pos - ball.y_pos, 2)) > 250)
   {
     std::cout << "forward to meet ball: " << sqrt(pow(robot.x_pos - ball.x_pos,2) + pow(robot.y_pos - ball.y_pos, 2)) << "\n";
     payload.y_vel = .42;
   }
   else
   {
     std::cout << "ball in range!\n";
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

