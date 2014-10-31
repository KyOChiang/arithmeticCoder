#ifndef _CUSTOM_ASSERTION_H_
#define _CUSTOM_ASSERTION_H_
#include "Stream.h"

#define TEST_ASSERT_EQUAL_FILE(expectedInFile, actualOutFile) \
 assertFileData( expectedInFile, actualOutFile, __LINE__);

#endif //_CUSTOM_ASSERTION_H_