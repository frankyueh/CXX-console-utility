
#include "gtest/gtest.h"

#include "conutil.h"


TEST(conutil_SWITCH_STRTest, General)
{
	char* paszCaseStr[] = {
		"CaseA", "CaseB", "CaseC", "CaseD", "Default"
	};
	size_t sCaseStrSize = sizeof(paszCaseStr) / sizeof(char*);

	for (size_t i = 0 ; i < sCaseStrSize ; ++i)
	{
		SWITCH_STR(paszCaseStr[i])
		{
			CASE_STR("CaseA")
				ASSERT_STREQ("CaseA", paszCaseStr[i]);
			BREAK_STR;
			CASE_STR("CaseB")
				ASSERT_STREQ("CaseB", paszCaseStr[i]);
			BREAK_STR;
			CASE_STR("CaseC")
				ASSERT_STREQ("CaseC", paszCaseStr[i]);
			BREAK_STR;
			CASE_STR("CaseD")
				ASSERT_STREQ("CaseD", paszCaseStr[i]);
			BREAK_STR;
			DEFAULT_STR
				ASSERT_STREQ("Default", paszCaseStr[i]);
		}
	}
}

TEST(conutil_SWITCH_STRTest, StringType)
{
	char* paszCaseStr[] = {
		"CaseA", "CaseB", "CaseC", "CaseD", "Default"
	};
	size_t sCaseStrSize = sizeof(paszCaseStr) / sizeof(char*);

	for (size_t i = 0 ; i < sCaseStrSize ; ++i)
	{
		SWITCH_STR(std::string(paszCaseStr[i]))
		{
			CASE_STR("CaseA")
				ASSERT_STREQ("CaseA", paszCaseStr[i]);
			BREAK_STR;
			CASE_STR(std::string("CaseB"))
				ASSERT_STREQ("CaseB", paszCaseStr[i]);
			BREAK_STR;
			CASE_STR("CaseC")
				ASSERT_STREQ("CaseC", paszCaseStr[i]);
			BREAK_STR;
			CASE_STR(std::string("CaseD"))
				ASSERT_STREQ("CaseD", paszCaseStr[i]);
			BREAK_STR;
			DEFAULT_STR
				ASSERT_STREQ("Default", paszCaseStr[i]);
		}
	}
}

TEST(conutil_SWITCH_STRTest, WithoutBreak)
{
	char* paszCaseStr[] = {
		"CaseA", "CaseB", "CaseC", "CaseD", "Default"
	};
	size_t sCaseStrSize = sizeof(paszCaseStr) / sizeof(char*);

	for (size_t i = 0 ; i < sCaseStrSize ; ++i)
	{
		int j = 0;
		SWITCH_STR(paszCaseStr[i])
		{
			CASE_STR("CaseA")
				ASSERT_STREQ("CaseA", paszCaseStr[i]);
				++j;
			CASE_STR("CaseB")
				if (strcmp("CaseA", paszCaseStr[i]) == 0)
					ASSERT_EQ(1, j);
				if (strcmp("CaseB", paszCaseStr[i]) == 0)
					ASSERT_EQ(0, j);
				++j;
			CASE_STR("CaseC")
				if (strcmp("CaseA", paszCaseStr[i]) == 0)
					ASSERT_EQ(2, j);
				if (strcmp("CaseB", paszCaseStr[i]) == 0)
					ASSERT_EQ(1, j);
				if (strcmp("CaseC", paszCaseStr[i]) == 0)
					ASSERT_EQ(0, j);
				++j;
			CASE_STR("CaseD")
				if (strcmp("CaseA", paszCaseStr[i]) == 0)
					ASSERT_EQ(3, j);
				if (strcmp("CaseB", paszCaseStr[i]) == 0)
					ASSERT_EQ(2, j);
				if (strcmp("CaseC", paszCaseStr[i]) == 0)
					ASSERT_EQ(1, j);
				if (strcmp("CaseD", paszCaseStr[i]) == 0)
					ASSERT_EQ(0, j);
				++j;
			BREAK_STR;
			DEFAULT_STR
				if (strcmp("CaseA", paszCaseStr[i]) == 0)
					ASSERT_EQ(4, j);
				if (strcmp("CaseB", paszCaseStr[i]) == 0)
					ASSERT_EQ(3, j);
				if (strcmp("CaseC", paszCaseStr[i]) == 0)
					ASSERT_EQ(2, j);
				if (strcmp("CaseD", paszCaseStr[i]) == 0)
					ASSERT_EQ(1, j);
				if (strcmp("Default", paszCaseStr[i]) == 0)
					ASSERT_EQ(0, j);
		}
	}
}
