#ifndef STREAM_H_
#define STREAM_H_
#include <stdio.h>
#include "dataType.h"

typedef struct{
  char* buffer;
  int size;
  int length;
  int byteIndex;
  int bitIndex;
  FILE *file;
  char *filename;
}Stream;

Stream *openStream(char *f_Name, char *openMethod, int bufferSize);
void closeStream(Stream *stream);

void *streamFlush(Stream *out);

int streamWriteBit(Stream *out, int bit); //return how many bit write
int streamWriteByte(Stream *out, char decodeSymbol, int bitSize);

uint32 streamReadBit(Stream *in);
uint32 streamReadBits(Stream *in, int bitSize); //decide how many bit to read from the file
void streamReadBlock(Stream *in, char *buffer, int numOfBytes);
#endif