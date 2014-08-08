#include <stdio.h>
#include <malloc.h>
#include "arithmeticEncode.h"
#include "arithmeticDecode.h"
#include "dataType.h"

char getSymbolFromTag(Range *range, uint32 *tag, CFT *cft, int tableSize, Stream *out){
  uint64 A, B;
  uint32 totalCount = cft[tableSize-1].cum_Freq;
  int tablePtr = 0;
  char decodeSymbol;
  
  A = (*tag - range->lower + 1);
  A = (A * totalCount) - 1;
  B = (uint64)range->upper - range->lower + 1;
  A = A / B;
  while(tablePtr < tableSize){
    if(A < cft[tablePtr].cum_Freq){
      streamWriteByte(out,cft[tablePtr].symbol,8);
      decodeSymbol = cft[tablePtr].symbol;
      printf("%c\n",decodeSymbol);
      break;
    }
    tablePtr = tablePtr + 1;
  }
  return decodeSymbol;
}

void decoderScaling(Range *range, uint32 *tag, Stream *in){
  uint32 upLimit = maskMSB(range->upper), lowLimit = maskMSB(range->lower);
  uint32 e3Up = e3Mask(range->upper), e3Low = e3Mask(range->lower);
  while((upLimit == lowLimit)||((e3Up == MSB10) && (e3Low == MSB01))){
    if(upLimit == lowLimit){                          // E1 || E2 condition
      range->upper = shiftToLeftBy1Bit(range->upper) + 1; 
      range->lower = shiftToLeftBy1Bit(range->lower);
      *tag = shiftToLeftBy1Bit(*tag) | streamReadBit(in, 1);
    }
    if((e3Up == MSB10) && (e3Low == MSB01)){          // E3 condition
      range->upper = shiftToLeftBy1Bit(range->upper) + 1; 
      range->lower = shiftToLeftBy1Bit(range->lower);
      *tag = shiftToLeftBy1Bit(*tag) | streamReadBit(in, 1);
      range->upper = complementMSB(range->upper);
      range->lower = complementMSB(range->lower);
      *tag = complementMSB(*tag);
    }
    upLimit = maskMSB(range->upper), lowLimit = maskMSB(range->lower);
    e3Up = e3Mask(range->upper), e3Low = e3Mask(range->lower);
  }
}

// void arithmeticDecode(int dataLength, uint32 *tag, CFT *cft, int tableSize, Stream *out, Stream *in){
  // char decodeSymbol;
  // int success;
  // Range* range;
  // range = rangeNew();
  
  // while(dataLength != 0){
    // success = 0;
    // decodeSymbol = getSymbolFromTag(range, tag, cft, tableSize, out);
    // if(decodeSymbol != '\0')
      // success = 1;
    // dataLength = dataLength - success;
    // getRangeOfSymbol(range, decodeSymbol, cft, tableSize);
    // decoderScaling(range, tag, in);
  // }
// }