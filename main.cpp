#include <iostream>
#include "client.h"


int main(int argc, char **argv)
{
  std::cout << "Initalizing\n";
  
  Client client;
  
  client.run();
  return 0; 
}


