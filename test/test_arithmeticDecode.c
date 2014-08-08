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
  CFT cft[] = {{.symbol = 1, .cum_Freq = 40},
               {.symbol = 2, .cum_Freq = 41},
               {.symbol = 3, .cum_Freq = 50}};
  int t_Size = 3;
  uint32 tag = 0xC56D5CF9;
  Range* range = rangeNew();
  streamWriteByte_ExpectAndReturn(&out,cft[0].symbol,8,8);
  getSymbolFromTag(range, tag, cft, t_Size, &out);
}

void test_getSymbolFromTag_to_obtain_symbol_3(){
  Stream out;
  CFT cft[] = {{.symbol = 1, .cum_Freq = 40},
               {.symbol = 2, .cum_Freq = 41},
               {.symbol = 3, .cum_Freq = 50}};
  int t_Size = 3;
  uint32 tag = 0xC56D5CF9;
  Range* range = rangeNew();
  range->upper = 0xCCCCCCCB;
  streamWriteByte_ExpectAndReturn(&out,cft[2].symbol,8,8);
  getSymbolFromTag(range, tag, cft, t_Size, &out);
}