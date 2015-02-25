#ifndef __CONUTIL_H_
#define __CONUTIL_H_

#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <ctime>
#include <string>
#include <iostream>
#include <map>
#include <queue>
#include <sstream>
#include <algorithm> 
#include <functional> 
#include <cctype>
#include <locale>
#include <iomanip>

//
// -----------------------------------------------------------------------------------
//
// string function and macro
//

// string switch/case macro
#define SWITCH_STR(STR)				std::string _cSwStr_ = STR; bool _bSwMatch_ = false, _bSwBreak_ = false; if (0)
#define CASE_STR(STR)				} if (_bSwMatch_ || (!_bSwBreak_ && (_bSwMatch_ = _cSwStr_ == STR))) {
#define BREAK_STR					_bSwMatch_ = false, _bSwBreak_ = true
#define DEFAULT_STR					} if (!_bSwMatch_ && !_bSwBreak_) {

// 
#define FOREACH_STR_GETLINE(CNXT_STR_DECLARE, STR, CHSPLIT)				\
	if(0){}else															\
	for (conutil::__ForeachStrGetlineProxy cForeachProxy(STR, CHSPLIT) ;\
		cForeachProxy.Condition() ; cForeachProxy.Next())				\
		for (CNXT_STR_DECLARE = cForeachProxy.Current() ;				\
			cForeachProxy.iBrkFlag ; --cForeachProxy.iBrkFlag)

namespace conutil
{
	// trim from start
	inline void ltrim(std::string &cStr)
	{
		cStr.erase(cStr.begin(), std::find_if(cStr.begin(), cStr.end(), std::not1(std::ptr_fun<int, int>(std::isspace))));
	}

	// trim from end
	inline void rtrim(std::string &cStr)
	{
		cStr.erase(std::find_if(cStr.rbegin(), cStr.rend(), std::not1(std::ptr_fun<int, int>(std::isspace))).base(), cStr.end());
	}

	// trim from both ends
	inline void trim(std::string &cStr)
	{
		conutil::rtrim(cStr);
		conutil::ltrim(cStr);
	}

	// string to unsigned long long int
	inline long long int atoill(const char *szStr)
	{
		long long int i64Val = 0;

		bool bIsSigned = false;
		if (*szStr && *szStr == '-')
		{
			bIsSigned = true;
			++szStr;
		}

		for (; *szStr ; ++szStr)
			i64Val = 10 * i64Val + (*szStr - '0');

		return bIsSigned ? i64Val * -1 : i64Val;
	}

	// convert string to upper case
	template <typename _Elem, typename _Traits>
	inline void toupper(std::basic_string<_Elem, _Traits>& cStr, const std::locale& cLoc = std::locale())
	{
		typename std::basic_string<_Elem, _Traits>::iterator cIt;
		for (cIt = cStr.begin(); cIt != cStr.end(); ++cIt)
			*cIt = std::use_facet< std::ctype<_Elem> >(cLoc).toupper(*cIt);
	}

	// convert string to lower case
	template <typename _Elem, typename _Traits>
	inline void tolower(std::basic_string<_Elem, _Traits>& cStr, const std::locale& cLoc = std::locale())
	{
		typename std::basic_string<_Elem, _Traits>::iterator cIt;
		for (cIt = cStr.begin(); cIt != cStr.end(); ++cIt)
			*cIt = std::use_facet< std::ctype<_Elem> >(cLoc).tolower(*cIt);
	}

	class __ForeachStrGetlineProxy
	{
	public:
		__ForeachStrGetlineProxy(const std::string& cStr, char chSplit) :
			iBrkFlag(0),
			m_cStrStream(cStr),
			m_chSplitor(chSplit)
		{
			Next();
		}
		mutable int iBrkFlag;
		bool Condition() const
		{
			return !iBrkFlag++ && !m_bIsEnd;
		}
		void Next()
		{
			m_bIsEnd = !std::getline(m_cStrStream, m_cCurrToken, m_chSplitor);
		}
		std::string Current() const
		{
			return m_cCurrToken;
		}
	private:
		std::istringstream m_cStrStream;
		char m_chSplitor;
		std::string m_cCurrToken;
		bool m_bIsEnd;
	};
}

//
// -----------------------------------------------------------------------------------
//
// app argument parsing
//

#define __ARGIV_S										conutil::__static_args_i()
#define __ARGKV_S										conutil::__static_args_s()

#define ARG_PARSE_STATIC(I_ARG_C, PCH_ARG_V)			conutil::__parse_args(I_ARG_C, PCH_ARG_V);

#define ARG_CLEAR_STATIC()								__ARGIV_S.clear();	__ARGKV_S.clear();

#define ARGI_SIZE()										__ARGIV_S.size()
#define ARGI(I_IND)										__ARGIV_S[I_IND]
#define ARGI_INT(I_IND)									conutil::atoi(ARGI(I_IND).c_str())
#define ARGI_ILL(I_IND)									conutil::atoill(ARGI(I_IND).c_str())
#define HAS_ARGI(I_IND)									(__ARGIV_S.find(I_IND) != __ARGIV_S.end())
#define HAS_ARGI_OR_DEF(I_IND, C_DEF)					(HAS_ARGI(I_IND) ? ARGI(I_IND) : std::string(C_DEF))
#define HAS_ARGI_OR_DEF_INT(I_IND, I_DEF)				(HAS_ARGI(I_IND) ? ARGI_INT(I_IND) : I_DEF)
#define HAS_ARGI_OR_DEF_ILL(I_IND, I64_DEF)				(HAS_ARGI(I_IND) ? ARGI_ILL(I64_IND) : I64_DEF)

#define ARGK_SIZE()										__ARGKV_S.size()
#define ARGK(C_ARG)										__ARGKV_S[C_ARG]
#define ARGK_INT(C_ARG)									conutil::atoi(ARGK(C_ARG).c_str())
#define ARGK_ILL(C_ARG)									conutil::atoill(ARGK(C_ARG).c_str())
#define IS_ARGK(C_ARG)									(ARGK(C_ARG).length() != 0)
#define HAS_ARGK(C_ARG)									(__ARGKV_S.find(C_ARG) != __ARGKV_S.end())
#define ARGK_OR_DEF(C_ARG, C_DEF)						(IS_ARGK(C_ARG) ? ARGK(C_ARG) : std::string(C_DEF))
#define HAS_ARGK_OR_DEF(C_ARG, C_DEF)					(HAS_ARGK(C_ARG) ? ARGK(C_ARG) : std::string(C_DEF))
#define ARGK_OR_DEF_INT(C_ARG, I_DEF)					HAS_ARGK_OR_DEF_INT(C_ARG, 1, I_DEF)
#define HAS_ARGK_OR_DEF_INT(C_ARG, I_DEF, I_HDEF)		(HAS_ARGK(C_ARG) ? (IS_ARGK(C_ARG) ? ARGK_INT(C_ARG) : I_DEF) : I_HDEF)
#define ARGK_OR_DEF_ILL(C_ARG, I64_DEF)					HAS_ARGK_OR_DEF_ILL(C_ARG, 1, I64_DEF)
#define HAS_ARGK_OR_DEF_ILL(C_ARG, I64_DEF, I64_HDEF)	(HAS_ARGK(C_ARG) ? (IS_ARGK(C_ARG) ? ARGK_ILL(C_ARG) : I64_DEF) : I64_HDEF)

namespace conutil
{
	inline std::map<std::string, std::string>& __static_args_s()
	{
		static std::map<std::string, std::string> s_cArgs;
		return s_cArgs;
	}

	inline std::map<int, std::string>& __static_args_i()
	{
		static std::map<int, std::string> s_cArgsa;
		return s_cArgsa;
	}

	inline void __parse_args(int iArgc, char** paszArgv)
	{
		__ARGIV_S.clear();
		__ARGKV_S.clear();

		int c = 0;
		for (int i = 0 ; i < iArgc ; ++i)
		{
			if (i == 0 ||
				paszArgv[i][0] != '-' ||
				paszArgv[i][1] != '-')
			{
				__ARGIV_S[c++] = paszArgv[i];
			}
			else
			{
				char* szKeyPos = paszArgv[i] + 2;
				char* szValPos = strchr(paszArgv[i], '=');
				if (szValPos)
				{
					__ARGKV_S[std::string(szKeyPos, szValPos - szKeyPos)] =
						szValPos + 1;
				}
				else
				{
					__ARGKV_S[szKeyPos] = "";
				}
			}
		}
	}
}

//
// -----------------------------------------------------------------------------------
//
// method parameter parsing from text utility
//

#define PARS_USING(PARS)			std::map<int, std::string> &__cLocalParasMap__ = PARS
#define PARS_PARSE(PARSSTR)			__cLocalParasMap__ = conutil::__parse_pars(PARSSTR);

#define PAR_OR_DEF(IND, DEF)		(IND < __cLocalParasMap__.size() ? __cLocalParasMap__[IND] : std::string(DEF))
#define PAR0_OR_DEF(DEF)			PAR_OR_DEF(0, DEF)
#define PAR1_OR_DEF(DEF)			PAR_OR_DEF(1, DEF)
#define PAR2_OR_DEF(DEF)			PAR_OR_DEF(2, DEF)
#define PAR3_OR_DEF(DEF)			PAR_OR_DEF(3, DEF)
#define PAR4_OR_DEF(DEF)			PAR_OR_DEF(4, DEF)
#define PAR5_OR_DEF(DEF)			PAR_OR_DEF(5, DEF)
#define PAR6_OR_DEF(DEF)			PAR_OR_DEF(6, DEF)
#define PAR7_OR_DEF(DEF)			PAR_OR_DEF(7, DEF)
#define PAR8_OR_DEF(DEF)			PAR_OR_DEF(8, DEF)
#define PAR9_OR_DEF(DEF)			PAR_OR_DEF(9, DEF)
#define PAR_OR_DEF_INT(IND, DEF)	(IND < __cLocalParasMap__.size() ? conutil::atoi(__cLocalParasMap__[IND].c_str()) : DEF)
#define PAR0_OR_DEF_INT(DEF)		PAR_OR_DEF_INT(0, DEF)
#define PAR1_OR_DEF_INT(DEF)		PAR_OR_DEF_INT(1, DEF)
#define PAR2_OR_DEF_INT(DEF)		PAR_OR_DEF_INT(2, DEF)
#define PAR3_OR_DEF_INT(DEF)		PAR_OR_DEF_INT(3, DEF)
#define PAR4_OR_DEF_INT(DEF)		PAR_OR_DEF_INT(4, DEF)
#define PAR5_OR_DEF_INT(DEF)		PAR_OR_DEF_INT(5, DEF)
#define PAR6_OR_DEF_INT(DEF)		PAR_OR_DEF_INT(6, DEF)
#define PAR7_OR_DEF_INT(DEF)		PAR_OR_DEF_INT(7, DEF)
#define PAR8_OR_DEF_INT(DEF)		PAR_OR_DEF_INT(8, DEF)
#define PAR9_OR_DEF_INT(DEF)		PAR_OR_DEF_INT(9, DEF)
#define PAR_OR_DEF_ILL(IND, DEF)	(IND < __cParas__.size() ? conutil::atoill(__cParas__[IND].c_str()) : DEF)
#define PAR0_OR_DEF_ILL(DEF)		PAR_OR_DEF_ILL(0, DEF)
#define PAR1_OR_DEF_ILL(DEF)		PAR_OR_DEF_ILL(1, DEF)
#define PAR2_OR_DEF_ILL(DEF)		PAR_OR_DEF_ILL(2, DEF)
#define PAR3_OR_DEF_ILL(DEF)		PAR_OR_DEF_ILL(3, DEF)
#define PAR4_OR_DEF_ILL(DEF)		PAR_OR_DEF_ILL(4, DEF)
#define PAR5_OR_DEF_ILL(DEF)		PAR_OR_DEF_ILL(5, DEF)
#define PAR6_OR_DEF_ILL(DEF)		PAR_OR_DEF_ILL(6, DEF)
#define PAR7_OR_DEF_ILL(DEF)		PAR_OR_DEF_ILL(7, DEF)
#define PAR8_OR_DEF_ILL(DEF)		PAR_OR_DEF_ILL(8, DEF)
#define PAR9_OR_DEF_ILL(DEF)		PAR_OR_DEF_ILL(9, DEF)

namespace conutil
{
	inline std::map<int, std::string> __parse_pars(std::string cParsString)
	{
		std::map<int, std::string> cParasMap;
		std::istringstream cParaStream(cParsString);

		if (std::getline(cParaStream, cParsString, '('))
		{
			int i = 0;
			std::string cPara;

			while (std::getline(cParaStream, cPara, ','))
			{
				size_t s = cPara.find_first_of(')');

				if (s != std::string::npos)
					cPara = cPara.substr(0, s);

				conutil::trim(cPara);
				cParasMap[i++] = cPara;
			}
		}
		return cParasMap;
	}
}

//
// -----------------------------------------------------------------------------------
//
// console cout text coloring utility
//

#define __COLORFILTER_S						conutil::__static_color_filter_flag()

#define COLOR_PARSE_STATIC(SZ_COLOR_FILTER)	conutil::__parse_color_filter_flag(SZ_COLOR_FILTER)
#define COLOR_CLEAR_STATIC()				__COLORFILTER_S = conutil::COLOR_ALL;

#define COLOR(E_COLOR)						conutil::__ColorObj(E_COLOR, __COLORFILTER_S)
#define FORCE_COLOR(E_COLOR)				conutil::__ColorObj(E_COLOR, conutil::COLOR_ALL)
#define COLOR_END()							conutil::__ColorObj(conutil::COLOR_DEFAULT, __COLORFILTER_S)
#define IS_COLOR(E_COLOR)					((E_COLOR & __COLORFILTER_S) != 0)

#define COLOR_NAME_ALL						"all"
#define COLOR_NAME_DEFAULT					"default"
#define COLOR_NAME_PURPLE					"purple"
#define COLOR_NAME_BLUE						"blue"
#define COLOR_NAME_GREEN					"green"
#define COLOR_NAME_YELLOW					"yellow"
#define COLOR_NAME_RED						"red"

namespace conutil
{
	enum Colors
	{
		COLOR_DEFAULT	= 0x01,
		COLOR_PURPLE	= 0x02,
		COLOR_CYAN		= 0x04,	// light blue
		COLOR_GREEN		= 0x08, // light green
		COLOR_YELLOW	= 0x10,
		COLOR_RED		= 0x20,

		COLOR_ALL		= 0xFF
	};

	inline unsigned char& __static_color_filter_flag()
	{
		static unsigned char s_btColorFilterFlag = conutil::COLOR_ALL;
		return s_btColorFilterFlag;
	}

	inline unsigned char __parse_color_filter_flag(const char *szColorFilter)
	{
		__COLORFILTER_S = 0;

		if (::strlen(szColorFilter))
		{
			std::string cColorFilter = szColorFilter;
			tolower(cColorFilter);

			FOREACH_STR_GETLINE(std::string cColor, szColorFilter, ':')
			{
				bool bNot = cColor.find('~') == 0;
				if (bNot)
					cColor = cColor.substr(1);

				SWITCH_STR(cColor)
				{
					CASE_STR(COLOR_NAME_DEFAULT)
						if (bNot)
							__COLORFILTER_S &= COLOR_DEFAULT ^ 0xFF;
						else
							__COLORFILTER_S |= COLOR_DEFAULT;
					BREAK_STR;
					CASE_STR(COLOR_NAME_PURPLE)
						if (bNot)
							__COLORFILTER_S &= COLOR_PURPLE ^ 0xFF;
						else
							__COLORFILTER_S |= COLOR_PURPLE;
					BREAK_STR;
					CASE_STR(COLOR_NAME_BLUE)
						if (bNot)
							__COLORFILTER_S &= COLOR_CYAN ^ 0xFF;
						else
							__COLORFILTER_S |= COLOR_CYAN;
					BREAK_STR;
					CASE_STR(COLOR_NAME_GREEN)
						if (bNot)
							__COLORFILTER_S &= COLOR_GREEN ^ 0xFF;
						else
							__COLORFILTER_S |= COLOR_GREEN;
					BREAK_STR;
					CASE_STR(COLOR_NAME_YELLOW)
						if (bNot)
							__COLORFILTER_S &= COLOR_YELLOW ^ 0xFF;
						else
							__COLORFILTER_S |= COLOR_YELLOW;
					BREAK_STR;
					CASE_STR(COLOR_NAME_RED)
						if (bNot)
							__COLORFILTER_S &= COLOR_RED ^ 0xFF;
						else
							__COLORFILTER_S |= COLOR_RED;
					BREAK_STR;
					DEFAULT_STR
						if (bNot)
							__COLORFILTER_S &= COLOR_ALL ^ 0xFF;
						else
							__COLORFILTER_S |= COLOR_ALL;
				}
			}
		}
	}

	struct __ColorObj
	{
		__ColorObj(Colors e, unsigned char bt) :
			eForeColor(e), btColorFilterFlag(bt) { }
		Colors eForeColor;
		unsigned char btColorFilterFlag;
	};

	template <typename _Elem, typename _Traits>
	inline std::basic_ostream<_Elem, _Traits>& operator<< (std::basic_ostream<_Elem, _Traits>& cStream, const __ColorObj& stColor)
	{

#	ifdef _WIN
		static int s_iDefTextColor = -1;
		HANDLE hStdOut = ::GetStdHandle(STD_OUTPUT_HANDLE);
		if (s_iDefTextColor == -1)
		{
			CONSOLE_SCREEN_BUFFER_INFO stInfo;
			::GetConsoleScreenBufferInfo(hStdOut, &stInfo);
			s_iDefTextColor = stInfo.wAttributes;
		}
#	endif

		static std::map<std::basic_ostream<_Elem, _Traits>*, std::basic_streambuf<_Elem, _Traits>*> s_cOrgBufMap;

		if (s_cOrgBufMap.find(&cStream) == s_cOrgBufMap.end())
			s_cOrgBufMap[&cStream] = cStream.rdbuf();

		if (stColor.btColorFilterFlag & stColor.eForeColor)
		{
			cStream.rdbuf(s_cOrgBufMap[&cStream]);

			switch(stColor.eForeColor)
			{
			case COLOR_PURPLE: // Light Purple
#			ifdef _WIN
				::SetConsoleTextAttribute(hStdOut,
					(FOREGROUND_RED |
					FOREGROUND_BLUE |
					FOREGROUND_INTENSITY));
#			else
				fwrite("\033[0;35m", sizeof(char), 7, stdout);
#			endif
				break;
			case COLOR_CYAN: // Light Cyan
#			ifdef _WIN
				::SetConsoleTextAttribute(hStdOut,
					(FOREGROUND_BLUE |
					FOREGROUND_GREEN |
					FOREGROUND_INTENSITY));
#			else
				fwrite("\033[0;36m", sizeof(char), 7, stdout);
#			endif
				break;
			case COLOR_GREEN: // Light Green
#			ifdef _WIN
				::SetConsoleTextAttribute(hStdOut,
					(FOREGROUND_GREEN |
					FOREGROUND_INTENSITY));
#			else
				fwrite("\033[0;32m", sizeof(char), 7, stdout);
#			endif
				break;
			case COLOR_YELLOW: // Yellow
#			ifdef _WIN
				::SetConsoleTextAttribute(hStdOut,
					(FOREGROUND_RED |
					FOREGROUND_GREEN |
					FOREGROUND_INTENSITY));
#			else
				fwrite("\033[0;33m", sizeof(char), 7, stdout);
#			endif
				break;
			case COLOR_RED: // Light Red
#			ifdef _WIN
				::SetConsoleTextAttribute(hStdOut,
					(FOREGROUND_RED |
					FOREGROUND_INTENSITY));
#			else
				fwrite("\033[0;31m", sizeof(char), 7, stdout);
#			endif
				break;
			default:
#			ifdef _WIN
				::SetConsoleTextAttribute(::GetStdHandle(STD_OUTPUT_HANDLE),
					static_cast<unsigned short>(s_iDefTextColor));
#			else
				fwrite("\033[m", sizeof(char), 3, stdout);
#			endif
			}
			cStream.flush();
		}
		else
		{
			cStream.flush();
			cStream.rdbuf(0);
		}

		return cStream;
	}
}

//
// -----------------------------------------------------------------------------------
//
// sleep_ms
//

#ifdef _WIN
#	include <windows.h>
#else
#	include <pthread.h>
#	include <sys/time.h>
#endif

namespace conutil
{
	inline void sleep_ms(unsigned int nMSec)
	{
#	ifdef _WIN
		Sleep(nMSec);
#	else
		struct timeval stNow;
		gettimeofday(&stNow,NULL);

		struct timespec stWaittill;
		stWaittill.tv_nsec = stNow.tv_usec * 1000 + (nMSec > 0 ? (nMSec % 1000) * 1000000 : 0);
		stWaittill.tv_sec = stNow.tv_sec + (nMSec > 0 ? nMSec / 1000 : 0);

		if (stWaittill.tv_nsec >= 1000000000)
		{
			stWaittill.tv_nsec %= 1000000000;
			stWaittill.tv_sec++;
		}

		static pthread_mutex_t s_stFakeMutex = PTHREAD_MUTEX_INITIALIZER;
		static pthread_cond_t s_stFakeCond = PTHREAD_COND_INITIALIZER;

		pthread_mutex_lock(&s_stFakeMutex);
		pthread_cond_timedwait(&s_stFakeCond, &s_stFakeMutex, &stWaittill);
		pthread_mutex_unlock(&s_stFakeMutex);
#	endif
	}
}

//
// -----------------------------------------------------------------------------------
//
// kbhit, getch
//

#ifdef _WIN
#	include <conio.h>

namespace conutil
{
	inline int kbhit()
	{
		return _kbhit();
	}
	inline int getch()
	{
		return _getch();
	}
}

#else
#	include <unistd.h>
#	include <termios.h>
#	include <sys/select.h>

namespace conutil
{
	inline bool& __static_terminal_is_rawmode()
	{
		static bool s_bIsRawMode = false;
		return s_bIsRawMode;
	}

	inline struct termios& __static_terminal_original_settings()
	{
		static struct termios s_stOriginalSettings;
		return s_stOriginalSettings;
	}

	inline struct termios& __static_terminal_rawmode_settings()
	{
		static struct termios s_stRawModeSettings;
		return s_stRawModeSettings;
	}

	inline void __terminal_reset_mode()
	{
		if (!__static_terminal_is_rawmode())
			return;

		tcsetattr(0, TCSANOW, &__static_terminal_original_settings());

		__static_terminal_is_rawmode() = false;
	}

	inline void __terminal_set_mode()
	{
		if (__static_terminal_is_rawmode())
			return;

		tcgetattr(0, &__static_terminal_original_settings());
		__static_terminal_rawmode_settings() = __static_terminal_original_settings();

		atexit(&__terminal_reset_mode);

		__static_terminal_rawmode_settings().c_lflag &= ~(ECHO | ICANON | ISIG);
		__static_terminal_rawmode_settings().c_cc[VMIN] = sizeof(unsigned char);
		__static_terminal_rawmode_settings().c_cc[VTIME] = 0;
		tcsetattr(0, TCSANOW, &__static_terminal_rawmode_settings());

		__static_terminal_is_rawmode() = true;
	}

	inline int kbhit()
	{
		__terminal_set_mode();

		struct timeval stTimeVal = { 0L, 0L };
		fd_set stFDs;
		FD_ZERO(&stFDs);
		FD_SET(0, &stFDs);
		return select(1, &stFDs, NULL, NULL, &stTimeVal);
	}

	inline int getch()
	{
		__terminal_set_mode();

		unsigned char btBuff;
		int iRead = read(0, &btBuff, sizeof(btBuff));
		return iRead > 0 ? btBuff : iRead;
	}
}
#endif

//
// -----------------------------------------------------------------------------------
//
// command input utility
//

namespace conutil
{
	inline char wait_command(const char *szCmds, int iTimeout = -1)
	{
		static const int CHECK_PERIOD = 30;
		char ch;
		char chCmd = 0;
		int iWait = iTimeout;
		do 
		{
			if (iTimeout < 0 || kbhit())
			{
				ch = getch();
				int i = 0;
				do 
				{
					chCmd = szCmds[i++];
				} while (
					chCmd &&
					ch != chCmd &&
					(((ch < 'A' || ch > 'Z') && (ch < 'a' || ch > 'z')) ||
					(ch + 32 != chCmd && ch - 32 != chCmd)));
			}
			else
			{
				sleep_ms(CHECK_PERIOD);
				if ((iWait -= CHECK_PERIOD) <= 0)
					break;
			}
		} while (!chCmd);

		return chCmd;
	}

	inline std::string input_value(const char *szInputTitle, bool *pbCanceled = NULL)
	{
		std::string cInput;
		std::cout << szInputTitle << std::flush;

		if (!pbCanceled || !(*pbCanceled))
		{
			char ch;
			do 
			{
				ch = getch();

				if (ch == '\r' || ch == '\n')
					break;

				if (ch == 0x1B)
				{
					if (pbCanceled)
						*pbCanceled = true;
					break;
				}

				if (ch == '\b' || ch == 127)
				{
					if (cInput.size())
					{
						cInput = cInput.substr(0, cInput.size() - 1);
						std::cout << "\b \b\033[K" << std::flush;
					}
					continue;
				}

				cInput += ch;
				std::cout << ch << std::flush;
			} while (1);
		}

		std::cout << std::endl;

		return cInput;
	}

	inline int input_value_n(const char *szInputTitle, bool *pbCanceled = NULL)
	{
		std::string cInput;
		std::cout << szInputTitle << std::flush;

		if (!pbCanceled || !(*pbCanceled))
		{
			char ch;
			do 
			{
				ch = getch();

				if (ch == '\r' || ch == '\n')
					break;

				if (ch == 0x1B)
				{
					if (pbCanceled)
						*pbCanceled = true;
					break;
				}

				if (ch == '\b' || ch == 127)
				{
					if (cInput.size())
					{
						cInput = cInput.substr(0, cInput.size() - 1);
						std::cout << "\b \b\033[K" << std::flush;
					}
					continue;
				}

				if (cInput.size() == 0 || cInput.size() > 1)
				{
					if (ch < '0' || ch > '9')
						continue;
				}
				else if (cInput[0] == '0')
				{
					continue;
				}

				cInput += ch;
				std::cout << ch << std::flush;
			} while (1);
		}

		std::cout << std::endl;

		return atoi(cInput.c_str());
	}

}

#endif // __CONUTIL_H_