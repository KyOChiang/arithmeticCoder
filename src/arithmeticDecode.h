#ifndef ARITHMETIC_DECODE_H_
#define ARITHMETIC_DECODE_H_
#include "dataType.h"
#include "Stream.h"
#include "arithmeticEncode.h"

char getSymbolFromTag(Range *range, uint32 *tag, CFT *cft, int tableSize, Stream *out);
void decoderScaling(Range *range, uint32 *tag, Stream *in);
void arithmeticDecode(int *dataLength, uint32 *tag, CFT *cft, int tableSize, Stream *out, Stream *in);
void tagReader(Stream *in, uint32 *tag);
#endif