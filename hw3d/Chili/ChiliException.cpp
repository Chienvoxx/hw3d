#include "ChiliException.h"
#include <sstream>



ChiliException::ChiliException(int line, const char* file) noexcept
	:line(line), file(file)
{}

const char* ChiliException::what() const noexcept
{
	std::ostringstream oss;
	oss << GetType() << std::endl
		<< GetOriginString();
	whatBuffer = oss.str();
	return whatBuffer.c_str();
}


const char* ChiliException::GetType() const noexcept
{
	return "ChiliException";
}


int ChiliException::GetLine() const noexcept
{
	return line;
}


const std::string& ChiliException::GetFile() const noexcept
{
	return file;
}


const std::string ChiliException::GetOriginString() const noexcept
{
	std::ostringstream oss;
	oss << "[line] " << line << std::endl
		<< " [file] " << file;
	return oss.str();
}



