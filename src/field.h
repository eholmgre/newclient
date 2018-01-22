#ifndef newclient_field_h
#define newclient_field_h

#include <vector>
#include <mutex>
#include "robot.h"

namespace newclient
{

  class Field
  {
    std::mutex roboMtx;
    std::mutex ballMtx;
    class Ball
    {
    public:
      Ball(double x = 0, double y = 0) : x_pos(x), y_pos(y) {};
      double x_pos;
      double y_pos;
    };
    Ball ball;
    std::vector<Robot> robots;
  public:
    Field() {};
    void setRobot(char color, int id, double x, double y, double alpha);
    Robot &getRobot(char color, uint32_t id);
    Robot &getRobot(std::string idstr);
    void setBall(double x, double y);
    const Ball &getBall(void) const { return ball; };
    
    std::vector<std::string> getIDs();
  
  };
}

#endif