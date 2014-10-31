#include "CustomAssertion.h"
#include "Error.h"
#include "unity.h"

void assertFileData(Stream* expectedInFile, Stream* actualOutFile, const UNITY_LINE_TYPE lineNumber){
	int i,getChar1,getChar2;		
	CEXCEPTION_T error;
	
	if(expectedInFile == NULL)
		UNITY_TEST_FAIL(lineNumber, "There no Input File.\n");
	if(actualOutFile == NULL)
		UNITY_TEST_FAIL(lineNumber, "There no Output File.\n");
		
	Try{
	  for(i = 0; ; i++){
		getChar1 = streamReadBits(expectedInFile,8);
		getChar2 = streamReadBits(actualOutFile,8);
		UNITY_TEST_ASSERT_EQUAL_INT(getChar1,getChar2,lineNumber,"The both character not the same.\n");
	  }
	}Catch(error){
		TEST_ASSERT_EQUAL(ERR_END_OF_FILE,error);
	}
}

// void TEST_ASSERT_EQUAL_FILE(Stream *inFile, Stream *outFile){
  // int i,getChar1,getChar2;
  
  // Try{
	  // for(i = 0; ; i++){
		// getChar1 = streamReadBits(inFile,8);
		// getChar2 = streamReadBits(outFile,8);

		// TEST_ASSERT_EQUAL(getChar1, getChar2);
	  // }
	// }Catch(error){
    // TEST_ASSERT_EQUAL(ERR_END_OF_FILE,error);
  // }
// }