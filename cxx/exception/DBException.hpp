/**
 * @file DBException.hpp
 * @author Ronald T. Fernandez
 * @version 1.0
 */

#ifndef CXX_DB_CONNECTION_DBEXCEPTION_HPP_
#define CXX_DB_CONNECTION_DBEXCEPTION_HPP_

#include <exception>
#include <string>

namespace exception {

class DBException : public std::exception {
private:
	std::string _message;
	int _errorCode;
public:
	DBException(std::string message = "", const int errorCode = -1) : _message(message), _errorCode(errorCode) {};
	const std::string getMessage() const { return _message; };
	const int getErrorCode() const { return _errorCode; };
	const char* what() const throw() { return _message.c_str(); };
	virtual ~DBException() throw() {};
};
};

#endif /* CXX_DB_CONNECTION_DBEXCEPTION_HPP_ */
