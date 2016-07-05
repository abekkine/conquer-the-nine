#ifndef EXCEPTION_H_
#define EXCEPTION_H_

#include <string>
#include <exception>

class Exception : public std::exception
{
private:
	std::string message_;
public:
	Exception(std::string message) : message_(message) {}
	virtual const char* what() const throw()
	{
		return message_.c_str();
	}
};

#endif // EXCEPTION_H_


