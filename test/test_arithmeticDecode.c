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
  streamReadBit_ExpectAndReturn(&in, 1, 1);
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
  streamReadBit_ExpectAndReturn(&in, 1, 0);
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
  streamReadBit_ExpectAndReturn(&in, 1, 1);
  decoderScaling(range, &tag, &in);
  TEST_ASSERT_EQUAL_UINT32(0xFFFFFFFF,range->upper);
  TEST_ASSERT_EQUAL_UINT32(0x01FFFFFE,range->lower);
  TEST_ASSERT_EQUAL_UINT32(0x90842021,tag);
}














