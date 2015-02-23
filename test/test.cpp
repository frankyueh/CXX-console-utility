
#include "gtest/gtest.h"

#include "conutil.h"

int main(int iArgc, char** pchArgv)
{
	/* TODO: test kbhit and getch
	while (!conutil::kbhit())
	{
		conutil::sleep_ms(100);
	}

	std::cout << conutil::getch() << std::endl << std::flush;
	std::cout << conutil::getch() << std::endl << std::flush;
	*/

	::testing::InitGoogleTest(&iArgc, pchArgv);
	::testing::FLAGS_gtest_death_test_style = "threadsafe";

	return RUN_ALL_TESTS();
}
