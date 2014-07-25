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

#endif