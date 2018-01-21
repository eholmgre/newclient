#include <iostream>
#include <thread>

#include "vision.h"
#include "field.h"
#include "communication.h"


int main(int argc, char **argv)
{
  std::cout << "Initalizing\n";
  
  newclient::Radio radio;
  newclient::Field field;
  newclient::Vision vis(field);
  
  std::thread receive(vis);
  
  sleep(5000);
  vis.stop();
  
  receive.join();
  return 0; 
}


