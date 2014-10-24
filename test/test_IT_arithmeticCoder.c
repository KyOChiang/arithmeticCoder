#include "unity.h"
#include "Stream.h"
#include "arithmeticEncode.h"
#include "arithmeticDecode.h"
#include "dataType.h"

void setUp(void){}
void tearDown(void){}

void test_cftNew_should_create_cft_for_symbols_from_file(){
  Stream *in = NULL;
  CFT *cftPtr;
  int tableSize;
  CEXCEPTION_T error;
  
  Try{
  // Please check cftData.txt, inside has a lengthy string 
    in = openStream("cftData.txt","r");
    cftPtr = cftNew(in, &tableSize);
  }Catch(error){
    TEST_ASSERT_NOT_EQUAL(ERR_FILE_NOT_EXIST,error);
  }
  dumpCFT(cftPtr,0);
  dumpCFT(cftPtr,1);
  dumpCFT(cftPtr,2);
  
  TEST_ASSERT_EQUAL(3,tableSize);
  
  TEST_ASSERT_EQUAL('a', cftPtr[0].symbol);
  TEST_ASSERT_EQUAL(40, cftPtr[0].cum_Freq);
  TEST_ASSERT_EQUAL(40, cftPtr[0].occurNo);

  TEST_ASSERT_EQUAL('b', cftPtr[1].symbol);
  TEST_ASSERT_EQUAL(41, cftPtr[1].cum_Freq);
  TEST_ASSERT_EQUAL(1, cftPtr[1].occurNo);

  TEST_ASSERT_EQUAL('c', cftPtr[2].symbol);
  TEST_ASSERT_EQUAL(50, cftPtr[2].cum_Freq);
  TEST_ASSERT_EQUAL(9, cftPtr[2].occurNo);
  
  if(in != NULL){
    closeStream(in);
  }
}

void test_arithmeticEncoder_to_encode_acba_with_cftData_txt_should_generate_a_tag(){
  Stream *cft = NULL, *in = NULL, *out = NULL;
  CFT *cftPtr;
  int dataLength = 0, tableSize;
  CEXCEPTION_T error;
  
  Try{
  // Please check cftData.txt, inside has a lengthy string 
    cft = openStream("cftData.txt","r");
    cftPtr = cftNew(cft,&tableSize);
    TEST_ASSERT_EQUAL(3,tableSize);
  }Catch(error){
    TEST_ASSERT_NOT_EQUAL(ERR_FILE_NOT_EXIST,error);
  }
  
  Try{
  /* Please check encodeACBA.txt contain the encode data
   * tag.txt/.bin will store the tag generate from encode data
   * acba will encode into 1100 0101 0110 1101 0101 1100 1111 1001 1100 000
   *
   * Unfortunately, editor cannot show the actual result as it show chinese character
   * To see the final result, using a hex editor to open the tag file and compare with
   * print statement at streamFlush.
   */
    in = openStream("encodeACBA.txt","r");
    out = openStream("tag.bin","w");
    arithmeticEncode(in, &dataLength, cftPtr,tableSize,out);
  }Catch(error){
    TEST_ASSERT_NOT_EQUAL(ERR_FILE_NOT_EXIST,error);
  }
  TEST_ASSERT_EQUAL(4,dataLength);
  if(in != NULL){
    closeStream(in);
  }if(out != NULL){
    closeStream(out);
  }if(cft != NULL){
    closeStream(cft);
  }
}

void test_tagReader_should_read_in_32bit_of_tag_value(){
  Stream *in = NULL;
  uint32 tag = 0;
  CEXCEPTION_T error;
  
  Try{
    in = openStream("tag.bin","r");
    tagReader(in,&tag);
  }Catch(error){
    TEST_ASSERT_NOT_EQUAL(ERR_FILE_NOT_EXIST,error);
  }
  TEST_ASSERT_EQUAL(0xC56D5CF9,tag);
  if(in != NULL){
    closeStream(in);
  }
}

void test_arithmeticDecoder_to_decode_tag_with_cftData_txt_should_generate_acba(){
  Stream *cft = NULL, *in = NULL, *out = NULL;
  CFT *cftPtr;
  uint32 tag = 0;
  int tableSize, dataLength = 4;
  CEXCEPTION_T error;
  
  Try{
  // Please check cftData.txt, inside has a lengthy string 
    cft = openStream("cftData.txt","r");
    cftPtr = cftNew(cft,&tableSize);
    TEST_ASSERT_EQUAL(3,tableSize);
  }Catch(error){
    TEST_ASSERT_NOT_EQUAL(ERR_FILE_NOT_EXIST,error);
  }
  
  Try{
  /* 1100 0101 0110 1101 0101 1100 1111 1001 1100 000 will decode back into acba
   * tag.txt/.bin will store the tag generate from encode data
   * acba store into decodeSymbol.txt
   */
    in = openStream("tag.bin","r");
    out = openStream("decodedSymbol.txt","w");
    tagReader(in,&tag);
    arithmeticDecode(&dataLength, &tag, cftPtr, tableSize, out, in);
  }Catch(error){
    TEST_ASSERT_NOT_EQUAL(ERR_FILE_NOT_EXIST,error);
  }
  
  if(in != NULL){
    closeStream(in);
  }if(out != NULL){
    closeStream(out);
  }if(cft != NULL){
    closeStream(cft);
  }
  TEST_ASSERT_EQUAL(0,dataLength);
}








