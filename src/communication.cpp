#include "communication.h"

namespace newclient
{
  void Radio::init()
  {
      my_nrf24l01p.disable();
      my_nrf24l01p.powerDown();
      usleep(200000);
      my_nrf24l01p.powerUp();
      usleep(200000);
      my_nrf24l01p.setTransferSize( TRANSFER_SIZE, NRF24L01P_PIPE_P0);
      if(my_nrf24l01p.getTransferSize( NRF24L01P_PIPE_P0) != TRANSFER_SIZE){
	  std::cout<< "nRF24 Error, RF module not initialized\n";
      }

      my_nrf24l01p.setRfOutputPower();
      my_nrf24l01p.setReceiveMode();
      my_nrf24l01p.setTxAddress(NRF24_ADDRESS_ROBO1, ADDRESS_WIDTH);
      std::cout << "txAddress = " << NRF24_ADDRESS_ROBO1 << "\n";
      std::cout << "read txAddress = " << my_nrf24l01p.getTxAddress() << "\n";
      if(my_nrf24l01p.getTxAddress() != NRF24_ADDRESS_ROBO1){
	  std::cout << "tx address error\n";
      }
      my_nrf24l01p.setRxAddress((unsigned long long)NRF24_ADDRESS_SERVER, ADDRESS_WIDTH, NRF24L01P_PIPE_P0);
      std::cout<<"rxAddress = " << NRF24_ADDRESS_SERVER << "\n";
      std::cout<<"read rxAddress = " << my_nrf24l01p.getRxAddress() << "\n";
      if(my_nrf24l01p.getRxAddress() != NRF24_ADDRESS_SERVER){
	  std::cout<< "Rx address error\n";
      }

      my_nrf24l01p.enable();
      
      kp = 55;
      ki = 0.0;
      kd = 12;
      
      putFrameFloat(1, 3, kp, ki, kd, (uint8_t *)txBuffer);
      my_nrf24l01p.write( NRF24L01P_PIPE_P0, txBuffer, TRANSFER_SIZE);
      std::cout << "Radio initalized\n";
  }

  
  void Radio::sendCommand(Payload &payload)
  {
   putFrameFloat(0, payload.id, payload.x_vel, payload.y_vel, payload.omega, (uint8_t *)txBuffer);
    my_nrf24l01p.write( NRF24L01P_PIPE_P0, txBuffer, TRANSFER_SIZE);
  }  
  
}