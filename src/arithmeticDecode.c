#include "arithmeticDecode.h"

/*  tagReader
 *  Function : To read in the first 32 bit of tag value
 *
 *  Arguments
 *  in(in)              : Contain the info of tag
 *  tag(out)            : Use to store the tag value
 *  tagModify(in)       : Use to get 1 byte tag value before shifting
 *  tagPlus(out)        : To store the tag value after shifting
 *  shiftMultiplier(in) : To shift the tagModify to proper location
 */
void tagReader(Stream *in, uint32 *tag){
  uint32 tagModify, tagPlus = 0;
  int shiftMultiplier = 4;
  CEXCEPTION_T error;
  while(shiftMultiplier!=0){
    Try{
      tagModify = streamReadBits(in,8);
      tagModify = tagModify<<(8*(shiftMultiplier - 1));
      tagPlus = tagPlus | tagModify;
      shiftMultiplier = shiftMultiplier - 1;
      in->byteIndex = in->byteIndex + 1;
    }Catch(error){
      shiftMultiplier == 0;
    }
  }
  // printf("Tag : %x\n",tagPlus);
  *(tag) = tagPlus;
}

/*  getSymbolFromTag
 *  Function      : Get the tag and get the symbol from cft.
 *
 *  Arguments     :
 *  range(in)     : pointer to Range struct that contain upper and lower range.
 *  tag(in)       : 32 bit tag used to decode symbol.
 *  cft(in)       : table that contain symbol.
 *  tableSize(in) : Size for the cft.
 *  out(out)      : Use to store the decoded symbol.
 *  A/ B (in)     : temp variables to calculate an value and compare to cum_Freq in cft.
 *
 *  return
 *  decodeSymbol  : to return the symbol decoded.
 */
char getSymbolFromTag(Range *range, uint32 *tag, CFT *cft, int tableSize, Stream *out){
  uint64 A, B;
  uint32 totalCount = cft[tableSize-1].cum_Freq;
  int tablePtr = 0;
  char decodeSymbol;
  A = (*tag - range->lower + 1);
  A = (A * totalCount) - 1;
  B = (uint64)range->upper - range->lower + 1;
  A = A / B;
  while(tablePtr < tableSize){
    if(A < cft[tablePtr].cum_Freq){
      streamWriteByte(out,cft[tablePtr].symbol);
      decodeSymbol = cft[tablePtr].symbol;
      break;
    }
    tablePtr = tablePtr + 1;
  }
  return decodeSymbol;
}

/*  decoderScaling
 *  Function          : To renew the upper/ lower range and tag based on E1,E2,E3 condition
 *                      3 scales -> E1, E2, E3
 *                      E1-> MSB of upper/lower are 0
 *                      E2-> MSB of upper/lower are 1
 *                      E3-> 1st and 2nd MSB of upper/lower are 10/01
 *
 *  Arguments
 *  tag(in)           : store the 32 bit tag
 *  range(in/out)     : The current range with current upper limit and lower limit
 *  in(in)            : File that store tag
 *  upLimit(in)       : Used as mask to determine upper fulfill E1/E2 scaling condition
 *  lowLimit(in)      : Used as mask to determine lower fulfill E1/E2 scaling condition
 *  e3Up/e3Low(in)    : Used as mask to determine upper/lower fulfill E3 scaling condition
 */
void decoderScaling(Range *range, uint32 *tag, Stream *in){
  uint32 upLimit = maskMSB(range->upper), lowLimit = maskMSB(range->lower);
  uint32 e3Up = e3Mask(range->upper), e3Low = e3Mask(range->lower);
  while((upLimit == lowLimit)||((e3Up == MSB10) && (e3Low == MSB01))){
    if(upLimit == lowLimit){                          // E1 || E2 condition
      range->upper = shiftToLeftBy1Bit(range->upper) + 1;
      range->lower = shiftToLeftBy1Bit(range->lower);
      *tag = shiftToLeftBy1Bit(*tag) | streamReadBits(in, 1);
    }
    if((e3Up == MSB10) && (e3Low == MSB01)){          // E3 condition
      range->upper = shiftToLeftBy1Bit(range->upper) + 1;
      range->lower = shiftToLeftBy1Bit(range->lower);
      *tag = shiftToLeftBy1Bit(*tag) | streamReadBits(in, 1);
      range->upper = complementMSB(range->upper);
      range->lower = complementMSB(range->lower);
      *tag = complementMSB(*tag);
    }
    upLimit = maskMSB(range->upper), lowLimit = maskMSB(range->lower);
    e3Up = e3Mask(range->upper), e3Low = e3Mask(range->lower);
  }
}

/*  arithmeticDecode
 *  Function        : Decode tag and retrieve data
 *
 *  How             : 1. Initialize upper and lower of range with 0xFFFFFFFF and 0
 *                    2. Try to decode the first symbol. If success, dataLength minus 1
 *                    3. Repeat the decode process again.
 *                    4. The ranges and tag are updating after decode process
 *                    5. Stop when dataLength equal to 0.
 *
 *  Arguments
 *  dataLength(in)    : The length of data after decode process
 *  tag(in)           : Store 32 bit value, used for decode
 *  cft(in)           : cft store the symbol and used for decode
 *  tableSize(in)     : Size of cft
 *  in(in)            : File store the tag
 *  out(out)          : File store the decoded symbol
 *  decodedSymbol(in) : Store the return symbol from getSymbolFromTag
 *  success(in)       : To record the decode process is success or not
 */
void arithmeticDecode(int dataLength, uint32 *tag, CFT *cft, int tableSize, Stream *out, Stream *in){
  char decodeSymbol;
  int success;
  Range* range;
  range = rangeNew();

  while(dataLength != 0){
    //printf("Data length before : %d \n", dataLength);
    success = 0;
    decodeSymbol = getSymbolFromTag(range, tag, cft, tableSize, out);
    if(decodeSymbol != '\0')
      success = 1;
    dataLength = dataLength - success;
    //printf("Decoded symbol : %c \n", decodeSymbol);
    //printf("Data length after : %d \n", dataLength);
    getRangeOfSymbol(range, decodeSymbol, cft, tableSize);
    decoderScaling(range, tag, in);
  }
  rangeDel(range);
}