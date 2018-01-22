#include "field.h"
#include <iostream>

namespace newclient
{
  void Field::setRobot(char color, int id, double x, double y, double alpha)
  {
    std::lock_guard<std::mutex> guard(roboMtx);
        
    bool found = false;
    for (Robot &robo : robots)
      if (robo.id == id && robo.color == color) {
	robo.x_pos = x;
	robo.y_pos = y;
	robo.alpha = alpha;
	found = true;
      }
    
    if (!found)
    {
      robots.push_back(Robot(color, id, x, y, alpha));
    }
  }
  
  void Field::setBall(double x, double y)
  {
    std::lock_guard<std::mutex> guard(ballMtx);
    
    ball.x_pos = x;
    ball.y_pos = y;
  }
  
Robot& Field::getRobot(char color, uint32_t id)
{
  for (Robot &robo : robots)
    if (robo.color == color && robo.id == id)
      return std::ref(robo);
}

Robot& Field::getRobot(std::string idstr)
{
  for (auto robo : robots)
    if (std::string(robo.color + std::to_string(robo.id)) == idstr)
      return std::ref(robo);
}

  
  
  std::vector<std::string> Field::getIDs()
  {
    std::vector<std::string> ids;
    
    for (const Robot &robot : robots)
      ids.push_back(robot.getID());
   
    return ids;
  }
  
}