
#include "gtest/gtest.h"

#include "conutil.h"
#include "ArgBuilder.h"

#include <sstream>
#include <list>


class conutil_ARGTest : public ::testing::Test
{
protected:

	virtual void SetUp()
	{
		ARG_CLEAR_STATIC();
	}

	virtual void TearDown()
	{
	}

	void TestArg(int iArgc, char** paszArgv, const char* szKeyPrefix, const char* szKeyValSplitor)
	{
		int iKeyPrefixLen = strlen(szKeyPrefix);

		ASSERT_EQ(iArgc, ARGI_SIZE() + ARGK_SIZE());
		
		int iArgIind = 0;
		for (int i = 0 ; i < iArgc ; ++i)
		{
			if (i == 0 ||
				strncmp(paszArgv[i], szKeyPrefix, iKeyPrefixLen) != 0)
			{
				ASSERT_STREQ(paszArgv[i], ARGI(iArgIind).c_str());
				ASSERT_TRUE(HAS_ARGI(iArgIind));

				std::string cVal = paszArgv[i];
				std::string cValDef = "__DEF__" + cVal;
				ASSERT_STREQ(cVal.c_str(), HAS_ARGI_OR_DEF(iArgIind, cValDef).c_str());

				++iArgIind;
			}
			else
			{
				const char* szKeyPos = paszArgv[i] + iKeyPrefixLen;
				const char* szValPos = strstr(paszArgv[i], szKeyValSplitor);

				std::string cKey, cVal;
				if (szValPos)
				{
					cKey = std::string(szKeyPos, szValPos - szKeyPos);
					cVal = szValPos + strlen(szKeyValSplitor);
				}
				else
				{
					cKey = szKeyPos;
					cVal = "";
				}

				std::string cValDef = "__DEF__" + cVal;

				ASSERT_TRUE(HAS_ARGK(cKey));
				ASSERT_STREQ(
					cVal.c_str(),
					ARGK(cKey.c_str()).c_str());

				if (cVal.length())
				{
					ASSERT_TRUE(IS_ARGK(cKey));
					ASSERT_STREQ(cVal.c_str(), ARGK_OR_DEF(cKey, cValDef).c_str());
					ASSERT_STREQ(cVal.c_str(), HAS_ARGK_OR_DEF(cKey, cValDef).c_str());
				}
				else
				{
					ASSERT_FALSE(IS_ARGK(cKey));
					ASSERT_STREQ(cValDef.c_str(), ARGK_OR_DEF(cKey, cValDef).c_str());
					ASSERT_STREQ(cVal.c_str(), HAS_ARGK_OR_DEF(cKey, cValDef).c_str());
				}
			}
		}
	}

private:
};

TEST_F(conutil_ARGTest, ARGITest)
{
	const int TEST_ARG_NUM = 1000;

	ArgBuilder cArgBuilder("ARGITest");

	for (int i = 0 ; i < TEST_ARG_NUM ; ++i)
	{
		std::stringstream cStrStream;
		cStrStream << "ARGITest_" << i;
		cArgBuilder.SetArgI(cStrStream.str());
	}

	std::auto_ptr<ArgObject> cArgObj = cArgBuilder.CreateArg();

	ARG_PARSE_STATIC(cArgObj->iArgc, cArgObj->paszArgv);

	TestArg(
		cArgObj->iArgc,
		cArgObj->paszArgv,
		cArgBuilder.GetKeyPrefix().c_str(),
		cArgBuilder.GetKeyValSplitor().c_str());
}

TEST_F(conutil_ARGTest, ARGKTest)
{
	const int TEST_ARG_NUM = 1000;

	ArgBuilder cArgBuilder("ARGKTest");

	for (int i = 0 ; i < TEST_ARG_NUM ; ++i)
	{
		std::stringstream cStrKeyStream;
		cStrKeyStream << "ARGKTest_Key_" << i;
		std::stringstream cStrValStream;
		cStrValStream << "ARGKTest_Val_" << i;
		cArgBuilder.SetArgK(cStrKeyStream.str(), cStrValStream.str());
	}

	std::auto_ptr<ArgObject> cArgObj = cArgBuilder.CreateArg();

	ARG_PARSE_STATIC(cArgObj->iArgc, cArgObj->paszArgv);

	TestArg(
		cArgObj->iArgc,
		cArgObj->paszArgv,
		cArgBuilder.GetKeyPrefix().c_str(),
		cArgBuilder.GetKeyValSplitor().c_str());
}

TEST_F(conutil_ARGTest, ARGI_ARGK_MixTest)
{
	const int TEST_ARG_NUM = 1000;

	ArgBuilder cArgBuilder("ARGKTest");

	for (int i = 0 ; i < TEST_ARG_NUM ; ++i)
	{
		std::stringstream cStrStream;
		cStrStream << "ARGITest_" << i;
		cArgBuilder.SetArgI(cStrStream.str());
	}

	for (int i = 0 ; i < TEST_ARG_NUM ; ++i)
	{
		std::stringstream cStrKeyStream;
		cStrKeyStream << "ARGKTest_Key_" << i;
		std::stringstream cStrValStream;
		cStrValStream << "ARGKTest_Val_" << i;
		cArgBuilder.SetArgK(cStrKeyStream.str(), cStrValStream.str());
	}

	std::auto_ptr<ArgObject> cArgObj = cArgBuilder.CreateArg();

	ARG_PARSE_STATIC(cArgObj->iArgc, cArgObj->paszArgv);

	TestArg(
		cArgObj->iArgc,
		cArgObj->paszArgv,
		cArgBuilder.GetKeyPrefix().c_str(),
		cArgBuilder.GetKeyValSplitor().c_str());
}
