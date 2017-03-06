package main.java.exception;

public class DBException extends Exception {
	/**
	 * Message that provoked the exception being thrown.
	 */
	private String _message = "";
	/**
	 * Error code related to the cause that provoked the exception being thrown.
	 */
	private int _errorCode = -1;

	/**
	 * Constructor of the class
	 */
	public DBException() {
	}

	/**
	 * Constructor of the class
	 * @param message	Message that reflects the problem that has occurred
	 */
	public DBException(final String message) {
		this._message = message;
	}

	/**
	 * Constructor of the class
	 * @param message	Message that reflects the problem that has occurred
	 * @param errorCode	Error code related to the cause that provoked the exception
	 */
	public DBException(final String message, final int errorCode) {
		this._message = message;
		this._errorCode = errorCode;
	}

	/**
	 * This method allows getting the error message related to the exception.
	 * @return A string indicating the error message
	 */
	public final String getMessage() { 
		return _message; 
	};

	/**
	 * This method allows getting the error code related to the exception.
	 * @return An integer which indicates the error code
	 */
	public final int getErrorCode() { 
		return _errorCode; 
		};
}
