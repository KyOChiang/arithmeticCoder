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
    fileStream = openStream("textSample.txt","r",128);
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
    fileStream = openStream("textSample_2.txt","w",128);
  }Catch(error){
    TEST_ASSERT_EQUAL(ERR_FILE_NOT_EXIST,error);
  }
  TEST_ASSERT_EQUAL(128,fileStream->size);
  TEST_ASSERT_EQUAL(0,fileStream->length);
  TEST_ASSERT_EQUAL(0,fileStream->bitIndex);
  TEST_ASSERT_EQUAL(0,fileStream->byteIndex);
  TEST_ASSERT_EQUAL("textSample_2.txt",fileStream->filename);
  if(fileStream != NULL){
    closeStream(fileStream);
  }
}

void test_openStream_to_open_file_with_read_mode_should_read_testSample_1_txt(){
  CEXCEPTION_T error;
  int value;
  Stream* fileStream = NULL;

  Try{
    fileStream = openStream("textSample_1.txt","r",128);
  }Catch(error){
    TEST_ASSERT_EQUAL(ERR_FILE_NOT_EXIST,error);
  }
  TEST_ASSERT_EQUAL(128,fileStream->size);
  TEST_ASSERT_EQUAL(0,fileStream->length);
  TEST_ASSERT_EQUAL(0,fileStream->bitIndex);
  TEST_ASSERT_EQUAL(0,fileStream->byteIndex);
  TEST_ASSERT_EQUAL("textSample_1.txt",fileStream->filename);
  if(fileStream != NULL){
    closeStream(fileStream);
  }
}




















