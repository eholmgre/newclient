#include <cmath>

namespace newclient
{
  class PID
  {
    const double _kp;
    const double _ki;
    const double _kd;
    
    double prev;
    double integ;
    
    double _min;
    double _max;
    bool limit = false;
    
    double _amp = 1;
    
  public:
    PID(double kp, double ki, double kd) : _ki(ki), _kp(kp), _kd(kd) {};
    
    PID(double kp, double ki, double kd, double min, double max) : _ki(ki), _kp(kp), _kd(kd),
								   _min(min), _max(max) { limit = true; };
								   
    PID(double kp, double ki, double kd, double min, double max, double amp) : _ki(ki), _kp(kp), _kd(kd),
								   _min(min), _max(max), _amp(amp) { limit = true; };

    
    double operator()(double current, double target)
    {
      double error = target - current;
      
      double P = _kp * error;
      
      integ += error;
      double I = _ki * integ;
      
      double delta = error - prev;
      double D = _kd * delta;
      
      prev = error;
      
      double total = (P + I + D) * _amp;
      
      if (limit)
      {
	if (total > _max)
	  total = _max;
	else if (total < _min)
	  total = _min;
	  
	// total = std::fmin(std::fmax(total, _min), _max);
      }
      
      return  total;
    }
  };
  
}