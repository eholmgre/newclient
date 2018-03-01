#include <iostream>
#include <thread>
#include <atomic>
#include <vector>
#include <string>
#include <cmath>
#include <ctime>
#include <csignal>
#include <cstdlib>
#include <unistd.h>


#include "vision.h"
#include "field.h"
#include "robot.h"
#include "communication.h"

int main(int argc, char **argv)
{
    std::cout << "Initalizing\n";

    newclient::Simulator radio;
    radio.init();
    newclient::Field field;
    newclient::Vision vis(field);
    std::atomic<bool> run(true);
    std::thread receive(vis, &run);
    std::cout << "main continuing\n";

    time_t start;
    start = time(NULL);
    while (run)
    {
        auto robots = field.getIDs();
        auto ball = field.getBall();

        if (robots.size() >= 2)
        {
            newclient::Robot yellow = field.getRobot(robots[1]);
	    newclient::Robot blue = field.getRobot(robots[0]);
	    
	    std::cout << "yellow: (" << yellow.x_pos << ", " << yellow.y_pos << ").\n";
	    std::cout << "blue: (" << blue.x_pos << ", " << blue.y_pos << ").\n";
	    std::cout << "ball: (" << ball.x_pos << ", " << ball.y_pos << ").\n";
	    
	    
	    // check to see if there is an obstical in the box between yellow and ball
	    if (blue.x_pos > min(yellow.x_pos, ball.x_pos) && blue.x_pos < max(yellow.x_pos, ball.x_pos) &&
		blue.y_pos > min(yellow.y_pos, ball.y_pos) && blue.y_pos < max(yellow.y_pos, ball.y_pos))
	    {
	      
	      std::cout << "turning to avoid robot at ";
	      std::cout << blue.x_pos << ", " << blue.y_pos << '\n';
	      
	      /* need to find the line orthoganol to robot's differance slope and solve the two points on the
	         sphere of infulance of the obstical and choose the one closet to out line assuming our line
	         goes through the two points. */
	      
	      double dif = atan2(blue.y_pos + 500 - yellow.y_pos, blue.x_pos - yellow.x_pos) - yellow.alpha;
	      if (dif < 0)
		dif += 2 * 3.14;
	      
	      std::cout << "dif: " << dif << '\n';
	    
	      newclient::Radio::Payload payload(3, 0, 0, 0);
	    
	      if (abs(dif) > .4)
	      {
		  if (abs(dif) > .1)
		  {
		      double omega = (dif < 3.14) ? 1 : -1;
		      payload.omega = omega;
		  }
	      }
	      else
	      {
		  payload.y_vel = 1;
	      }
	      radio.sendCommand(payload);
	    }
	    else  // take the straight line between the yellow robot and ball
	    {
	      double dif = atan2(ball.y_pos - yellow.y_pos, ball.x_pos - yellow.x_pos) - yellow.alpha;
	      
	      if (dif < 0)
		dif += 2 * 3.14;

	      newclient::Radio::Payload payload(3, 0, 0, 0);

	      std::cout << "going to get the ball\n";
	      std::cout << "dif: " << dif << '\n';


	      if (abs(dif) > .4)
	      {
		  if (abs(dif) > .1)
		  {
		      //std::cout << "turning to face, dif: " << dif << "\n";

		      double omega = (dif < 3.14) ? 1 : -1;

		      //std::cout << "omega: " << omega <<'\n';

		      payload.omega = omega;
		  }

	      } else if (sqrt(pow(yellow.x_pos - ball.x_pos, 2) + pow(yellow.y_pos - ball.y_pos, 2)) > 250)
	      {
		  //std::cout << "forward to meet ball: " << sqrt(pow(robot.x_pos - ball.x_pos,2) + pow(robot.y_pos - ball.y_pos, 2)) << "\n";
		  payload.y_vel = 1;
	      } else
	      {
		  std::cout << "ball in range!\n";
		  break;
	      }
	      radio.sendCommand(payload);
	  }
	}
	else
	  std::cerr << "Could not locate two robots\n";
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

