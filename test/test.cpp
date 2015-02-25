
#include "gtest/gtest.h"

#include "conutil.h"


int main(int iArgc, char** paszArgv)
{
	::testing::InitGoogleTest(&iArgc, paszArgv);
	::testing::FLAGS_gtest_death_test_style = "threadsafe";

	return RUN_ALL_TESTS();
}
