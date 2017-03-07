package main.java.utils;

import java.io.BufferedReader;
import java.io.File;
import java.io.FileInputStream;
import java.io.FileNotFoundException;
import java.io.IOException;
import java.io.InputStreamReader;
import java.util.Properties;
import java.util.StringTokenizer;
import java.util.Vector;

public final class Utils {

	public static final String DB_CONF = "conf/db.properties";
	public static final String REST_CONF = "conf/rest.properties";
	
	/**
	 * Get the DB connection properties
	 * @return DB connection properties
	 * @throws Exception Throws an exception in case a problem during parsing
	 * the file happened or the file does not exist.
	 */
	public static Properties getDBProperties() throws Exception{
		return parseFile(DB_CONF);
	}

	/**
	 * Get the REST service connection properties
	 * @return REST service properties
	 * @throws Exception Throws an exception in case a problem during parsing
	 * the file happened or the file does not exist.
	 */
	public static Properties getRESTProperties() throws Exception{
		return parseFile(REST_CONF);
	}
	
	/**
	 * Read and parses a properties file
	 * @param confName	Properties file name
	 * @return Return the parsed properties
	 * @throws Exception Throws an exception in case of any problem
	 */
	@SuppressWarnings("resource")
	private static Properties parseFile(final String confName) throws Exception {
		BufferedReader br = null;
		InputStreamReader isr = null;
		FileInputStream fis = null;
		Properties properties = new Properties();
		Exception exception = null;

		try {
			fis = new FileInputStream(new File(confName));
			isr = new InputStreamReader(fis);
			br = new BufferedReader(isr);
			String line;
			// Read and parse the file
			while ((line = br.readLine()) != null) {
				Vector<String> tokens = new Vector<String>();
				StringTokenizer st = new StringTokenizer(line, ":");
				while (st.hasMoreTokens())
					tokens.addElement(st.nextToken().trim());
				if (tokens.size() < 2) {
					exception = new Exception("Invalid configuration file: it must contain lines of type \"key : value\"");
					break;
				}
				properties.put(tokens.elementAt(0), tokens.elementAt(1));
				tokens.clear();
			}
		} 
		// Capture exceptions
		catch (FileNotFoundException fnfe) {
			exception = new Exception("Configuration file does not exist: " + confName);
		} catch (IOException ioe) {
			exception = new Exception("Error reading configuration file: " + confName);
		}

		// Close the streams
		if (br != null)
			br.close();
		if (isr != null)
			isr.close();
		if (fis != null)
			fis.close();
		
		if (exception != null)
			throw exception;
		
		return properties;
	}
	
	/**
	 * Get the host name / IP from the REST properties file
	 * @return Host name / IP for the REST service
	 * @throws Exception An exception is thrown in case the property is not found
	 */
	public static String getRESTHost() throws Exception {
		String host = getRESTProperties().getProperty("host");
		if (host == null)
			throw new Exception("Host parameter has not been set in the REST properties file");
		return host;
	}

	/**
	 * Get the port from the REST properties file
	 * @return Port for the REST service
	 * @throws Exception An exception is thrown in case the property is not found or port is invalid
	 */
	public static int getRESTPort() throws Exception {
		String strPort = getRESTProperties().getProperty("port");
		if (strPort == null)
			throw new Exception("Port parameter has not been set in the REST properties file");
		try {
			int port = Integer.parseInt(strPort);
			if (port == -1)
				throw new NumberFormatException();
			return port;
		} catch (NumberFormatException nfe) {
			throw new Exception("Invalid port (not a valid number: " + strPort + ")");
		}
	}
	
	/**
	 * Read the content of a file and return the String content
	 * @param fileName	Name of the file
	 * @return			Content of the file
	 * @throws IOException Throws an exception is the file is not found or there has been
	 * 					a problem to read it.
	 */
	public static String readFile(String fileName) throws IOException {
		FileInputStream fis = new FileInputStream(new File(fileName));
		InputStreamReader isr = new InputStreamReader(fis);
		BufferedReader br = new BufferedReader(isr);
		String result = new String();
		String line;
		
		while ((line = br.readLine()) != null)
			result += line + "\n";
		br.close();
		isr.close();
		fis.close();
		
		return result;
	}
	
}
