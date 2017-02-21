/**
 * @file ParseException.hpp
 * @author Ronald T. Fernandez
 * @version 1.0
 */

#ifndef CXX_EXCEPTION_PARSEEXCEPTION_HPP_
#define CXX_EXCEPTION_PARSEEXCEPTION_HPP_

#include <exception>
#include <string>

namespace exception {

class ParseException : public std::exception {
private:
	std::string _message;
public:
	ParseException(std::string message = "") : _message(message) {};
	const std::string getMessage() const { return _message; };
	const char* what() const throw() { return _message.c_str(); };
	virtual ~ParseException() throw() {};
};
};

#endif /* CXX_EXCEPTION_PARSEEXCEPTION_HPP_ */
