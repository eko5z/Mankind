#include "FormatString.hpp"

std::string FormatString::StringF(std::string fmt, va_list vl)
{
	std::string text;
	va_list vl2;
	va_copy(vl2, vl);
	size_t text_size = vsnprintf(nullptr, 0, fmt.c_str(), vl);
	char *tmp_str = new char[text_size+1]();
	vsnprintf(tmp_str, text_size+1, fmt.c_str(), vl2);
	text = std::string(tmp_str);
	delete[] tmp_str;
	return text;
}

std::string FormatString::StringF(std::string fmt, ...)
{
	std::string text;
	va_list fmt_list;
	va_start(fmt_list, fmt);
	text = FormatString::StringF(fmt, fmt_list);
	va_end(fmt_list);
	return text;
}

