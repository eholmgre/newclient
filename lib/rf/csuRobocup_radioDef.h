/*	CSU Robocup 2017
 * 	Avpreet Singh, avpreetsingh@hotmail.com
 * 	---------------------------------------
 *
 * 	Robo Frame ID defines
 * 	(Note: 	Crosscheck with the defines in the firmware.
 * 			Filename: "periphConfig.h")
 *
 */

#ifndef __CSUROBOCUP_RADIODEF__
#define __CSUROBOCUP_RADIODEF__



#define PI 					3.14159
#define CRTL_SAMPLING_TIME_mS	15
#define ENCODER_CPR			48			// counts per revolution
#define GEAR_RATIO			20.4
#define WHEEL_DIAMETER		0.045 		// meters
#define VEL_TO_CNTS_PS(_VEL)	((_VEL * GEAR_RATIO * ENCODER_CPR * (CRTL_SAMPLING_TIME_mS/1000))/(WHEEL_DIAMETER * PI))
#define CNTS_TO_VEL(_CNTS)		((_CNTS * WHEEL_DIAMETER * PI)/(GEAR_RATIO * ENCODER_CPR * (CRTL_SAMPLING_TIME_mS/1000)))


#define TRANSFER_SIZE   16
#define ADDRESS_WIDTH 	5
#define NRF24_ADDRESS_SERVER	0x464332304D
// address, ascii: FC201
// FC2: Fort Collins Football Club
// 0X: robot index
#define NRF24_ADDRESS_ROBO1 	0x4643323031
#define NRF24_ADDRESS_ROBO2 	0x4643323032
#define NRF24_ADDRESS_ROBO3 	0x4643323033
#define NRF24_ADDRESS_ROBO4 	0x4643323034
#define NRF24_ADDRESS_ROBO5 	0x4643323035
#define NRF24_ADDRESS_ROBO6 	0x4643323036

//unsigned long long int roboAddressBase = 0x4643323000;



enum nrfFrameID{
	ID_ROBO_VEL,
	ID_PID_K,
	ID_PID_LIMITS,

	ID_ROBO_1,
	ID_ROBO_2,
	ID_ROBO_3,
	ID_ROBO_4,
	ID_ROBO_5,
	ID_ROBO_6,

	ID_MOTOR_1_DIR,
	ID_MOTOR_2_DIR,
	ID_MOTOR_3_DIR,
	ID_MOTOR_4_DIR,

	ID_MOTOR_1_PWM,
	ID_MOTOR_2_PWM,
	ID_MOTOR_3_PWM,
	ID_MOTOR_4_PWM,

	ID_MOTOR_1_VEL
};


#endif
