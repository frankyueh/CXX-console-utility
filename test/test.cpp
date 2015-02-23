
#include "gtest/gtest.h"

#include "conutil.h"

void test_kbhit_getch()
{
	std::cout << "====== test kbhit/getch begin ======" << std::endl;

	std::cout
		<< "kbhit() waiting any key hit (without any hit 3 second for ignoring the test)" << std::flush;

	int iWaited = 0;
	while (!conutil::kbhit())
	{
		conutil::sleep_ms(250);
		std::cout << "." << std::flush;

		iWaited += 250;
		if (iWaited >= 3000)
		{
			std::cout
				<< std::endl
				<< "====== test kbhit/getch ignored ======" << std::endl;
			return;
		}
	}

	std::cout
		<< std::endl
		<< "getch() fetch key immediately after kbhit(): " << std::flush;
	std::cout
		<< conutil::getch() << std::endl << std::flush;

	std::cout
		<< "getch() blocked until any key hit: " << std::flush;
	std::cout
		<< conutil::getch() << std::endl << std::flush;

	std::cout << "====== test kbhit/getch end ======" << std::endl;
}

int main(int iArgc, char** pchArgv)
{
	test_kbhit_getch();

	::testing::InitGoogleTest(&iArgc, pchArgv);
	::testing::FLAGS_gtest_death_test_style = "threadsafe";

	return RUN_ALL_TESTS();
}
