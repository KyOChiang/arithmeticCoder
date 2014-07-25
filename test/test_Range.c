#include "unity.h"
#include "Stream.h"
#include "Range.h"
#include "dataType.h"
#include "limits.h"

void setUp(void){}
void tearDown(void){}

///////////////////////////
// rangeNew
//////////////////////////
void test_rangeNew_to_initialize_upper_lower_and_scale3(){
  Range* rangeA;
  rangeA = rangeNew();
  
  TEST_ASSERT_EQUAL_UINT32(0,rangeA->scale3);
  TEST_ASSERT_EQUAL_UINT32(0,rangeA->lower);
  TEST_ASSERT_EQUAL_UINT32(0xFFFFFFFFL,rangeA->upper);
}

///////////////////////////
// getRangeOfSymbol
//////////////////////////
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

void test_getRangeOfSymbol_should_retrieve_new_range_for_symbol_sequence_of_1_1(){
  CFT cft[] = {{.symbol = 1, .cum_Freq = 25},
               {.symbol = 2, .cum_Freq = 40},
               {.symbol = 3, .cum_Freq = 50}};
  int t_Size = 3;
  uint32 symbol_1 = 1;
  Range* range11 = rangeNew();
  getRangeOfSymbol(range11,symbol_1,cft,t_Size);
  getRangeOfSymbol(range11,symbol_1,cft,t_Size);
  
  TEST_ASSERT_EQUAL_UINT32(0x3FFFFFFF,range11->upper);
  TEST_ASSERT_EQUAL_UINT32(0,range11->lower);
}

void test_getRangeOfSymbol_should_retrieve_new_range_for_symbol_sequence_of_1_2(){
  CFT cft[] = {{.symbol = 1, .cum_Freq = 25},
               {.symbol = 2, .cum_Freq = 40},
               {.symbol = 3, .cum_Freq = 50}};
  int t_Size = 3;
  uint32 symbol_1 = 1;
  uint32 symbol_2 = 2;
  Range* range12 = rangeNew();
  getRangeOfSymbol(range12,symbol_1,cft,t_Size);
  getRangeOfSymbol(range12,symbol_2,cft,t_Size);
  
  TEST_ASSERT_EQUAL_UINT32(0x66666665,range12->upper);
  TEST_ASSERT_EQUAL_UINT32(0x40000000,range12->lower);
}

void test_getRangeOfSymbol_should_retrieve_new_range_for_symbol_sequence_of_1_3(){
  CFT cft[] = {{.symbol = 1, .cum_Freq = 25},
               {.symbol = 2, .cum_Freq = 40},
               {.symbol = 3, .cum_Freq = 50}};
  int t_Size = 3;
  uint32 symbol_1 = 1;
  uint32 symbol_3 = 3;
  Range* range13 = rangeNew();
  getRangeOfSymbol(range13,symbol_1,cft,t_Size);
  getRangeOfSymbol(range13,symbol_3,cft,t_Size);
  
  TEST_ASSERT_EQUAL_UINT32(0x7FFFFFFF,range13->upper);
  TEST_ASSERT_EQUAL_UINT32(0x66666666,range13->lower);
}

void test_getRangeOfSymbol_should_retrieve_new_range_for_symbol_sequence_of_2_1(){
  CFT cft[] = {{.symbol = 1, .cum_Freq = 25},
               {.symbol = 2, .cum_Freq = 40},
               {.symbol = 3, .cum_Freq = 50}};
  int t_Size = 3;
  uint32 symbol_1 = 1;
  uint32 symbol_2 = 2;
  Range* range21 = rangeNew();
  getRangeOfSymbol(range21,symbol_2,cft,t_Size);
  getRangeOfSymbol(range21,symbol_1,cft,t_Size);
  
  TEST_ASSERT_EQUAL_UINT32(0xA6666665,range21->upper);
  TEST_ASSERT_EQUAL_UINT32(0x80000000,range21->lower);
}

void test_getRangeOfSymbol_should_retrieve_new_range_for_symbol_sequence_of_2_2(){
  CFT cft[] = {{.symbol = 1, .cum_Freq = 25},
               {.symbol = 2, .cum_Freq = 40},
               {.symbol = 3, .cum_Freq = 50}};
  int t_Size = 3;
  uint32 symbol_2 = 2;
  Range* range22 = rangeNew();
  getRangeOfSymbol(range22,symbol_2,cft,t_Size);
  getRangeOfSymbol(range22,symbol_2,cft,t_Size);
  
  TEST_ASSERT_EQUAL_UINT32(0xBD70A3D5,range22->upper);
  TEST_ASSERT_EQUAL_UINT32(0xA6666666,range22->lower);
}

void test_getRangeOfSymbol_should_retrieve_new_range_for_symbol_sequence_of_2_3(){
  CFT cft[] = {{.symbol = 1, .cum_Freq = 25},
               {.symbol = 2, .cum_Freq = 40},
               {.symbol = 3, .cum_Freq = 50}};
  int t_Size = 3;
  uint32 symbol_2 = 2;
  uint32 symbol_3 = 3;
  Range* range23 = rangeNew();
  getRangeOfSymbol(range23,symbol_2,cft,t_Size);
  getRangeOfSymbol(range23,symbol_3,cft,t_Size);
  
  TEST_ASSERT_EQUAL_UINT32(0xCCCCCCCB,range23->upper);
  TEST_ASSERT_EQUAL_UINT32(0xBD70A3D6,range23->lower);
}

void test_getRangeOfSymbol_should_retrieve_new_range_for_symbol_sequence_of_3_1(){
  CFT cft[] = {{.symbol = 1, .cum_Freq = 25},
               {.symbol = 2, .cum_Freq = 40},
               {.symbol = 3, .cum_Freq = 50}};
  int t_Size = 3;
  uint32 symbol_1 = 1;
  uint32 symbol_3 = 3;
  Range* range31 = rangeNew();
  getRangeOfSymbol(range31,symbol_3,cft,t_Size);
  getRangeOfSymbol(range31,symbol_1,cft,t_Size);
  
  TEST_ASSERT_EQUAL_UINT32(0xE6666665,range31->upper);
  TEST_ASSERT_EQUAL_UINT32(0xCCCCCCCC,range31->lower);
}

void test_getRangeOfSymbol_should_retrieve_new_range_for_symbol_sequence_of_3_2(){
  CFT cft[] = {{.symbol = 1, .cum_Freq = 25},
               {.symbol = 2, .cum_Freq = 40},
               {.symbol = 3, .cum_Freq = 50}};
  int t_Size = 3;
  uint32 symbol_2 = 2;
  uint32 symbol_3 = 3;
  Range* range32 = rangeNew();
  getRangeOfSymbol(range32,symbol_3,cft,t_Size);
  getRangeOfSymbol(range32,symbol_2,cft,t_Size);
  
  TEST_ASSERT_EQUAL_UINT32(0xF5C28F5B,range32->upper);
  TEST_ASSERT_EQUAL_UINT32(0xE6666666,range32->lower);
}

void test_getRangeOfSymbol_should_retrieve_new_range_for_symbol_sequence_of_3_3(){
  CFT cft[] = {{.symbol = 1, .cum_Freq = 25},
               {.symbol = 2, .cum_Freq = 40},
               {.symbol = 3, .cum_Freq = 50}};
  int t_Size = 3;
  uint32 symbol_3 = 3;
  Range* range33 = rangeNew();
  getRangeOfSymbol(range33,symbol_3,cft,t_Size);
  getRangeOfSymbol(range33,symbol_3,cft,t_Size);
  
  TEST_ASSERT_EQUAL_UINT32(0xFFFFFFFF,range33->upper);
  TEST_ASSERT_EQUAL_UINT32(0xF5C28F5C,range33->lower);
}

void test_getRangeOfSymbol_should_retrieve_new_range_for_symbol_sequence_of_1_2_3_1(){
  CFT cft[] = {{.symbol = 1, .cum_Freq = 25},
               {.symbol = 2, .cum_Freq = 40},
               {.symbol = 3, .cum_Freq = 50}};
  int t_Size = 3;
  uint32 symbol_1 = 1;
  uint32 symbol_2 = 2;
  uint32 symbol_3 = 3;
  Range* range1231 = rangeNew();
  
  getRangeOfSymbol(range1231,symbol_1,cft,t_Size);
  TEST_ASSERT_EQUAL_UINT32(0x7FFFFFFF,range1231->upper);
  TEST_ASSERT_EQUAL_UINT32(0,range1231->lower);
  
  getRangeOfSymbol(range1231,symbol_2,cft,t_Size);
  TEST_ASSERT_EQUAL_UINT32(0x66666665,range1231->upper);
  TEST_ASSERT_EQUAL_UINT32(0x40000000,range1231->lower);
  
  getRangeOfSymbol(range1231,symbol_3,cft,t_Size);
  TEST_ASSERT_EQUAL_UINT32(0x66666665,range1231->upper);
  TEST_ASSERT_EQUAL_UINT32(0x5EB851EB,range1231->lower);
  
  getRangeOfSymbol(range1231,symbol_1,cft,t_Size);
  TEST_ASSERT_EQUAL_UINT32(0x628F5C27,range1231->upper);
  TEST_ASSERT_EQUAL_UINT32(0x5EB851EB,range1231->lower);
}

