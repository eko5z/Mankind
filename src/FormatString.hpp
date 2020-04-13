#pragma once

#include <string>
#include <cstdarg>

class FormatString
{
public:
	static std::string StringF(std::string fmt, va_list vl);
	static std::string StringF(std::string fmt, ...);
};

