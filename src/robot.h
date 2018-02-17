#ifndef newclient_robot_h
#define newclient_robot_h

#include <string>

namespace newclient
{
    class Robot
    {
    public:
        char color;
        uint32_t id;
        double x_pos, y_pos, alpha;
        double x_speed, y_speed, omega;

        Robot(char color, uint32_t id, double x_pos, double y_pos, double alpha) : color(color), id(id), x_pos(x_pos),
                                                                                   y_pos(y_pos), alpha(alpha)
        {};

        std::string getID() const
        { return std::string(color + std::to_string(id)); };
    };
}

#endif