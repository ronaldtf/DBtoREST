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

/**
 * This class is used to indicate that a parsing problem has occurred. In this project,
 * it is used when a problem is found when parsing a JSON document.
 */
class ParseException : public std::exception {
private:
	/**
	 * Message that provoked the exception being thrown.
	 */
	std::string _message;
public:
	/**
	 * Constructor of the class
	 * @param[in] message	Message that reflects the problem that has occurred
	 */
	ParseException(std::string message = "") : _message(message) {};

	/**
	 * This method allows getting the error message related to the exception.
	 * @return A string indicating the error message
	 */
	const std::string getMessage() const { return _message; };

	/**
	 * This method allows to get the error message. It is equivalent to the
	 * <code>getMessage</code> method, but it is inherited from the base class.
	 */
	const char* what() const throw() { return _message.c_str(); };

	/**
	 * Class destructor
	 */
	virtual ~ParseException() throw() {};
};
};

#endif /* CXX_EXCEPTION_PARSEEXCEPTION_HPP_ */
