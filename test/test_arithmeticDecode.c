#include "unity.h"
#include "mock_Stream.h"
#include "arithmeticEncode.h"
#include "arithmeticDecode.h"
#include "dataType.h"

void setUp(void){}
void tearDown(void){}

///////////////////////////
// getSymbolFromTag
//////////////////////////
void test_getSymbolFromTag_to_obtain_symbol_1(){
  Stream out;
  CFT cft[] = {{.symbol = '1', .cum_Freq = 40},
               {.symbol = '2', .cum_Freq = 41},
               {.symbol = '3', .cum_Freq = 50}};
  int t_Size = 3;
  uint32 tag = 0xC56D5CF9;
  Range* range = rangeNew();
  streamWriteByte_ExpectAndReturn(&out,cft[0].symbol,8,8);
  getSymbolFromTag(range, &tag, cft, t_Size, &out);
}

void test_getSymbolFromTag_to_obtain_symbol_3(){
  Stream out;
  CFT cft[] = {{.symbol = '1', .cum_Freq = 40},
               {.symbol = '2', .cum_Freq = 41},
               {.symbol = '3', .cum_Freq = 50}};
  int t_Size = 3;
  uint32 tag = 0xC56D5CF9;
  Range* range = rangeNew();
  range->upper = 0xCCCCCCCB;
  streamWriteByte_ExpectAndReturn(&out,cft[2].symbol,8,8);
  getSymbolFromTag(range, &tag, cft, t_Size, &out);
}

///////////////////////////
// decoderScaling
//////////////////////////
void test_decoderScaling_should_not_perform_any_scaling_operation(){
  uint32 tag = 0xC56D5CF9;
  Range* range = rangeNew();
  Stream in;
  decoderScaling(range, &tag, &in);
  TEST_ASSERT_EQUAL_UINT32(0xFFFFFFFF,range->upper);
  TEST_ASSERT_EQUAL_UINT32(0x00000000,range->lower);
  TEST_ASSERT_EQUAL_UINT32(0xC56D5CF9,tag);
}

void test_decoderScaling_should_perform_E1_scaling_operation(){
  uint32 tag = 0x08421010;
  Range* range = rangeNew();
  Stream in;
  range->upper = 0x7FFFFFFF;
  streamReadBits_ExpectAndReturn(&in, 1, 1);
  decoderScaling(range, &tag, &in);
  TEST_ASSERT_EQUAL_UINT32(0xFFFFFFFF,range->upper);
  TEST_ASSERT_EQUAL_UINT32(0x00000000,range->lower);
  TEST_ASSERT_EQUAL_UINT32(0x10842021,tag);
}

void test_decoderScaling_should_perform_E2_scaling_operation(){
  uint32 tag = 0x08421010;
  Range* range = rangeNew();
  Stream in;
  range->lower = 0x80000000;
  streamReadBits_ExpectAndReturn(&in, 1, 0);
  decoderScaling(range, &tag, &in);
  TEST_ASSERT_EQUAL_UINT32(0xFFFFFFFF,range->upper);
  TEST_ASSERT_EQUAL_UINT32(0x00000000,range->lower);
  TEST_ASSERT_EQUAL_UINT32(0x10842020,tag);
}

void test_decoderScaling_should_perform_E3_scaling_operation(){
  uint32 tag = 0x08421010;
  Range* range = rangeNew();
  Stream in;
  range->upper = 0xBFFFFFFF;
  range->lower = 0x40FFFFFF;
  streamReadBits_ExpectAndReturn(&in, 1, 1);
  decoderScaling(range, &tag, &in);
  TEST_ASSERT_EQUAL_UINT32(0xFFFFFFFF,range->upper);
  TEST_ASSERT_EQUAL_UINT32(0x01FFFFFE,range->lower);
  TEST_ASSERT_EQUAL_UINT32(0x90842021,tag);
}

///////////////////////////
// arithmeticDecode
//////////////////////////
void test_arithmeticDecode_with_tag_should_return_1321(){
  uint32 tag = 0xC56D5CF9;
  int dataLength = 4, t_Size = 3;
  Stream in, out;
  CFT cft[] = {{.symbol = '1', .cum_Freq = 40},
               {.symbol = '2', .cum_Freq = 41},
               {.symbol = '3', .cum_Freq = 50}};

  streamWriteByte_ExpectAndReturn(&out,cft[0].symbol,8, 8);
  streamWriteByte_ExpectAndReturn(&out,cft[2].symbol,8, 16);
  streamReadBits_ExpectAndReturn(&in, 1, 1);
  streamReadBits_ExpectAndReturn(&in, 1, 1);
  streamWriteByte_ExpectAndReturn(&out,cft[1].symbol,8, 24);
  streamReadBits_ExpectAndReturn(&in, 1, 0);
  streamReadBits_ExpectAndReturn(&in, 1, 0);
  streamReadBits_ExpectAndReturn(&in, 1, 0);
  streamReadBits_ExpectAndReturn(&in, 1, 0);
  streamReadBits_ExpectAndReturn(&in, 1, 0);
  streamWriteByte_ExpectAndReturn(&out,cft[0].symbol,8, 32);

  arithmeticDecode(dataLength, &tag, cft, t_Size, &out, &in);
  //Tag: 1100 0101 0110 1101 0101 1100 1111 1001 1100 000
}

void test_arithmeticDecode_with_tag_on_different_cft_should_return_1321(){
  uint32 tag = 0x73333333;
  int dataLength = 4, t_Size = 3;
  Stream in, out;
  CFT cft[] = {{.symbol = '1', .cum_Freq = 25},
               {.symbol = '2', .cum_Freq = 40},
               {.symbol = '3', .cum_Freq = 50}};

  streamWriteByte_ExpectAndReturn(&out,cft[0].symbol,8, 8);
  streamReadBits_ExpectAndReturn(&in, 1, 0);
  streamWriteByte_ExpectAndReturn(&out,cft[2].symbol,8, 16);
  streamReadBits_ExpectAndReturn(&in, 1, 0);
  streamReadBits_ExpectAndReturn(&in, 1, 0);
  streamWriteByte_ExpectAndReturn(&out,cft[1].symbol,8, 24);
  streamReadBits_ExpectAndReturn(&in, 1, 0);
  streamWriteByte_ExpectAndReturn(&out,cft[0].symbol,8, 32);
  streamReadBits_ExpectAndReturn(&in, 1, 0);

  arithmeticDecode(dataLength, &tag, cft, t_Size, &out, &in);
  //Tag: 0111 0011 0011 0011 0011 0011 0011 0011 0000 0
}










