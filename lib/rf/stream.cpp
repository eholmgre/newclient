
/*	CSU Robocup 2017
 * 	Avpreet Singh, avpreetsingh@hotmail.com
 * 	---------------------------------------
 *
 * 	Steam lib implementation for robocup
 * 	RF frame parsing
 *	RF Frame structure:
 *
 *  Frame length: 16 bytes
 *	-------------------------------------------------------
 *	| ID | Data ID | data | Data ID | data| Data ID | data|
 *	-------------------------------------------------------
 *	LSByte: 		frame identifier, IDs defined in seperate header file (periphConfig.h)
 *	2nd Byte: 		Data Identifier, i.e. float or int
 * 					'f' : 	float (single precision, 4 bytes)
 *					'i'	: 	integer	(signed short, 2 or 4 bytes)
 *	following 4 bytes: data
 */

#include "stream.h"
#include <iostream>


 uint8_t parseFrameID(uint8_t *_data){
 	return *(_data + 0);
 }

 void putFrameFloat(uint8_t _id, float _data1, float _data2, float _data3, uint8_t *_stream){
	//std::cout<< "_id = " << (int)_id << std::endl;
 	*(_stream + 0) = _id;
 	//std::cout<< "*stream[0] = " << (int)*(_stream) << std::endl;
 	memcpy((_stream + 2), &_data1, 4);
 	memcpy((_stream + 7), &_data2, 4);
 	memcpy((_stream + 12), &_data3, 4);
 	//std::cout<<"stream = ";
 	//for(int i = 0; i < 16; i ++)
 	//	std::cout<< (int)*(_stream + i) << " ";
 	//std::cout<< "\n";
 }


 void parseFrameFloat(uint8_t *_stream, float *_data){
 	uint8_t _dataType, _j = 0;
 	for(int _i = 2; _i < 13; _i = _i + 5){
 		memcpy((_data + _j), (_stream + _i), 4);
 		_j ++;
 	}
 }


 void parseFrameInt(uint8_t *_stream, int *_data1, int *_data2, int *_data3, int *_data4){
	 memcpy((_data1), (_stream + 0), 4);
	 memcpy((_data2), (_stream + 4), 4);
	 memcpy((_data3), (_stream + 8), 4);
	 memcpy((_data4), (_stream + 12), 4);
 }
