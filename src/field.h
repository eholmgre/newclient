#ifndef newclient_field_h
#define newclient_field_h

#include <vector>
#include "robot.h"

namespace newclient
{

  class Field
  {
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
    void setRobot(int id, double x, double y);
    const Robot &getRobot(int id) const;
    void setBall(double x, double y) { ball.x_pos = x; ball.y_pos; };
    Ball getBal(void) { return Ball(ball.x_pos, ball.y_pos); };
  
  };
}

#endif