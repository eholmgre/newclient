#include "field.h"

namespace newclient
{
  void Field::setRobot(int team, int id, double x, double y, double alpha)
  {
    std::lock_guard<std::mutex> guard(roboMtx);
    
    std::vector<Robot> &robots = (team ==1) ? team1 : team2;
    
    bool found = false;
    for (Robot &robo : robots)
      if (robo.id == id) {
	robo.x_pos = x;
	robo.y_pos = y;
	robo.alpha = alpha;
	found = true;
      }
    
    if (!found)
    {
      robots.push_back(Robot(id, x, y, alpha));
    }
  }
  
  void Field::setBall(double x, double y)
  {
    std::lock_guard<std::mutex> guard(ballMtx);
    
    ball.x_pos = x;
    ball.y_pos = y;
  }
}