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
    std::vector<Robot> team1;
    std::vector<Robot> team2;
  public:
    Field() {};
    void setRobot(int team, int id, double x, double y, double alpha);
    const Robot &getRobot(int id) const;
    void setBall(double x, double y);
    const Ball &getBal(void) const { return ball; };
  
  };
}

#endif