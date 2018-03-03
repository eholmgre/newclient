

namespace newclient
{
  class PID
  {
    const double _kp;
    const double _ki;
    const double _kd;
    
    double prev;
    double integ;
    
  public:
    PID(double kp, double ki, double kd) : _ki(ki), _kp(kp), _kd(kd) {};
    
    double operator()(double current, double target)
    {
      double error = target - current;
      
      double P = _kp * error;
      
      integ += error;
      double I = _ki * error;
      
      double delta = error - prev;
      double D = _ki * delta;
      
      prev = error;
      
      return  P + I + D;
    }
  };
  
}