﻿#pragma once
#include <string>
#include <Windows.h>

#include <json.hpp>


//utf8으로 인코딩 된것을 unicode를 바꿔줌
std::wstring Utf8ToUnicode(const std::string& utf8)
{
	std::wstring result;
	if (utf8.size() < 0)
		return result;
	int nLen = MultiByteToWideChar(CP_UTF8, 0, utf8.c_str(), static_cast<int>(strlen(utf8.c_str())), NULL, NULL);
	if (nLen < 0)
		return result;
	//reserve사용시 wchar_t * nLen 길이만큼 메모리를 할당해버림
	result.resize(nLen);
	MultiByteToWideChar(CP_UTF8, 0, utf8.c_str(),
		strlen(utf8.c_str()), &result[0], nLen);
	return result;
}

std::wstring Utf8ToUnicode(const nlohmann::json& json)
{
	std::wstring result;
	if (json.dump().size() < 0)
		return result;
	int nLen = MultiByteToWideChar(CP_UTF8, 0, json.dump().c_str(), static_cast<int>(strlen(json.dump().c_str())), NULL, NULL);
	if (nLen < 0)
		return result;
	//reserve사용시 wchar_t * nLen 길이만큼 메모리를 할당해버림
	result.resize(nLen);
	MultiByteToWideChar(CP_UTF8, 0, json.dump().c_str(),
		strlen(json.dump().c_str()), &result[0], nLen);
	return result;
}
