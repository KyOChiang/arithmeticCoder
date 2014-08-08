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
  char symbol;
  uint32 cum_Freq;
  uint32 occurNo;
}CFT;

void dumpRange(Range *range);
Range *rangeNew();
void rangeDel(Range *range);
void getRangeOfSymbol(Range *range, char symbol, CFT *cft,int tableSize);
void encoderScaling(Range *range, Stream *out);
void andMask32bit(Range *range);
void arithmeticEncode(char *dataPtr, int dataLength, CFT *cft, int tableSize, Stream *out);
CFT *cftNew(Stream *in);

#endif