#include <iostream>
#include <thread>

#include "vision.h"


int main(int argc, char **argv)
{
  std::cout << "Initalizing\n";
  
  newclient::Vision vis;
  
  std::thread receive(vis);
  
  sleep(5000);
  vis.stop();
  
  receive.join();
  return 0; 
}


