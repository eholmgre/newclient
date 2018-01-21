#ifndef newclient_robot_h
#define newclient_robot_h



namespace newclient
{
  class Robot
  {
  public:
    int id;
    double x_pos, y_pos, alpha;
    double x_speed, y_speed, omega;
    Robot(int id) : id(id) {};
    Robot(int id, double x_pos, double y_pos, double alpha) : id(id), x_pos(x_pos), y_pos(y_pos), alpha(alpha) {};
  };
}

#endif