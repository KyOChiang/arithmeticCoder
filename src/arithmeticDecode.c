#include <stdio.h>
#include <malloc.h>
#include "arithmeticEncode.h"
#include "arithmeticDecode.h"
#include "dataType.h"

void getSymbolFromTag(Range *range, uint32 tag, CFT *cft, int tableSize){
  uint64 A, B;
  uint32 totalCount = cft[tableSize-1].cum_Freq;
  int tablePtr = 0;
  
  A = (tag - range->lower + 1);
  A = (A * totalCount) - 1;
  B = (uint64)range->upper - range->lower + 1;
  A = A / B;
  while(tablePtr < tableSize){
    if(A < cft[tablePtr].cum_Freq){
      printf("Symbol : %u\n", cft[tablePtr].symbol);
      break;
    }
    tablePtr = tablePtr + 1;
  }
}

void decoderScaling(Range *range, uint32 tag){
  uint32 upLimit = maskMSB(range->upper), lowLimit = maskMSB(range->lower);
  uint32 e3Up = e3Mask(range->upper), e3Low = e3Mask(range->lower);
  
  while((upLimit == lowLimit)||((e3Up == MSB10) && (e3Low == MSB01))){
    if(upLimit == lowLimit){                          // E1 || E2 condition
      range->upper = shiftToLeftBy1Bit(range->upper) + 1; 
      range->lower = shiftToLeftBy1Bit(range->lower);
      //tag = shiftToLeftBy1Bit(range->lower) + readNext;
    }
    if((e3Up == MSB10) && (e3Low == MSB01)){          // E3 condition
      range->upper = shiftToLeftBy1Bit(range->upper) + 1; 
      range->lower = shiftToLeftBy1Bit(range->lower);
      //tag = shiftToLeftBy1Bit(range->lower) + readNext;
      range->upper = (uint64)(range->upper) + 0x80000000;
      range->lower = range->lower & 0x7FFFFFFF;
      // tagMSBcomplement
    }
    upLimit = maskMSB(range->upper), lowLimit = maskMSB(range->lower);
    e3Up = e3Mask(range->upper), e3Low = e3Mask(range->lower);
  }
}

void arithmeticDecode(){

}