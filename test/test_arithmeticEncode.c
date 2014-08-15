#include "unity.h"
#include "mock_Stream.h"
#include "arithmeticEncode.h"
#include "dataType.h"

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
  CFT cft[] = {{.symbol = '1', .cum_Freq = 25},
               {.symbol = '2', .cum_Freq = 40},
               {.symbol = '3', .cum_Freq = 50}};
  int t_Size = 3;
  char symbol = '1';
  Range* range1 = rangeNew();
  getRangeOfSymbol(range1,symbol,cft,t_Size);
  TEST_ASSERT_EQUAL_UINT32(0x7FFFFFFF,range1->upper);
  TEST_ASSERT_EQUAL_UINT32(0,range1->lower);
}

void test_getRangeOfSymbol_should_retrieve_new_range_for_symbol2(){
  CFT cft[] = {{.symbol = '1', .cum_Freq = 25},
               {.symbol = '2', .cum_Freq = 40},
               {.symbol = '3', .cum_Freq = 50}};
  int t_Size = 3;
  char symbol = '2';
  Range* range2 = rangeNew();
  getRangeOfSymbol(range2,symbol,cft,t_Size);

  TEST_ASSERT_EQUAL_UINT32(0xCCCCCCCB,range2->upper);
  TEST_ASSERT_EQUAL_UINT32(0x80000000,range2->lower);
}

void test_getRangeOfSymbol_should_retrieve_new_range_for_symbol3(){
  CFT cft[] = {{.symbol = '1', .cum_Freq = 25},
               {.symbol = '2', .cum_Freq = 40},
               {.symbol = '3', .cum_Freq = 50}};
  int t_Size = 3;
  char symbol = '3';
  Range* range3 = rangeNew();
  getRangeOfSymbol(range3,symbol,cft,t_Size);

  TEST_ASSERT_EQUAL_UINT32(0xFFFFFFFF,range3->upper);
  TEST_ASSERT_EQUAL_UINT32(0xCCCCCCCC,range3->lower);
}

void test_getRangeOfSymbol_should_retrieve_new_range_for_symbol_sequence_of_1_1(){
  CFT cft[] = {{.symbol = '1', .cum_Freq = 25},
               {.symbol = '2', .cum_Freq = 40},
               {.symbol = '3', .cum_Freq = 50}};
  int t_Size = 3;
  char symbol_1 = '1';
  Range* range11 = rangeNew();
  getRangeOfSymbol(range11,symbol_1,cft,t_Size);
  getRangeOfSymbol(range11,symbol_1,cft,t_Size);

  TEST_ASSERT_EQUAL_UINT32(0x3FFFFFFF,range11->upper);
  TEST_ASSERT_EQUAL_UINT32(0,range11->lower);
}

void test_getRangeOfSymbol_should_retrieve_new_range_for_symbol_sequence_of_1_2(){
  CFT cft[] = {{.symbol = '1', .cum_Freq = 25},
               {.symbol = '2', .cum_Freq = 40},
               {.symbol = '3', .cum_Freq = 50}};
  int t_Size = 3;
  char symbol_1 = '1';
  char symbol_2 = '2';
  Range* range12 = rangeNew();
  getRangeOfSymbol(range12,symbol_1,cft,t_Size);
  getRangeOfSymbol(range12,symbol_2,cft,t_Size);

  TEST_ASSERT_EQUAL_UINT32(0x66666665,range12->upper);
  TEST_ASSERT_EQUAL_UINT32(0x40000000,range12->lower);
}

void test_getRangeOfSymbol_should_retrieve_new_range_for_symbol_sequence_of_1_3(){
  CFT cft[] = {{.symbol = '1', .cum_Freq = 25},
               {.symbol = '2', .cum_Freq = 40},
               {.symbol = '3', .cum_Freq = 50}};
  int t_Size = 3;
  char symbol_1 = '1';
  char symbol_3 = '3';
  Range* range13 = rangeNew();
  getRangeOfSymbol(range13,symbol_1,cft,t_Size);
  getRangeOfSymbol(range13,symbol_3,cft,t_Size);

  TEST_ASSERT_EQUAL_UINT32(0x7FFFFFFF,range13->upper);
  TEST_ASSERT_EQUAL_UINT32(0x66666666,range13->lower);
}

void test_getRangeOfSymbol_should_retrieve_new_range_for_symbol_sequence_of_2_1(){
  CFT cft[] = {{.symbol = '1', .cum_Freq = 25},
               {.symbol = '2', .cum_Freq = 40},
               {.symbol = '3', .cum_Freq = 50}};
  int t_Size = 3;
  char symbol_1 = '1';
  char symbol_2 = '2';
  Range* range21 = rangeNew();
  getRangeOfSymbol(range21,symbol_2,cft,t_Size);
  getRangeOfSymbol(range21,symbol_1,cft,t_Size);

  TEST_ASSERT_EQUAL_UINT32(0xA6666665,range21->upper);
  TEST_ASSERT_EQUAL_UINT32(0x80000000,range21->lower);
}

void test_getRangeOfSymbol_should_retrieve_new_range_for_symbol_sequence_of_2_2(){
  CFT cft[] = {{.symbol = '1', .cum_Freq = 25},
               {.symbol = '2', .cum_Freq = 40},
               {.symbol = '3', .cum_Freq = 50}};
  int t_Size = 3;
  char symbol_2 = '2';
  Range* range22 = rangeNew();
  getRangeOfSymbol(range22,symbol_2,cft,t_Size);
  getRangeOfSymbol(range22,symbol_2,cft,t_Size);

  TEST_ASSERT_EQUAL_UINT32(0xBD70A3D5,range22->upper);
  TEST_ASSERT_EQUAL_UINT32(0xA6666666,range22->lower);
}

void test_getRangeOfSymbol_should_retrieve_new_range_for_symbol_sequence_of_2_3(){
  CFT cft[] = {{.symbol = '1', .cum_Freq = 25},
               {.symbol = '2', .cum_Freq = 40},
               {.symbol = '3', .cum_Freq = 50}};
  int t_Size = 3;
  char symbol_2 = '2';
  char symbol_3 = '3';
  Range* range23 = rangeNew();
  getRangeOfSymbol(range23,symbol_2,cft,t_Size);
  getRangeOfSymbol(range23,symbol_3,cft,t_Size);

  TEST_ASSERT_EQUAL_UINT32(0xCCCCCCCB,range23->upper);
  TEST_ASSERT_EQUAL_UINT32(0xBD70A3D6,range23->lower);
}

void test_getRangeOfSymbol_should_retrieve_new_range_for_symbol_sequence_of_3_1(){
  CFT cft[] = {{.symbol = '1', .cum_Freq = 25},
               {.symbol = '2', .cum_Freq = 40},
               {.symbol = '3', .cum_Freq = 50}};
  int t_Size = 3;
  char symbol_1 = '1';
  char symbol_3 = '3';
  Range* range31 = rangeNew();
  getRangeOfSymbol(range31,symbol_3,cft,t_Size);
  getRangeOfSymbol(range31,symbol_1,cft,t_Size);

  TEST_ASSERT_EQUAL_UINT32(0xE6666665,range31->upper);
  TEST_ASSERT_EQUAL_UINT32(0xCCCCCCCC,range31->lower);
}

void test_getRangeOfSymbol_should_retrieve_new_range_for_symbol_sequence_of_3_2(){
  CFT cft[] = {{.symbol = '1', .cum_Freq = 25},
               {.symbol = '2', .cum_Freq = 40},
               {.symbol = '3', .cum_Freq = 50}};
  int t_Size = 3;
  char symbol_2 = '2';
  char symbol_3 = '3';
  Range* range32 = rangeNew();
  getRangeOfSymbol(range32,symbol_3,cft,t_Size);
  getRangeOfSymbol(range32,symbol_2,cft,t_Size);

  TEST_ASSERT_EQUAL_UINT32(0xF5C28F5B,range32->upper);
  TEST_ASSERT_EQUAL_UINT32(0xE6666666,range32->lower);
}

void test_getRangeOfSymbol_should_retrieve_new_range_for_symbol_sequence_of_3_3(){
  CFT cft[] = {{.symbol = '1', .cum_Freq = 25},
               {.symbol = '2', .cum_Freq = 40},
               {.symbol = '3', .cum_Freq = 50}};
  int t_Size = 3;
  char symbol_3 = '3';
  Range* range33 = rangeNew();
  getRangeOfSymbol(range33,symbol_3,cft,t_Size);
  getRangeOfSymbol(range33,symbol_3,cft,t_Size);

  TEST_ASSERT_EQUAL_UINT32(0xFFFFFFFF,range33->upper);
  TEST_ASSERT_EQUAL_UINT32(0xF5C28F5C,range33->lower);
}

void test_getRangeOfSymbol_should_retrieve_new_range_for_symbol_sequence_of_1_2_3_1(){
  CFT cft[] = {{.symbol = '1', .cum_Freq = 25},
               {.symbol = '2', .cum_Freq = 40},
               {.symbol = '3', .cum_Freq = 50}};
  int t_Size = 3;
  char symbol_1 = '1';
  char symbol_2 = '2';
  char symbol_3 = '3';
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

///////////////////////////
// andMask32bit - Test to mask 32 bit
//////////////////////////
void test_andMask32bit_should_mask_all_the_value_to_0_except_MSB(){
  Range* range = rangeNew();
  range->upper = 0xF341FFBA;
  range->lower = 0x44215678;

  andMask32bit(range);
  TEST_ASSERT_EQUAL_UINT32(0x80000000,range->upper);
  TEST_ASSERT_EQUAL_UINT32(0x00000000,range->lower);

  range->upper = 0xF341FFBA;
  range->lower = 0xC4215678;

  andMask32bit(range);
  TEST_ASSERT_EQUAL_UINT32(0x80000000,range->upper);
  TEST_ASSERT_EQUAL_UINT32(0x80000000,range->lower);
}

///////////////////////////
// encoderScaling
//////////////////////////
void test_encoderScaling_for_E1_E3_E3_scaling_should_do_the_scaling(){
  Range* range = rangeNew();
  Stream out;
  range->lower = 0x34000000;   // 0011 0100 .... 0000
  range->upper = 0x45000000;   // 0100 0101 .... 0000

  streamWriteBit_ExpectAndReturn(&out,0,1);
  encoderScaling(range,&out);

  TEST_ASSERT_EQUAL_UINT32(0xA8000007,range->upper);
  TEST_ASSERT_EQUAL_UINT32(0x20000000,range->lower);
  TEST_ASSERT_EQUAL(2,range->scale3);
}

void test_encoderScaling_for_E2_E3_E3_scaling_should_do_the_scaling(){
  Range* range = rangeNew();
  Stream out;
  range->lower = 0xB4000000;   // 1011 0100 .... 0000
  range->upper = 0xC5000000;   // 1100 0101 .... 0000

  streamWriteBit_ExpectAndReturn(&out,1,1);
  encoderScaling(range,&out);

  TEST_ASSERT_EQUAL_UINT32(0xA8000007,range->upper);
  TEST_ASSERT_EQUAL_UINT32(0x20000000,range->lower);
  TEST_ASSERT_EQUAL(2,range->scale3);
}

void test_encoderScaling_should_do_nothing_if_upper_is_0x00123456_and_lower_is_0x11123456(){
  Range* range = rangeNew();
  Stream out;
  range->lower = 0x00123456;   // 0000 0000 .... 0110
  range->upper = 0xC1123456;   // 1100 0001 .... 0110

  encoderScaling(range,&out);

  TEST_ASSERT_EQUAL_UINT32(0xC1123456,range->upper);
  TEST_ASSERT_EQUAL_UINT32(0x00123456,range->lower);
  TEST_ASSERT_EQUAL(0,range->scale3);
}

void test_encoderScaling_for_E3_E3_E3_scaling_should_increment_the_scale_by_3(){
  Range* range = rangeNew();
  Stream out;
  range->lower = 0x74000000;   // 0111 0100 .... 0000
  range->upper = 0x85000000;   // 1000 0101 .... 0000

  encoderScaling(range,&out);

  TEST_ASSERT_EQUAL_UINT32(0xA8000007,range->upper);
  TEST_ASSERT_EQUAL_UINT32(0x20000000,range->lower);
  TEST_ASSERT_EQUAL(3,range->scale3);
}

void test_encoderScaling_for_E3_E3_E3_E2_should_do_the_scaling(){
  Range* range = rangeNew();
  Stream out;
  range->lower = 0x74000000;   // 0111 0100 .... 0000
  range->upper = 0x85000000;   // 1000 0101 .... 0000

  encoderScaling(range,&out);
  TEST_ASSERT_EQUAL_UINT32(0xA8000007,range->upper);
  TEST_ASSERT_EQUAL_UINT32(0x20000000,range->lower);
  TEST_ASSERT_EQUAL(3,range->scale3);

  range->upper = 0xFA000001;  // 1111 1010 .... 0001
  range->lower = 0x9A000000;  // 1001 1010 .... 0000

  streamWriteBit_ExpectAndReturn(&out,1,1);
  streamWriteBit_ExpectAndReturn(&out,0,2);
  streamWriteBit_ExpectAndReturn(&out,0,3);
  streamWriteBit_ExpectAndReturn(&out,0,4);

  encoderScaling(range,&out);
  TEST_ASSERT_EQUAL_UINT32(0xF4000003,range->upper); //1111 0100 .... 0011
  TEST_ASSERT_EQUAL_UINT32(0x34000000,range->lower); //0011 0100 .... 0000
  TEST_ASSERT_EQUAL(0,range->scale3);
}

void test_encoderScaling_for_E3_E3_E3_E2_E2_should_do_the_scaling(){
  Range* range = rangeNew();
  Stream out;
  range->lower = 0x74000000;   // 0111 0100 .... 0000
  range->upper = 0x85000000;   // 1000 0101 .... 0000

  encoderScaling(range,&out);
  TEST_ASSERT_EQUAL_UINT32(0xA8000007,range->upper);
  TEST_ASSERT_EQUAL_UINT32(0x20000000,range->lower);
  TEST_ASSERT_EQUAL(3,range->scale3);

  range->upper = 0xFA000001;  // 1111 1010 .... 0001
  range->lower = 0xDA000000;  // 1101 1010 .... 0000

  streamWriteBit_ExpectAndReturn(&out,1,1);
  streamWriteBit_ExpectAndReturn(&out,0,2);
  streamWriteBit_ExpectAndReturn(&out,0,3);
  streamWriteBit_ExpectAndReturn(&out,0,4);
  streamWriteBit_ExpectAndReturn(&out,1,5);

  encoderScaling(range,&out);
  TEST_ASSERT_EQUAL_UINT32(0xE8000007,range->upper); //1110 1000 .... 0111
  TEST_ASSERT_EQUAL_UINT32(0x68000000,range->lower); //0110 1000 .... 0000
  TEST_ASSERT_EQUAL(0,range->scale3);
}

///////////////////////////
// arithmeticEncode
//////////////////////////
void test_arithmeticEncode_should_perform_encoding_process_on_symbol_1321_and_create_a_tag(){
  int dataLength = 4, t_Size = 3;
  char symbol[] = "1321";
  char *dataPtr;
  dataPtr = symbol;
  CFT cft[] = {{.symbol = '1', .cum_Freq = 25},
               {.symbol = '2', .cum_Freq = 40},
               {.symbol = '3', .cum_Freq = 50}};

  Stream out;

  streamWriteBit_ExpectAndReturn(&out,0,1);
  streamWriteBit_ExpectAndReturn(&out,1,2);
  streamWriteBit_ExpectAndReturn(&out,1,3);
  streamWriteBit_ExpectAndReturn(&out,1,4);
  streamWriteBit_ExpectAndReturn(&out,0,5);

  streamWriteBit_ExpectAndReturn(&out,0,6);
  streamWriteBit_ExpectAndReturn(&out,1,7);
  streamWriteBit_ExpectAndReturn(&out,1,8);
  streamWriteBit_ExpectAndReturn(&out,0,1);

  streamWriteBit_ExpectAndReturn(&out,0,2);
  streamWriteBit_ExpectAndReturn(&out,1,3);
  streamWriteBit_ExpectAndReturn(&out,1,4);
  streamWriteBit_ExpectAndReturn(&out,0,5);

  streamWriteBit_ExpectAndReturn(&out,0,6);
  streamWriteBit_ExpectAndReturn(&out,1,7);
  streamWriteBit_ExpectAndReturn(&out,1,8);
  streamWriteBit_ExpectAndReturn(&out,0,1);

  streamWriteBit_ExpectAndReturn(&out,0,2);
  streamWriteBit_ExpectAndReturn(&out,1,3);
  streamWriteBit_ExpectAndReturn(&out,1,4);
  streamWriteBit_ExpectAndReturn(&out,0,5);

  streamWriteBit_ExpectAndReturn(&out,0,6);
  streamWriteBit_ExpectAndReturn(&out,1,7);
  streamWriteBit_ExpectAndReturn(&out,1,8);
  streamWriteBit_ExpectAndReturn(&out,0,1);

  streamWriteBit_ExpectAndReturn(&out,0,2);
  streamWriteBit_ExpectAndReturn(&out,1,3);
  streamWriteBit_ExpectAndReturn(&out,1,4);
  streamWriteBit_ExpectAndReturn(&out,0,5);

  streamWriteBit_ExpectAndReturn(&out,0,6);
  streamWriteBit_ExpectAndReturn(&out,1,7);
  streamWriteBit_ExpectAndReturn(&out,1,8);
  streamWriteBit_ExpectAndReturn(&out,0,1);

  streamWriteBit_ExpectAndReturn(&out,0,2);
  streamWriteBit_ExpectAndReturn(&out,0,3);
  streamWriteBit_ExpectAndReturn(&out,0,4);
  streamWriteBit_ExpectAndReturn(&out,0,5);
  arithmeticEncode(dataPtr, dataLength, cft, t_Size, &out);
}

void test_arithmeticEncode_should_perform_encoding_process_with_another_CFT_on_symbol_1321_and_create_a_tag(){
  int dataLength = 4, t_Size = 3;
  char symbol[] = "1321";
  char *dataPtr;
  dataPtr = symbol;
  CFT cft[] = {{.symbol = '1', .cum_Freq = 40},
               {.symbol = '2', .cum_Freq = 41},
               {.symbol = '3', .cum_Freq = 50}};

  Stream out;

  streamWriteBit_ExpectAndReturn(&out,1,1);
  streamWriteBit_ExpectAndReturn(&out,1,2);
  streamWriteBit_ExpectAndReturn(&out,0,3);
  streamWriteBit_ExpectAndReturn(&out,0,4);
  streamWriteBit_ExpectAndReturn(&out,0,5);
  streamWriteBit_ExpectAndReturn(&out,1,6);

  streamWriteBit_ExpectAndReturn(&out,0,7);
  streamWriteBit_ExpectAndReturn(&out,1,8);
  streamWriteBit_ExpectAndReturn(&out,0,1);
  streamWriteBit_ExpectAndReturn(&out,1,2);
  streamWriteBit_ExpectAndReturn(&out,1,3);

  streamWriteBit_ExpectAndReturn(&out,0,4);
  streamWriteBit_ExpectAndReturn(&out,1,5);
  streamWriteBit_ExpectAndReturn(&out,1,6);
  streamWriteBit_ExpectAndReturn(&out,0,7);

  streamWriteBit_ExpectAndReturn(&out,1,8);
  streamWriteBit_ExpectAndReturn(&out,0,1);
  streamWriteBit_ExpectAndReturn(&out,1,2);
  streamWriteBit_ExpectAndReturn(&out,0,3);

  streamWriteBit_ExpectAndReturn(&out,1,4);
  streamWriteBit_ExpectAndReturn(&out,1,5);
  streamWriteBit_ExpectAndReturn(&out,1,6);
  streamWriteBit_ExpectAndReturn(&out,0,7);

  streamWriteBit_ExpectAndReturn(&out,0,8);
  streamWriteBit_ExpectAndReturn(&out,1,1);
  streamWriteBit_ExpectAndReturn(&out,1,2);
  streamWriteBit_ExpectAndReturn(&out,1,3);

  streamWriteBit_ExpectAndReturn(&out,1,4);
  streamWriteBit_ExpectAndReturn(&out,1,5);
  streamWriteBit_ExpectAndReturn(&out,0,6);
  streamWriteBit_ExpectAndReturn(&out,0,7);

  streamWriteBit_ExpectAndReturn(&out,1,8);
  streamWriteBit_ExpectAndReturn(&out,1,1);
  streamWriteBit_ExpectAndReturn(&out,1,2);
  streamWriteBit_ExpectAndReturn(&out,0,3);

  streamWriteBit_ExpectAndReturn(&out,0,4);
  streamWriteBit_ExpectAndReturn(&out,0,5);
  streamWriteBit_ExpectAndReturn(&out,0,6);
  streamWriteBit_ExpectAndReturn(&out,0,7);
  arithmeticEncode(symbol, dataLength, cft, t_Size, &out);
}

void test_arithmeticEncode_should_perform_encoding_process_on_symbol_acba_and_create_a_tag(){
  int dataLength = 4, t_Size = 3;
  char symbol[] = "acba";
  char *dataPtr;
  dataPtr = symbol;
  CFT cft[] = {{.symbol = 'a', .cum_Freq = 40},
               {.symbol = 'b', .cum_Freq = 41},
               {.symbol = 'c', .cum_Freq = 50}};

  Stream out;

  streamWriteBit_ExpectAndReturn(&out,1,1);
  streamWriteBit_ExpectAndReturn(&out,1,2);
  streamWriteBit_ExpectAndReturn(&out,0,3);
  streamWriteBit_ExpectAndReturn(&out,0,4);
  streamWriteBit_ExpectAndReturn(&out,0,5);
  streamWriteBit_ExpectAndReturn(&out,1,6);

  streamWriteBit_ExpectAndReturn(&out,0,7);
  streamWriteBit_ExpectAndReturn(&out,1,8);
  streamWriteBit_ExpectAndReturn(&out,0,1);
  streamWriteBit_ExpectAndReturn(&out,1,2);
  streamWriteBit_ExpectAndReturn(&out,1,3);

  streamWriteBit_ExpectAndReturn(&out,0,4);
  streamWriteBit_ExpectAndReturn(&out,1,5);
  streamWriteBit_ExpectAndReturn(&out,1,6);
  streamWriteBit_ExpectAndReturn(&out,0,7);

  streamWriteBit_ExpectAndReturn(&out,1,8);
  streamWriteBit_ExpectAndReturn(&out,0,1);
  streamWriteBit_ExpectAndReturn(&out,1,2);
  streamWriteBit_ExpectAndReturn(&out,0,3);

  streamWriteBit_ExpectAndReturn(&out,1,4);
  streamWriteBit_ExpectAndReturn(&out,1,5);
  streamWriteBit_ExpectAndReturn(&out,1,6);
  streamWriteBit_ExpectAndReturn(&out,0,7);

  streamWriteBit_ExpectAndReturn(&out,0,8);
  streamWriteBit_ExpectAndReturn(&out,1,1);
  streamWriteBit_ExpectAndReturn(&out,1,2);
  streamWriteBit_ExpectAndReturn(&out,1,3);

  streamWriteBit_ExpectAndReturn(&out,1,4);
  streamWriteBit_ExpectAndReturn(&out,1,5);
  streamWriteBit_ExpectAndReturn(&out,0,6);
  streamWriteBit_ExpectAndReturn(&out,0,7);

  streamWriteBit_ExpectAndReturn(&out,1,8);
  streamWriteBit_ExpectAndReturn(&out,1,1);
  streamWriteBit_ExpectAndReturn(&out,1,2);
  streamWriteBit_ExpectAndReturn(&out,0,3);

  streamWriteBit_ExpectAndReturn(&out,0,4);
  streamWriteBit_ExpectAndReturn(&out,0,5);
  streamWriteBit_ExpectAndReturn(&out,0,6);
  streamWriteBit_ExpectAndReturn(&out,0,7);
  arithmeticEncode(symbol, dataLength, cft, t_Size, &out);
}

///////////////////////////
// cftNew
//////////////////////////

void test_cftNew_should_create_cft_for_1_symbol(){
  Stream in;
  CFT *cftPtr;

  streamReadBits_ExpectAndReturn(&in, 8, '1');
  streamReadBits_ExpectAndThrow(&in, 8, ERR_END_OF_FILE);
  cftPtr = cftNew(&in);

  TEST_ASSERT_EQUAL('1', cftPtr[0].symbol);
  TEST_ASSERT_EQUAL(1, cftPtr[0].cum_Freq);
  TEST_ASSERT_EQUAL(1, cftPtr[0].occurNo);
}

void test_cftNew_should_create_cft_for_2_difference_symbols(){
  Stream in;
  CFT *cftPtr;

  streamReadBits_ExpectAndReturn(&in, 8, '1');
  streamReadBits_ExpectAndReturn(&in, 8, '2');
  streamReadBits_ExpectAndThrow(&in, 8, ERR_END_OF_FILE);
  cftPtr = cftNew(&in);

  TEST_ASSERT_EQUAL('1', cftPtr[0].symbol);
  TEST_ASSERT_EQUAL(1, cftPtr[0].cum_Freq);
  TEST_ASSERT_EQUAL(1, cftPtr[0].occurNo);

  TEST_ASSERT_EQUAL('2', cftPtr[1].symbol);
  TEST_ASSERT_EQUAL(2, cftPtr[1].cum_Freq);
  TEST_ASSERT_EQUAL(1, cftPtr[1].occurNo);
}

void test_cftNew_should_create_cft_for_2_same_symbols(){
  Stream in;
  CFT *cftPtr;

  streamReadBits_ExpectAndReturn(&in, 8, '1');
  streamReadBits_ExpectAndReturn(&in, 8, '1');
  streamReadBits_ExpectAndThrow(&in, 8, ERR_END_OF_FILE);
  cftPtr = cftNew(&in);

  TEST_ASSERT_EQUAL('1', cftPtr[0].symbol);
  TEST_ASSERT_EQUAL(2, cftPtr[0].cum_Freq);
  TEST_ASSERT_EQUAL(2, cftPtr[0].occurNo);
}

void test_cftNew_should_create_cft_for_symbols(){
  Stream in;
  CFT *cftPtr;

  streamReadBits_ExpectAndReturn(&in, 8, '1');
  streamReadBits_ExpectAndReturn(&in, 8, '2');
  streamReadBits_ExpectAndReturn(&in, 8, '2');
  streamReadBits_ExpectAndReturn(&in, 8, '1');
  streamReadBits_ExpectAndReturn(&in, 8, '2');
  streamReadBits_ExpectAndReturn(&in, 8, '4');
  streamReadBits_ExpectAndReturn(&in, 8, '5');
  streamReadBits_ExpectAndReturn(&in, 8, '3');
  streamReadBits_ExpectAndReturn(&in, 8, '5');
  streamReadBits_ExpectAndThrow(&in, 8, ERR_END_OF_FILE);
  cftPtr = cftNew(&in);

  TEST_ASSERT_EQUAL('1', cftPtr[0].symbol);
  TEST_ASSERT_EQUAL(2, cftPtr[0].cum_Freq);
  TEST_ASSERT_EQUAL(2, cftPtr[0].occurNo);

  TEST_ASSERT_EQUAL('2', cftPtr[1].symbol);
  TEST_ASSERT_EQUAL(5, cftPtr[1].cum_Freq);
  TEST_ASSERT_EQUAL(3, cftPtr[1].occurNo);

  TEST_ASSERT_EQUAL('4', cftPtr[2].symbol);
  TEST_ASSERT_EQUAL(6, cftPtr[2].cum_Freq);
  TEST_ASSERT_EQUAL(1, cftPtr[2].occurNo);

  TEST_ASSERT_EQUAL('5', cftPtr[3].symbol);
  TEST_ASSERT_EQUAL(8, cftPtr[3].cum_Freq);
  TEST_ASSERT_EQUAL(2, cftPtr[3].occurNo);

  TEST_ASSERT_EQUAL('3', cftPtr[4].symbol);
  TEST_ASSERT_EQUAL(9, cftPtr[4].cum_Freq);
  TEST_ASSERT_EQUAL(1, cftPtr[4].occurNo);
}
















