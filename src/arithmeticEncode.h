#ifndef ARITHMETIC_ENCODE_H_
#define ARITHMETIC_ENCODE_H_
#include "dataType.h"
#include "Stream.h"

typedef struct{
  uint32 lower;
  uint32 upper;
  uint32 scale3;
}Range;

typedef struct{
  uint32 symbol;
  uint32 cum_Freq;
}CFT;

void dumpRange(Range *range);
Range *rangeNew();
void rangeDel(Range *range);
void getRangeOfSymbol(Range *range, uint32 symbol, CFT *cft,int tableSize);
void encoderScaling(Range *range, Stream *out);
void andMask32bit(Range *range);

#endif