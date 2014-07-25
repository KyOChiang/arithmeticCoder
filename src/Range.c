#include <stdio.h>
#include <malloc.h>
#include "Range.h"
#include "dataType.h"
#include "limits.h"

/*  dumpRange
 *  Function : To print upper, lower and scale3.
 */
void dumpRange(Range *range){
  printf("Upper range: %u\n", range->upper);
  printf("Lower range: %u\n", range->lower);
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
 *  range       : The current range with current upper limit and lower limit
 *  symbol      : The input symbol required to get upper and lower limit
 *  tbPtr       : Index counter for CFT (Cumulative Frequency Table)
 *  rangeDiff   : Subtraction of upper limit to lower limit from range
 *  tempL       : temporary variable to store lower limit
 *  tempU       : temporary variable to store upper limit
 *  low_Count   : the lower limit for the input symbol
 *  up_Count    : the upper limit for the input symbol
 *  total_Count : the cum_Freq of last symbol
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
  // printf("ub : %u\n",range->upper);
  // printf("lb : %u\n",range->lower);
  
  tempL = (rangeDiff * low_Count);
  tempL = tempL / total_Count;
  tempL = tempL + range->lower;
  
  tempU = (rangeDiff * up_Count);
  tempU = tempU / total_Count;
  tempU = tempU + range->lower;
  tempU = tempU - 1;
  
  range->lower = tempL;
  range->upper = tempU;
  
  // printf("range different : %llu\n",rangeDiff);
  // printf("cum_count - 1 : %u\n",low_Count);
  // printf("cum_count :%u\n",up_Count);
  // printf("total_count : %u\n",total_Count);
  // printf("ua : %u\n",range->upper);
  // printf("la : %u\n",range->lower);
}














