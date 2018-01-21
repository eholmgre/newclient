

/*	CSU Robocup 2017
 * 	Avpreet Singh, avpreetsingh@hotmail.com
 * 	---------------------------------------
 *  Stream parsing routines for CSU robocup
 *  * implements memcpy from string lib
 *  * Frame structure defined in source file
 *
 */


#ifndef __STREAM_H__
#define __STREAM_H__

#include <cstring>
typedef unsigned char uint8_t;

uint8_t parseFrameID(uint8_t *);
void parseFrameFloat(uint8_t *, float *);
void putFrameFloat(uint8_t, float, float, float, uint8_t *);

void parseFrameInt(uint8_t *, int *, int *, int *, int *);

#endif
