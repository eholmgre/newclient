


#include <iostream>
#include "nRF24L01P.h"
#include "stream.h"
#include "csuRobocup_radioDef.h"


nRF24L01P my_nrf24l01p;

using namespace std;

void wait_ms(unsigned long int);


char rxBuffer[TRANSFER_SIZE];
char txBuffer[TRANSFER_SIZE];// = "012345678912345";

float kp, ki, kd, maxSum, maxITerm, xVel, yVel, wVel;
int mtrV1, mtrV2, mtrV3, mtrV4;

int main() {

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

    /*
    //---------------------------------------------------
    putFrameFloat(ID_PID_K, 5.123, 4.152, 9.154, (uint8_t *)txBuffer);

    cout<< "txBuffer = " ;
    for(int i = 0; i < 16; i ++)
    	cout<< (int)txBuffer[i] << " ";

   cout<< endl;
   my_nrf24l01p.write( NRF24L01P_PIPE_P0, txBuffer, TRANSFER_SIZE);

   cout<<"write ok" << endl;
    //--------------------------------------------------
	*/

    cout<< "enter kp" << endl;
    cin>> kp;
    cout<< "enter ki" << endl;
    cin>> ki;
    cout<< "enter kd" << endl;
    cin>> kd;
    cout<< "enter vel" << endl;
    cin>> yVel;
    //putFrameFloat(ID_PID_K, kp, ki, kd, (uint8_t *)txBuffer);


    putFrameFloat(ID_PID_K, kp, ki, kd, (uint8_t *)txBuffer);
    my_nrf24l01p.write( NRF24L01P_PIPE_P0, txBuffer, TRANSFER_SIZE);

    wait_ms(500);

   putFrameFloat(ID_ROBO_VEL, (float)0.0, yVel, 0.0, (uint8_t *)txBuffer);
    my_nrf24l01p.write( NRF24L01P_PIPE_P0, txBuffer, TRANSFER_SIZE);



    while(1){
        if(my_nrf24l01p.readable(NRF24L01P_PIPE_P0) == 1){
    		my_nrf24l01p.read(NRF24L01P_PIPE_P0, rxBuffer, TRANSFER_SIZE );
    		//cout<<"rRF read\n";
    		//cout<< "rxbuffer :";
    		//for(int i = 0; i < TRANSFER_SIZE; i++)
    			//cout<< rxBuffer[i];

    		//cout<<"\n";

    		parseFrameInt((uint8_t *)rxBuffer, &mtrV1, &mtrV2, &mtrV3, &mtrV4);

    		cout<< "v1 = " << mtrV1 << " | v2 = " << mtrV2 << " | v3 = " << mtrV3 << " | v4 = " << mtrV4 << endl;

    	}
    }

    my_nrf24l01p.disable();



}

void wait_ms(unsigned long int _waitTime){
	std::chrono::steady_clock::time_point timerStart = std::chrono::steady_clock::now();
	while((int)std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::steady_clock::now() - timerStart).count() <= _waitTime);
}

