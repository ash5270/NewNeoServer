#pragma once
#include <string>
#include <vector>
#include <optional>
#include <io.h>

std::optional<std::vector<std::wstring>> GetFilesInDir(const std::wstring& path, const std::wstring& filter)
{
	std::wstring resultPath = path + filter;
	std::vector<std::wstring> resultVec;

	_wfinddata_t fd;
	intptr_t handle = _wfindfirst(resultPath.c_str(), &fd);
	if (handle == -1)
		return std::nullopt;
	int result = 0;
	while(result !=-1)
	{
		resultVec.push_back(fd.name);
		result = _wfindnext(handle, &fd);
	}

	_findclose(handle);
	return resultVec;
}
