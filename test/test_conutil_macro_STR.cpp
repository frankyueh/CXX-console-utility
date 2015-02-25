
#include "gtest/gtest.h"

#include "conutil.h"


// -----------------------------------------------------------------------------------
// conutil_macro_SWITCH_STRTest

TEST(conutil_macro_SWITCH_STRTest, General)
{
	const char* paszCaseStr[] = {
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

TEST(conutil_macro_SWITCH_STRTest, StringType)
{
	const char* paszCaseStr[] = {
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

TEST(conutil_macro_SWITCH_STRTest, WithoutBreak)
{
	const char* paszCaseStr[] = {
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

// -----------------------------------------------------------------------------------
// conutil_macro_FOREACH_STR_GETLINETest

TEST(conutil_macro_FOREACH_STR_GETLINETest, General)
{

	int i = 0;
	const char* szTestString = "TokenA:TokenB:TokenC:TokenD";

	FOREACH_STR_GETLINE(std::string cToken, szTestString, ':')
	{
		if (cToken == "TokenA")
		{
			ASSERT_EQ(0, i);
		}
		else if (cToken == "TokenB")
		{
			ASSERT_EQ(1, i);
		}
		else if (cToken == "TokenC")
		{
			ASSERT_EQ(2, i);
		}
		else
		{
			ASSERT_EQ(3, i);
			ASSERT_STREQ("TokenD", cToken.c_str());
		}
		++i;
	}
}

TEST(conutil_macro_FOREACH_STR_GETLINETest, Inline)
{
	int i = 0;
	const char* szTestString = "TokenA:TokenB:TokenC:TokenD";
	FOREACH_STR_GETLINE(std::string cToken, szTestString, ':')
		++i;
	ASSERT_EQ(4, i);
}

TEST(conutil_macro_FOREACH_STR_GETLINETest, Break)
{
	int i = 0;
	const char* szTestString = "TokenA:TokenB:TokenC:TokenD";

	FOREACH_STR_GETLINE(std::string cToken, szTestString, ':')
	{
		++i;
		break;
	}

	ASSERT_EQ(1, i);
}
