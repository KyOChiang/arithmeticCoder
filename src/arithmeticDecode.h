#ifndef ARITHMETIC_DECODE_H_
#define ARITHMETIC_DECODE_H_
#include "dataType.h"
#include "Stream.h"

void getSymbolFromTag(Range *range, uint32 tag, CFT *cft, int tableSize);
void decoderScaling(Range *range, uint32 tag);
void arithmeticDecode();

#endif