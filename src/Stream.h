#ifndef STREAM_H_
#define STREAM_H_
#include "dataType.h"

typedef struct{
  uint8* buffer;
  uint8 currentByte;
  int byteIndex;
  int bitIndex;
  FILE *file;
  char *filename;
}Stream;

Stream *openStream(char *f_Name, char *openMethod);
void closeStream(Stream *stream);

void streamFlush(Stream *out);

void streamWriteBit(Stream *out, int inputBit);
void streamWriteByte(Stream *out, char decodeSymbol);

uint32 streamReadBit(Stream *in);
uint32 streamReadBits(Stream *in, int bitSize); //decide how many bit to read from the file
#endif