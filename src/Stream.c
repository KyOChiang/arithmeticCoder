#include <stdio.h>
#include <malloc.h>
#include "Stream.h"
#include "dataType.h"

/*  openStream
 *
 *  Function      : To open or create a file and create Stream structure.
 *
 *  Arguments
 *  f_Name(in)    : The file name going to open or create
 *  openMethod(in): The operate method for file, either read ("r") or write ("w")
 *  bufferSize(in): The size of buffer in byte
 *
 *  Return
 *  newStream     : Stream structure that create recently.
 */
Stream *openStream(char *f_Name, char *openMethod, int bufferSize){

  Stream* newStream = calloc(sizeof(Stream),1);
  newStream->file = fopen(f_Name,openMethod);
  if(newStream->file == NULL){
    printf("Error: cannot open the file %s\n",f_Name);
    Throw(ERR_FILE_NOT_EXIST);
  }
  newStream->size = bufferSize;
  newStream->length = 0;
  newStream->bitIndex = 0;
  newStream->byteIndex = 0;
  newStream->filename = f_Name;

  return newStream;
}

/*  closeStream
 *
 *  Function : Close the file and free the Stream structure.
 *
 *  Arguments
 *  stream(in)  : Stream structure that contain the message related file and buffer.
 */
void closeStream(Stream *stream){
  fclose(stream->file);
  free(stream);
}

uint32 streamReadBits(Stream *in, int bitSize){

}