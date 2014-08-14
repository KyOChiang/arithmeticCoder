#ifndef STREAM_H_
#define STREAM_H_

typedef struct{
  char* buffer;
  int length;
  int byteIndex;
  int bitIndex;
}Stream;

Stream *openStream(char *fileName, char *openMethod, int bufferSize);
void *streamFlush(Stream *out);
int streamWriteBit(Stream *out, int bit); //return how many bit write
int streamWriteByte(Stream *out, char decodeSymbol, int bitSize);
int streamReadBit(Stream *in, int bitSize); //decide how many bit to read from the file
void streamReadBlock(Stream *in, char *buffer, int numOfBytes);
#endif