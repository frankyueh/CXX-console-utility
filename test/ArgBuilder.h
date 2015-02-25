#ifndef __ARG_BUILDER_H
#define __ARG_BUILDER_H

#include <list>
#include <map>
#include <memory>
#include <sstream>


struct ArgObject
{
	ArgObject(int i) :
		iArgc(i),
		paszArgv(new char*[i])
	{
	}

	~ArgObject()
	{
		for (int i = 0 ; i < iArgc ; ++i)
			delete [] paszArgv[i];
		delete [] paszArgv;
	}

	int iArgc;
	char** paszArgv;
};


class ArgBuilder
{
	typedef std::list<std::string> ArgIList;
	typedef std::map<std::string, std::string> ArgKMap;
public:
	ArgBuilder(
			const std::string cFirstArg,
			const char* szKeyPrefix = "--",
			const char* szKeyValSplitor = "=") :
		m_cKeyPrefix(szKeyPrefix),
		m_cKeyValSplitor(szKeyValSplitor)
	{
		m_cArgIList.push_front(cFirstArg);
	}

	~ArgBuilder()
	{
	}

	const std::string GetKeyPrefix() const
	{
		return m_cKeyPrefix;
	}

	const std::string GetKeyValSplitor() const
	{
		return m_cKeyValSplitor;
	}

	void SetArgI(std::string cVal)
	{
		m_cArgIList.push_back(cVal);
	}

	void SetArgK(std::string cKey, std::string cVal)
	{
		m_cArgKMap[cKey] = cVal;
	}

	std::auto_ptr<ArgObject> CreateArg() const
	{
		std::auto_ptr<ArgObject> ArgObjPtr(
			new ArgObject(m_cArgIList.size() + m_cArgKMap.size()));
		
		int i = 0;

		for (ArgIList::const_iterator cIt = m_cArgIList.begin() ;
				cIt != m_cArgIList.end() ; ++cIt)
		{
			ArgObjPtr->paszArgv[i++] = NewCopyStr(*cIt);
		}

		for (ArgKMap::const_iterator cIt = m_cArgKMap.begin() ;
				cIt != m_cArgKMap.end() ; ++cIt)
		{
			std::stringstream sStrStream;
			sStrStream << m_cKeyPrefix << (*cIt).first << m_cKeyValSplitor << (*cIt).second;
			ArgObjPtr->paszArgv[i++] = NewCopyStr(sStrStream.str());
		}

		return ArgObjPtr;
	}

private:
	char* NewCopyStr(const std::string cSrcStr) const
	{
		char* szStr = new char[cSrcStr.size() + 1];
		memcpy(szStr, cSrcStr.c_str(), cSrcStr.size() + 1);
		return szStr;
	}

	const std::string m_cKeyPrefix;
	const std::string m_cKeyValSplitor;
	ArgIList m_cArgIList;
	ArgKMap m_cArgKMap;
};

#endif
