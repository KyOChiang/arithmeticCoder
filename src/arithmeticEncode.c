#include "arithmeticEncode.h"

/*  dumpRange
 *  Function      : To print upper, lower and scale3.
 *
 *  Arguments
 *  range(in)     : Pass in Range struct to display data inside
 */
void dumpRange(Range *range){
  printf("Upper range: %x\n", range->upper);
  printf("Lower range: %x\n", range->lower);
  printf("Scale3 range: %u\n", range->scale3);
}

/*  dumpCFT
 *  Function  : To print out the value inside cumulative frequency table
 *
 *  Arguments
 *  cft(in)   : Cumulative frequency table
 *  index(in) : The index location want to print out
 */
void dumpCFT(CFT* cft, int index){
  printf("Symbol: %c cum_Freq: %d occurNo: %d\n",cft[index].symbol,cft[index].cum_Freq,cft[index].occurNo);
}

/*  cftNew
 *
 *  Function          : Create new cumulative frequencies table (cft) by reading the char one by one
 *
 *  How               : 1. Check if there got char or not.
 *                         If char there, start to get 1 symbol. Otherwise, return exception error.
 *                      2. Check first index in table, is that empty or occupy by char.
 *                         If not empty, compare the char and the symbol. If same, occurNo plus 1
 *                         If not same, go to next index and check. If is a new symbol, add into the table, occurNo plus 1
 *                      3. Get the next symbol and repeat step 2 again until there no more char.
 *                      4. The cumulative frequency of each data in table is calculated as below:
 *                           cft[x].cum_Freq = cft[x-1].cum_Freq + cft[x].occurNo
 *                      5. Return the pointer that point to the created table.
 *
 *  Arguments
 *  in(in)            : Txt file contain characters and symbols
 *  t_Size(out)       : size of cft table
 *  t_Ptr(in)         : index pointer for cft
 *  loop(in)          : Help to stop searching table if it is 1
 *  keepGetSymbol(in) : Help to stop retrieve the next symbol if end of char
 *  getSymbol(in)     : Use to store the return char from streamReadBits
 *
 *  return
 *  cft             : a pointer to the created cft
 */
CFT *cftNew(Stream *in, int* tableSize){
  int t_Size = 0, t_Ptr = 0, loop, keepGetSymbol = 1;
  char getSymbol;
  CEXCEPTION_T error;
  CFT *cft = calloc(sizeof(CFT),256);

  while(keepGetSymbol){
    Try{
      getSymbol = streamReadBits(in, 8);
    }Catch(error){
      keepGetSymbol = 0;
    }
    if(keepGetSymbol == 0)
      break;
    loop = 0;
    for(t_Ptr = 0; t_Ptr < 256; t_Ptr = t_Ptr + 1){
      if(cft[t_Ptr].symbol == '\0'){
        cft[t_Ptr].symbol = getSymbol;
        cft[t_Ptr].occurNo = cft[t_Ptr].occurNo + 1;
        t_Ptr = t_Ptr + 1;
        loop = 1;
      }
      else if(getSymbol == cft[t_Ptr].symbol){
        cft[t_Ptr].occurNo = cft[t_Ptr].occurNo + 1;
        loop = 1;
      }
      if(t_Ptr >= t_Size)
        t_Size = t_Ptr;
      if(loop == 1)
        break;
    }
  }
  *(tableSize) = t_Size;
  for(t_Ptr = 0; t_Ptr < t_Size; t_Ptr = t_Ptr + 1){
    if(t_Ptr == 0)
      cft[t_Ptr].cum_Freq = cft[t_Ptr].occurNo;
    else
      cft[t_Ptr].cum_Freq = cft[t_Ptr-1].cum_Freq + cft[t_Ptr].occurNo;
  }

  return cft;
}

/*  rangeNew
 *  Function : To initialize a new range.
 *
 *  return
 *  newRange : New range with lower = 0, upper = 0xFFFFFFFFL
 */
Range *rangeNew(){
  Range* newRange = malloc(sizeof(Range));

  newRange->upper = 0xFFFFFFFFL;
  newRange->lower = 0;
  newRange->scale3 = 0;
  //dumpRange(newRange);

  return newRange;
}

/*  getRangeOfSymbol
 *  Function    : To get the new interval of a symbol
 *
 *  Arguments
 *  range(in/out)     : The current range with current upper limit and lower limit
 *  symbol(in)        : The input symbol required to get upper and lower limit
 *  tableSize(in)     : The size of CFT
 *  tbPtr(out)        : Index counter for CFT (Cumulative Frequency Table)
 *  rangeDiff(in)     : Subtraction of upper limit to lower limit from range
 *  tempL(out)        : temporary variable to store lower limit
 *  tempU(out)        : temporary variable to store upper limit
 *  low_Count(in)     : the lower limit for the input symbol
 *  up_Count(in)      : the upper limit for the input symbol
 *  total_Count(in)   : the cum_Freq of last symbol
 */
void getRangeOfSymbol(Range *range, char symbol, CFT *cft,int tableSize){
  int tbPtr;
  uint64 rangeDiff, tempL, tempU;
  uint32 low_Count, up_Count, total_Count;

  rangeDiff = ((uint64)range->upper - range->lower) + 1;
  total_Count = cft[tableSize-1].cum_Freq;
  // printf("Symbol : %c\n",symbol);
  for(tbPtr = 0; tbPtr < tableSize; tbPtr++){
    if(symbol == cft[tbPtr].symbol){
      if(tbPtr == 0)
        low_Count = 0;
      else
        low_Count = cft[tbPtr-1].cum_Freq;

      up_Count = cft[tbPtr].cum_Freq;
      break;
    }
  }
  tempL = (rangeDiff * low_Count);
  tempL /= total_Count;
  tempL += range->lower;

  tempU = (rangeDiff * up_Count);
  tempU /= total_Count;
  tempU += range->lower;
  tempU -= 1;

  range->lower = tempL;
  range->upper = tempU;
}

void rangeDel(Range *range){
  free(range);
}

/*  encoderScaling
 *  Function: To rescale the range, then transmit the encoder message.
 *            3 scales -> E1, E2, E3
 *            E1-> MSB of upper/lower are 0
 *            E2-> MSB of upper/lower are 1
 *            E3-> 1st and 2nd MSB of upper/lower are 10/01
 *
 *  Arguments
 *  range(in/out)     : The current range with current upper limit and lower limit
 *  out(out)          : To store the transmit message (encode value)
 *  upLimit(in)       : Used as mask to determine upper fulfill E1/E2 scaling condition
 *  lowLimit(in)      : Used as mask to determine lower fulfill E1/E2 scaling condition
 *  e3Up/e3Low(in)    : Used as mask to determine upper/lower fulfill E3 scaling condition
 *  transmitBit(out)  : Encode value to be sent out
 */
void encoderScaling(Range *range, Stream *out){
  int transmitBit;
  uint32 upLimit = maskMSB(range->upper), lowLimit = maskMSB(range->lower);
  uint32 e3Up = e3Mask(range->upper), e3Low = e3Mask(range->lower);

  while((upLimit == lowLimit)||((e3Up == MSB10) && (e3Low == MSB01))){
    if(upLimit == lowLimit){                          // E1 || E2 condition
      if(upLimit == 0 && lowLimit == 0){
       transmitBit = 0;
       streamWriteBit(out,transmitBit);
      }
      else{
        transmitBit = 1;
        streamWriteBit(out,transmitBit);
      }
      shiftToLeftBy1Bit(range->upper);
      range->upper += 1;
      shiftToLeftBy1Bit(range->lower);
      while(range->scale3 > 0){
        streamWriteBit(out,!transmitBit);
        range->scale3 -= 1;
      }
    }
    if((e3Up == MSB10) && (e3Low == MSB01)){          // E3 condition
      range->scale3 += 1;
      shiftToLeftBy1Bit(range->upper);
      range->upper += 1;
      shiftToLeftBy1Bit(range->lower);
      range->upper = complementMSB(range->upper);
      range->lower = complementMSB(range->lower);
    }
    upLimit = maskMSB(range->upper), lowLimit = maskMSB(range->lower);
    e3Up = e3Mask(range->upper), e3Low = e3Mask(range->lower);
  }
}

/*  andMask32bit
 *  Function : Mask 32 unsigned int with 0x8000 0000
 *
 *  Argument
 *  range(in) : Contain the upper and lower.
 */
void andMask32bit(Range *range){
  range->upper = (range->upper & 0x80000000);
  range->lower = (range->lower & 0x80000000);
}

/*  arithmeticEncode
 *  Function          : Encode data into tag
 *
 *  How               : 1. Initialize upper and lower of range with 0xFFFFFFFF and 0
 *                      2. If not EOF, will checking by streamReadBits and throw exception if EOF
 *                         Update the range->upper and range->lower(probability range for the symbol)
 *                      3. Perform the E1/E2/E3 scaling if necessary
 *                      4. Grab the next symbol and start over from step 2 again
 *                      5. If EOF, store the range->lower to code, shift the 1st MSB and send out
 *                      6. Check scale3, if zero, transmit out all the remaining bits of code
 *                         Else, send out 1 and decrease the scale3 by 1
 *  Arguments
 *  in(in)                : The input file contain symbols being encoded
 *  cft(in)               : Cumulative Freq.(CF) Table that store symbol and their own CF
 *  dataLength(in)        : To record the no of symbols encoded
 *  tableSize(in)         : The size of CFT
 *  out(out)              : To store the transmit message (encode value)
 *  arrayPtr(in)          : Use to point the location of data from start
 *  bitLeft(in)           : Total times to transmit the last range->lower
 *  code(in)              : Temporary store range->lower and use for shift and MSB check
 */
void arithmeticEncode(Stream *in, int *dataLength, CFT *cft, int tableSize, Stream *out){
  int arrayPtr = 0, bitLeft = 32; CEXCEPTION_T error;
  uint32 code; int data, encodeDone = 0; Range* range;
  
  range = rangeNew();
  while(!encodeDone){
    Try{
      data = streamReadBits(in,8);
      *dataLength += 1;
      // printf("%c\n",data);
      getRangeOfSymbol(range, data, cft, tableSize);
      // dumpRange(range);
      encoderScaling(range,out);
    }Catch(error){
      encodeDone = 1;
    }
  }
  code = range->lower;

  while(bitLeft!=0){
    if(maskMSB(code) == 0x80000000)
      streamWriteBit(out,1);
    else
      streamWriteBit(out,0);

    while(range->scale3 > 0){
      streamWriteBit(out,1);
      range->scale3 -= 1;
    }
    shiftToLeftBy1Bit(code);
    bitLeft -= 1;
  }
  if(out->bitIndex!=0)  //Not usable in mock code, since out->bitIndex only increment by 1 inside the mock function
    streamFlush(out);
  rangeDel(range);
}











