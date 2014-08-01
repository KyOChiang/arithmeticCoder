#include <stdio.h>
#include <malloc.h>
#include "arithmeticEncode.h"
#include "dataType.h"
#include "limits.h"

/*  Define keyword
 *  
 *  maskMSB           : To mask the 1st MSB of value
 *  e3Mask            : To mask the 1st and 2nd MSB of upper and lower in range
 *  MSB10             : IS a must that 1st and 2nd MSB of upper must be "10...." for E3 Scaling
 *  MSB01             : IS a must that 1st and 2nd MSB of lower must be "01...." for E3 Scaling
 *  shiftToLeftBy1Bit : Shift variable to left by 1 bit
 */
#define maskMSB(x) (x & 0x80000000)
#define e3Mask(x) (x & 0xC0000000)
#define MSB10 0x80000000
#define MSB01 0x40000000
#define shiftToLeftBy1Bit(x) (x<<1)

/*  dumpRange
 *  Function      : To print upper, lower and scale3.
 *
 *  Arguments
 *  range(in)     : Pass in Range struct to display data inside
 */
void dumpRange(Range *range){
  printf("Upper range: %x\n", range->upper);
  printf("Lower range: %x\n", range->lower);
  printf("Scale3 range: %u\n", range->scale3);
}

/*  rangeNew
 *  Function : To initialize a new range.
 *  
 *  return
 *  newRange : New range with lower = 0, upper = 0xFFFFFFFFL
 */
Range *rangeNew(){
  Range* newRange = malloc(sizeof(Range));
  
  newRange->upper = 0xFFFFFFFFL;
  newRange->lower = 0;
  newRange->scale3 = 0;
  //dumpRange(newRange);
  
  return newRange;
}

/*  getRangeOfSymbol
 *  Function    : To get the new interval of a symbol
 *  
 *  Arguments
 *  range(in/out)     : The current range with current upper limit and lower limit
 *  symbol(in)        : The input symbol required to get upper and lower limit
 *  tableSize(in)     : The size of CFT
 *  tbPtr(out)        : Index counter for CFT (Cumulative Frequency Table)
 *  rangeDiff(in)     : Subtraction of upper limit to lower limit from range
 *  tempL(out)        : temporary variable to store lower limit
 *  tempU(out)        : temporary variable to store upper limit
 *  low_Count(in)     : the lower limit for the input symbol
 *  up_Count(in)      : the upper limit for the input symbol
 *  total_Count(in)   : the cum_Freq of last symbol
 */
void getRangeOfSymbol(Range *range, uint32 symbol, CFT *cft,int tableSize){
  int tbPtr;
  uint64 rangeDiff, tempL, tempU;
  uint32 low_Count, up_Count, total_Count;
  
  rangeDiff = ((uint64)range->upper - range->lower) + 1;
  total_Count = cft[tableSize-1].cum_Freq;
  
  for(tbPtr = 0; tbPtr < tableSize; tbPtr++){
    if(symbol == cft[tbPtr].symbol){
      if(tbPtr == 0)
        low_Count = 0;
      else
        low_Count = cft[tbPtr-1].cum_Freq;
        
      up_Count = cft[tbPtr].cum_Freq;
      break;
    }
  }
  tempL = (rangeDiff * low_Count);
  tempL = tempL / total_Count;
  tempL = tempL + range->lower;
  
  tempU = (rangeDiff * up_Count);
  tempU = tempU / total_Count;
  tempU = tempU + range->lower;
  tempU = tempU - 1;
  
  range->lower = tempL;
  range->upper = tempU;
}

void rangeDel(Range *range){
  free(range);
}

/*  encoderScaling
 *  Function: To rescale the range, then transmit the encoder message.
 *            3 scales -> E1, E2, E3
 *            E1-> MSB of upper/lower are 0
 *            E2-> MSB of upper/lower are 1
 *            E3-> 1st and 2nd MSB of upper/lower are 10/01
 *
 *  Arguments
 *  range(in/out)     : The current range with current upper limit and lower limit
 *  out(out)          : To store the transmit message (encode value)
 *  upLimit(in)       : Used as mask to determine upper fulfill E1/E2 scaling condition
 *  lowLimit(in)      : Used as mask to determine lower fulfill E1/E2 scaling condition
 *  e3Up/e3Low(in)    : Used as mask to determine upper/lower fulfill E3 scaling condition
 *  transmitBit(out)  : Encode value to be sent out
 */
void encoderScaling(Range *range, Stream *out){
  int transmitBit;
  uint32 upLimit = maskMSB(range->upper), lowLimit = maskMSB(range->lower);
  uint32 e3Up = e3Mask(range->upper), e3Low = e3Mask(range->lower);
  
  while((upLimit == lowLimit)||((e3Up == MSB10) && (e3Low == MSB01))){
    if(upLimit == lowLimit){                          // E1 || E2 condition
      if(upLimit == 0 && lowLimit == 0){
       transmitBit = 0;
       streamWriteBit(out,transmitBit);
      }
      else{
        transmitBit = 1;
        streamWriteBit(out,transmitBit);
      }
      range->upper = shiftToLeftBy1Bit(range->upper) + 1; 
      range->lower = shiftToLeftBy1Bit(range->lower);
      while(range->scale3 > 0){
        streamWriteBit(out,!transmitBit);
        range->scale3 = range->scale3 - 1;
      }
    }
    if((e3Up == MSB10) && (e3Low == MSB01)){          // E3 condition
      range->scale3 = range->scale3 + 1;
      range->upper = shiftToLeftBy1Bit(range->upper) + 1; 
      range->lower = shiftToLeftBy1Bit(range->lower);
      range->upper = (uint64)(range->upper) + 0x80000000;
      range->lower = range->lower & 0x7FFFFFFF;
    }
    upLimit = maskMSB(range->upper), lowLimit = maskMSB(range->lower);
    e3Up = e3Mask(range->upper), e3Low = e3Mask(range->lower);
  }
}

/*  andMask32bit
 *  Function : Mask 32 unsigned int with 0x8000 0000
 *  
 *  Argument
 *  range(in) : Contain the upper and lower.
 */
void andMask32bit(Range *range){
  range->upper = (range->upper & 0x80000000);
  range->lower = (range->lower & 0x80000000);
}

/*  arithmeticEncode
 *  Function          : Encode data into tag
 *
 *  How               : 1. Initialize upper and lower of range with 0xFFFFFFFF and 0
 *                      2. If not EOF(replaced by number of inputs->dataLength)
 *                         Update the range->upper and range->lower(probability range for the symbol)
 *                      3. Perform the E1/E2/E3 scaling if necessary
 *                      4. Update the arrayPtr and dataLength and start over from step 2 again
 *                      5. If EOF, store the range->lower to lowTransmit, shift the 1st MSB and send out
 *                      6. Check scale3, if zero, transmit out all the remaining bits of lowTransmit
 *                         Else, send out 1 and decrease the scale3 by 1
 *  Arguments
 *  dataPtr(in)           : A pointer point to an array that store symbol
 *  dataLength(in)        : Total size of an array that store symbol
 *  cft(in)               : Cumulative Freq.(CF) Table that store symbol and their own CF
 *  tableSize(in)         : The size of CFT
 *  out(out)              : To store the transmit message (encode value)
 *  arrayPtr(in)          : Use to point the location of data from start
 *  lowTransmitCount(in)  : Total times to transmit the last range->lower
 *  lowTransmit(in)       : Temporary store range->lower and use for shift and MSB check
 */
void arithmeticEncode(int *dataPtr, int dataLength, CFT *cft, int tableSize, Stream *out){
  int arrayPtr = 0, lowTransmitCount = 32;
  uint32 lowTransmit;
  Range* range;
  range = rangeNew();
  
  while(dataLength != 0){
    getRangeOfSymbol(range, dataPtr[arrayPtr], cft, tableSize);
    printf("\n");
    dumpRange(range);
    encoderScaling(range,out);
    dumpRange(range);
    arrayPtr = arrayPtr + 1;
    dataLength = dataLength - 1;
  }
  lowTransmit = range->lower;
  
  while(lowTransmitCount!=0){
    if(maskMSB(lowTransmit) == 0x80000000)
      streamWriteBit(out,1);
    else
      streamWriteBit(out,0);
    
    while(range->scale3 > 0){
      streamWriteBit(out,1);
      range->scale3 = range->scale3 - 1;
    }
    lowTransmit = shiftToLeftBy1Bit(lowTransmit);
    lowTransmitCount = lowTransmitCount - 1;
  }
}











