#include "unity.h"
#include "Stream.h"
#include "dataType.h"

void setUp(void){}
void tearDown(void){}

/////////////////////
// openStream
////////////////////
void test_openStream_to_open_a_file_with_read_mode_should_throw_error(){
  CEXCEPTION_T error;
  Stream* fileStream = NULL;

  Try{
    fileStream = openStream("textSample.txt","r");
    TEST_FAIL_MESSAGE("No exception thrown.");
  }Catch(error){
    TEST_ASSERT_EQUAL(ERR_FILE_NOT_EXIST,error);
  }
  if(fileStream != NULL){
    closeStream(fileStream);
  }
}

void test_openStream_to_open_file_with_write_mode_should_create_testSample_1_txt(){
  CEXCEPTION_T error;
  Stream* fileStream = NULL;

  Try{
    fileStream = openStream("textSample_2.txt","w");
  }Catch(error){
    TEST_ASSERT_EQUAL(ERR_FILE_NOT_EXIST,error);
  }
  TEST_ASSERT_EQUAL(0,fileStream->bitIndex);
  TEST_ASSERT_EQUAL(0,fileStream->byteIndex);
  TEST_ASSERT_EQUAL("textSample_2.txt",fileStream->filename);
  if(fileStream != NULL){
    closeStream(fileStream);
  }
}

void test_openStream_to_open_file_with_read_mode_should_read_testSample_1_txt(){
  CEXCEPTION_T error;
  Stream* fileStream = NULL;

  Try{
    fileStream = openStream("textSample_1.txt","r");
  }Catch(error){
    TEST_ASSERT_EQUAL(ERR_FILE_NOT_EXIST,error);
  }
  TEST_ASSERT_EQUAL(0,fileStream->bitIndex);
  TEST_ASSERT_EQUAL(0,fileStream->byteIndex);
  TEST_ASSERT_EQUAL("textSample_1.txt",fileStream->filename);
  if(fileStream != NULL){
    closeStream(fileStream);
  }
}

/////////////////////////
//  streamReadBits / streamReadBit
////////////////////////

void test_streamReadBits_to_read_1_char_from_file(){
  CEXCEPTION_T error;
  int value;
  Stream* fileStream = NULL;

  Try{
    fileStream = openStream("textSample_1.txt","r");
    value = streamReadBits(fileStream,8);
  }Catch(error){
    TEST_ASSERT_EQUAL(ERR_END_OF_FILE,error);
  }
  TEST_ASSERT_EQUAL('q',value);
  if(fileStream != NULL){
    closeStream(fileStream);
  }
}

void test_streamReadBits_to_read_5_char_from_file(){
  CEXCEPTION_T error;
  int value;
  Stream* fileStream = NULL;

  Try{
    fileStream = openStream("textSample_1.txt","r");
    value = streamReadBits(fileStream,8);
    value = streamReadBits(fileStream,8);
    value = streamReadBits(fileStream,8);
    value = streamReadBits(fileStream,8);
    value = streamReadBits(fileStream,8);
  }Catch(error){
    TEST_ASSERT_EQUAL(ERR_END_OF_FILE,error);
  }
  TEST_ASSERT_EQUAL('1',value);
  if(fileStream != NULL){
    closeStream(fileStream);
  }
}

void test_streamReadBits_to_read_6_char_from_file_should_throw_error_because_EOF(){
  CEXCEPTION_T error;
  int value;
  Stream* fileStream = NULL;

  Try{
    fileStream = openStream("textSample_1.txt","r");
    value = streamReadBits(fileStream,8);
    value = streamReadBits(fileStream,8);
    value = streamReadBits(fileStream,8);
    value = streamReadBits(fileStream,8);
    value = streamReadBits(fileStream,8);
    value = streamReadBits(fileStream,8);
    TEST_FAIL_MESSAGE("No exception thrown.");
  }Catch(error){
    TEST_ASSERT_EQUAL(ERR_END_OF_FILE,error);
  }
  if(fileStream != NULL){
    closeStream(fileStream);
  }
}

void test_streamReadBits_to_read_4_bit_from_file(){
  CEXCEPTION_T error;
  int value;
  Stream* fileStream = NULL;
  // First byte is 'q', it has binary value of 0111 0001
  // So, the first 4 bits read in should be 0111
  Try{
    fileStream = openStream("textSample_1.txt","r");
    value = streamReadBits(fileStream,1);
    TEST_ASSERT_EQUAL(0,value);
    value = streamReadBits(fileStream,1);
    TEST_ASSERT_EQUAL(1,value);
    value = streamReadBits(fileStream,1);
    TEST_ASSERT_EQUAL(1,value);
    value = streamReadBits(fileStream,1);
    TEST_ASSERT_EQUAL(1,value);
  }Catch(error){
    TEST_ASSERT_EQUAL(ERR_END_OF_FILE,error);
  }
  if(fileStream != NULL){
    closeStream(fileStream);
  }
}

void test_streamReadBits_to_read_10_bit_should_read_across_boundary(){
  CEXCEPTION_T error;
  int value;
  Stream* fileStream = NULL;
  
  // First byte is 'q' (0111 0001), second byte is 'a' (0110 0001)
  // So, the first 8 bits read in should be 0111 0001
  // Now, it need to read 2 more bits from a, it should be 01
  Try{
    fileStream = openStream("textSample_1.txt","r");
    value = streamReadBits(fileStream,1);
    TEST_ASSERT_EQUAL(0,value);
    value = streamReadBits(fileStream,1);
    TEST_ASSERT_EQUAL(1,value);
    value = streamReadBits(fileStream,1);
    TEST_ASSERT_EQUAL(1,value);
    value = streamReadBits(fileStream,1);
    TEST_ASSERT_EQUAL(1,value);
    value = streamReadBits(fileStream,1);
    TEST_ASSERT_EQUAL(0,value);
    value = streamReadBits(fileStream,1);
    TEST_ASSERT_EQUAL(0,value);
    value = streamReadBits(fileStream,1);
    TEST_ASSERT_EQUAL(0,value);
    value = streamReadBits(fileStream,1);
    TEST_ASSERT_EQUAL(1,value);
    value = streamReadBits(fileStream,1);
    TEST_ASSERT_EQUAL(0,value);
    value = streamReadBits(fileStream,1);
    TEST_ASSERT_EQUAL(1,value);
  }Catch(error){
    TEST_ASSERT_EQUAL(ERR_END_OF_FILE,error);
  }
  if(fileStream != NULL){
    closeStream(fileStream);
  }
}

void test_streamReadBits_should_success_read_8_bit_from_file_if_there_only_1_byte_data(){
  CEXCEPTION_T error;
  int value;
  Stream* fileStream = NULL;
  // First byte is 'z', it has binary value of 0111 1010
  // So, the first 8 bits read in should be 0111 1010
  Try{
    fileStream = openStream("textSample_3.txt","r");
    value = streamReadBits(fileStream,1);
    TEST_ASSERT_EQUAL(0,value);
    value = streamReadBits(fileStream,1);
    TEST_ASSERT_EQUAL(1,value);
    value = streamReadBits(fileStream,1);
    TEST_ASSERT_EQUAL(1,value);
    value = streamReadBits(fileStream,1);
    TEST_ASSERT_EQUAL(1,value);
    value = streamReadBits(fileStream,1);
    TEST_ASSERT_EQUAL(1,value);
    value = streamReadBits(fileStream,1);
    TEST_ASSERT_EQUAL(0,value);
    value = streamReadBits(fileStream,1);
    TEST_ASSERT_EQUAL(1,value);
    value = streamReadBits(fileStream,1);
    TEST_ASSERT_EQUAL(0,value);
  }Catch(error){
    TEST_ASSERT_EQUAL(ERR_END_OF_FILE,error);
  }
  if(fileStream != NULL){
    closeStream(fileStream);
  }
}

/////////////////////
// streamWriteBit/Byte - streamFlush
////////////////////

void test_streamWriteBit_should_send_data_to_file_if_bitIndex_reach_8(){
  CEXCEPTION_T error;
  Stream* fileStream = NULL;
  // Data written : 0111 0001 equivalent to 'q'
  // Or 0110 0001 equivalent to 'a'
  Try{
    fileStream = openStream("write8bitData.txt","w");
    streamWriteBit(fileStream,0);
    streamWriteBit(fileStream,1);
    streamWriteBit(fileStream,1);
    streamWriteBit(fileStream,1);
    streamWriteBit(fileStream,0);
    streamWriteBit(fileStream,0);
    streamWriteBit(fileStream,0);
    streamWriteBit(fileStream,1);
  }Catch(error){
    TEST_ASSERT_EQUAL(ERR_FILE_NOT_EXIST,error);
  }
  TEST_ASSERT_EQUAL(0,fileStream->bitIndex);
  if(fileStream != NULL){
    closeStream(fileStream);
  }
}

void test_streamWriteBit_should_not_send_data_to_file_if_bitIndex_does_not_reach_8(){
  CEXCEPTION_T error;
  Stream* fileStream = NULL;
  // Data written : 0111 0001 equivalent to 'q'
  // Or 0110 0001 equivalent to 'a'
  Try{
    fileStream = openStream("write3bitData.txt","w");
    streamWriteBit(fileStream,0);
    streamWriteBit(fileStream,1);
    streamWriteBit(fileStream,1);
  }Catch(error){
    TEST_ASSERT_EQUAL(ERR_FILE_NOT_EXIST,error);
  }
  TEST_ASSERT_EQUAL(3,fileStream->bitIndex);
  if(fileStream != NULL){
    closeStream(fileStream);
  }
}

void test_streamWriteByte_should_write_data_to_file(){
  CEXCEPTION_T error;
  Stream* fileStream = NULL;
  // Data written : "I am back!"
  Try{
    fileStream = openStream("writeData.txt","w");
    streamWriteByte(fileStream,'I');
    streamWriteByte(fileStream,' ');
    streamWriteByte(fileStream,'a');
    streamWriteByte(fileStream,'m');
    streamWriteByte(fileStream,' ');
    streamWriteByte(fileStream,'b');
    streamWriteByte(fileStream,'a');
    streamWriteByte(fileStream,'c');
    streamWriteByte(fileStream,'k');
    streamWriteByte(fileStream,'!');
  }Catch(error){
    TEST_ASSERT_EQUAL(ERR_FILE_NOT_EXIST,error);
  }
  if(fileStream != NULL){
    closeStream(fileStream);
  }
}











