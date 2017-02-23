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

/**
 * This class is used to indicate that some problem has occurred with the database connection or
 * transaction. It is equivalent to the sql::SQLException in MySQL. However, it has been created
 * in order to offer more flexibility when using databases (we might use a different database,
 * e.g. Oracle)
 */
class DBException : public std::exception {
private:
	/**
	 * Message that provoked the exception being thrown.
	 */
	std::string _message;
	/**
	 * Error code related to the cause that provoked the exception being thrown.
	 */
	int _errorCode;
public:
	/**
	 * Constructor of the class
	 * @param[in] message	Message that reflects the problem that has occurred
	 * @param[in] errorCode	Error code related to the cause that provoked the exception
	 */
	DBException(std::string message = "", const int errorCode = -1) : _message(message), _errorCode(errorCode) {};

	/**
	 * This method allows getting the error message related to the exception.
	 * @return A string indicating the error message
	 */
	const std::string getMessage() const { return _message; };

	/**
	 * This method allows getting the error code related to the exception.
	 * @return An integer which indicates the error code
	 */
	const int getErrorCode() const { return _errorCode; };

	/**
	 * This method allows to get the error message. It is equivalent to the
	 * <code>getMessage</code> method, but it is inherited from the base class.
	 */
	const char* what() const throw() { return _message.c_str(); };

	/**
	 * Class destructor
	 */
	virtual ~DBException() throw() {};
};
};

#endif /* CXX_DB_CONNECTION_DBEXCEPTION_HPP_ */
