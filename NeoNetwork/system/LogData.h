//로그 출력을 위한 로그 데이터  
//
#pragma once
#include <string>
namespace neo::system
{
	//LOG Type
	enum class LogType : uint32_t	
	{
		//확인을 위한 용도
		LOG_INFO=0,
		//경고
		LOG_WARNING,
		//에러
		LOG_ERROR,
		//디버그 용도
		LOG_DEBUG,
	};

	enum class FontColor : WORD
	{
		Blue =1,
		Green =2,
		Cyan=3,
		Red=4,
		Purple=5,
		Yellow=6,
		Default_White =7
	};

	//Log Data 
	struct LogData
	{
		LogType Type;
		std::wstring LogMessage;
	};
}
