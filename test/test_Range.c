#include "unity.h"
#include "Stream.h"
#include "Range.h"
#include "dataType.h"
#include "limits.h"

void setUp(void){}
void tearDown(void){}

void test_newRange_to_initialize_upper_lower_and_scale3(){
  Range* rangeA;
  rangeA = rangeNew();
  
  TEST_ASSERT_EQUAL_UINT32(0,rangeA->scale3);
  TEST_ASSERT_EQUAL_UINT32(0,rangeA->lower);
  TEST_ASSERT_EQUAL_UINT32(0xFFFFFFFFL,rangeA->upper);
}

void test_getRangeOfSymbol_should_retrieve_new_range_for_symbol1(){
  CFT cft[] = {{.symbol = 1, .cum_Freq = 25},
               {.symbol = 2, .cum_Freq = 40},
               {.symbol = 3, .cum_Freq = 50}};
  int t_Size = 3;
  uint32 symbol = 1;
  Range* range1 = rangeNew();
  getRangeOfSymbol(range1,symbol,cft,t_Size);
  
  TEST_ASSERT_EQUAL_UINT32(0x7FFFFFFF,range1->upper);
  TEST_ASSERT_EQUAL_UINT32(0,range1->lower);
}

void test_getRangeOfSymbol_should_retrieve_new_range_for_symbol2(){
  CFT cft[] = {{.symbol = 1, .cum_Freq = 25},
               {.symbol = 2, .cum_Freq = 40},
               {.symbol = 3, .cum_Freq = 50}};
  int t_Size = 3;
  uint32 symbol = 2;
  Range* range2 = rangeNew();
  getRangeOfSymbol(range2,symbol,cft,t_Size);
  
  TEST_ASSERT_EQUAL_UINT32(0xCCCCCCCB,range2->upper);
  TEST_ASSERT_EQUAL_UINT32(0x80000000,range2->lower);
}

void test_getRangeOfSymbol_should_retrieve_new_range_for_symbol3(){
  CFT cft[] = {{.symbol = 1, .cum_Freq = 25},
               {.symbol = 2, .cum_Freq = 40},
               {.symbol = 3, .cum_Freq = 50}};
  int t_Size = 3;
  uint32 symbol = 3;
  Range* range3 = rangeNew();
  getRangeOfSymbol(range3,symbol,cft,t_Size);
  
  TEST_ASSERT_EQUAL_UINT32(0xFFFFFFFF,range3->upper);
  TEST_ASSERT_EQUAL_UINT32(0xCCCCCCCC,range3->lower);
}