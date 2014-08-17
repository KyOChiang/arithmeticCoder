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
void dumpCFT(CFT* cft, int index);

CFT *cftNew(Stream *in, int* tableSize);
Range *rangeNew();

void rangeDel(Range *range);
void andMask32bit(Range *range);

void getRangeOfSymbol(Range *range, char symbol, CFT *cft,int tableSize);
void encoderScaling(Range *range, Stream *out);
void arithmeticEncode(Stream *in, int *dataLength, CFT *cft, int tableSize, Stream *out);

#endif