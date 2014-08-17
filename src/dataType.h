#ifndef DATATYPE_H_
#define DATATYPE_H_

#include <stdio.h>
#include "CException.h"
#include <malloc.h>

#define uint32 unsigned int
#define uint64 unsigned long long
#define uint8 unsigned char

typedef enum { NO_ERROR,
               ERR_END_OF_FILE,
               ERR_FILE_NOT_EXIST
} ExceptionError;

/*  Define keyword
 *
 *  maskMSB           : To mask the 1st MSB of value
 *  mask1ByteMSB      : To mask the 1st MSB of 1 Byte value
 *  e3Mask            : To mask the 1st and 2nd MSB of upper and lower in range
 *  MSB10             : IS a must that 1st and 2nd MSB of upper must be "10...." for E3 Scaling
 *  MSB01             : IS a must that 1st and 2nd MSB of lower must be "01...." for E3 Scaling
 *  shiftToLeftBy1Bit : Shift variable to left by 1 bit
 *  complementMSB     : To complement the MSB only
 */
#define maskMSB(x) (x & 0x80000000)
#define mask1ByteMSB(x) (x & 0x80)
#define e3Mask(x) (x & 0xC0000000)
#define MSB10 0x80000000
#define MSB01 0x40000000
#define shiftToLeftBy1Bit(x) (x<<1)
#define complementMSB(x) (x ^ 0x80000000)

#endif