#include "communication.h"

namespace newclient
{
  void Radio::init()
  {
      my_nrf24l01p.disable();
      my_nrf24l01p.powerDown();
      wait_ms(20);
      my_nrf24l01p.powerUp();
      wait_ms(20);
      my_nrf24l01p.setTransferSize( TRANSFER_SIZE, NRF24L01P_PIPE_P0);
      if(my_nrf24l01p.getTransferSize( NRF24L01P_PIPE_P0) != TRANSFER_SIZE){
	  cout<< "nRF24 Error, RF module not initialized" << endl;
      }

      my_nrf24l01p.setRfOutputPower();
      my_nrf24l01p.setReceiveMode();
      my_nrf24l01p.setTxAddress(NRF24_ADDRESS_ROBO1, ADDRESS_WIDTH);
      cout<<"txAddress = " << NRF24_ADDRESS_ROBO1 << endl;
      cout<<"read txAddress = " << my_nrf24l01p.getTxAddress() << endl;
      if(my_nrf24l01p.getTxAddress() != NRF24_ADDRESS_ROBO1){
	  cout<< "tx address error" << endl;
      }
      my_nrf24l01p.setRxAddress((unsigned long long)NRF24_ADDRESS_SERVER, ADDRESS_WIDTH, NRF24L01P_PIPE_P0);
      cout<<"rxAddress = " << NRF24_ADDRESS_SERVER << endl;
      cout<<"read rxAddress = " << my_nrf24l01p.getRxAddress() << endl;
      if(my_nrf24l01p.getRxAddress() != NRF24_ADDRESS_SERVER){
	  cout<< "Rx address error" << endl;
      }

      my_nrf24l01p.enable();
  }

  
  void Radio::sendCommand(std::string payload)
  {

  }  
  
}