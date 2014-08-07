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