#ifndef newclient_robot_h
#define newclient_robot_h



namespace newclient
{
  class Robot
  {
    int id;
    double x_pos, y_pos, orientation;
    double x_speed, y_speed, theta;
  public:
    Robot(int id) : id(id) {};
  };
}

#endif