package main.java.rest;

import java.util.Vector;

import javax.ws.rs.GET;
import javax.ws.rs.Path;
import javax.ws.rs.PathParam;
import javax.ws.rs.Produces;
import javax.ws.rs.core.MediaType;
import javax.ws.rs.core.Response;

import main.java.db.connection.DBExecutor;
import main.java.db.table.Column;
import main.java.utils.Utils;

/**
 * This classes defines the REST handlers
 * @author 	Ronald T. Fernandez
 * @version 1.0
 */
@Path("/")
public class RESTHandler {
	
	final static String SEP = System.getProperty("file.separator");
	final String CURR_DIR = this.getClass().getClassLoader().getResource("").getPath();
	
	/**
	 * Http allowed response codes
	 * OK: 	http code 200 (success)
	 * NOK: http code 404 (bad request)
	 */
	private enum HttpResponseCode {
		OK(200), 
		NOK(400);
		
		private int code;
		
		/**
		 * Class Constructor
		 * @param code	Http status value
		 */
		HttpResponseCode(int code) {
			this.code = code;
		}
		
		/**
		 * Get the associated status
		 * @return Http status
		 */
		public int getValue() {
			return this.code;
		}
	}
	
	private static Response getResponseWithHeaders(String content, HttpResponseCode status) {
		return Response.ok(content).
				status(status.getValue()).
				header("Access-Control-Allow-Origin","*").
				header("Access-Control-Allow-Methods", "POST, GET, OPTIONS, DELETE").
				header("Access-Control-Max-Age", "3600").
				header("Access-Control-Allow-Headers", "x-requested-with").build();
	}
	
	/**
	 * Publish the swagger settings file
	 * @return The swagger file content or, if an error occurs, the error message
	 */
	@GET
	@Path("/swagger.json")
	@Produces(MediaType.APPLICATION_JSON)
	public Response getSwaggerJson() {
		try {
			final String fileName = CURR_DIR + SEP + ".." + SEP + ".." + SEP + "conf" + SEP + "swagger.json";
			return getResponseWithHeaders(Utils.readFile(fileName), HttpResponseCode.OK);
		} catch (Exception e) {
			return getResponseWithHeaders(e.getMessage(), HttpResponseCode.NOK);
		}
	}
	
	/**
	 * Define the handler when looking for the databases in the database manager in the JSON format
	 * @return The list of databases in JSON format or, if an error occurs, the error message
	 */
	@SuppressWarnings("static-method")
	@GET
	@Path("/alldbs")
	@Produces(MediaType.APPLICATION_JSON)
	public Response getDBsJSON() {
		try {
			Vector<String> dbs = DBExecutor.getDBs();
			return getResponseWithHeaders(JSONGenerator.getJson("databases", dbs), HttpResponseCode.OK);
		} catch (Exception e) {
			return getResponseWithHeaders(e.getMessage(), HttpResponseCode.NOK);
		}
	}
	
	/**
	 * Define the handler when looking for the databases in the database manager in the XML format
	 * @return The list of databases in XML format or, if an error occurs, the error message
	 */
	@SuppressWarnings("static-method")
	@GET
	@Path("/alldbs")
	@Produces(MediaType.APPLICATION_XML)
	public Response getDBsXml() {
		try {
			Vector<String> dbs = DBExecutor.getDBs();
			return getResponseWithHeaders(JSONGenerator.getXml("databases", "database", dbs), HttpResponseCode.OK);
		} catch (Exception e) {
			return getResponseWithHeaders(e.getMessage(), HttpResponseCode.NOK);
		}
	}
	
	/**
	 * Define the handler when looking for the tables in a database in the JSON format
	 * @param dbName	Database name
	 * @return 			The list of tables in the database in JSON format or, if an error occurs, the error message
	 */
	@SuppressWarnings("static-method")
	@GET
	@Path("/alltables/{dbName}")
	@Produces(MediaType.APPLICATION_JSON)
	public Response getTablesJson(@PathParam("dbName") String dbName) {
		try {
			Vector<String> tables = DBExecutor.getTables(dbName);
			return getResponseWithHeaders(JSONGenerator.getJson("tables", tables), HttpResponseCode.OK);
		} catch (Exception e) {
			return getResponseWithHeaders(e.getMessage(), HttpResponseCode.NOK);
		}
	}
	
	/**
	 * Define the handler when looking for the tables in a database in the XML format
	 * @param dbName	Database name
	 * @return 			The list of tables in the database in XML format or, if an error occurs, the error message
	 */
	@GET
	@Path("/alltables/{dbName}")
	@Produces(MediaType.APPLICATION_XML)
	public static Response getTablesXml(@PathParam("dbName") String dbName) {
		try {
			Vector<String> tables = DBExecutor.getTables(dbName);
			return getResponseWithHeaders(JSONGenerator.getXml("tables", "table", tables), HttpResponseCode.OK);
		} catch (Exception e) {
			return getResponseWithHeaders(e.getMessage(), HttpResponseCode.NOK);
		}
	}
	
	/**
	 * Define the handler when looking for a table content in the JSON format
	 * @param dbName	Database name
	 * @param tableName	Table name
	 * @return 			The content of the table in JSON format or, if an error occurs, the error message
	 */
	@GET
	@Path("/table/{dbName}/{tableName}")
	@Produces(MediaType.APPLICATION_JSON)
	public static Response getTableInfoJson(@PathParam("dbName") String dbName, @PathParam("tableName") String tableName) {
		try {
			Column table = DBExecutor.getTableInfo(dbName, tableName);
			return getResponseWithHeaders(JSONGenerator.getJson("table", table), HttpResponseCode.OK);
		} catch (Exception e) {
			return getResponseWithHeaders(e.getMessage(), HttpResponseCode.NOK);
		}
	}
	
	/**
	 * Define the handler when looking for a table content in the XML format
	 * @param dbName	Database name
	 * @param tableName	Table name
	 * @return The content of the table in XML format or, if an error occurs, the error message
	 */
	@GET
	@Path("/table/{dbName}/{tableName}")
	@Produces(MediaType.APPLICATION_XML)
	public static Response getTableInfoXml(@PathParam("dbName") String dbName, @PathParam("tableName") String tableName) {
		try {
			Column table = DBExecutor.getTableInfo(dbName, tableName);
			return getResponseWithHeaders(JSONGenerator.getXml("tables", "table", table), HttpResponseCode.OK);
		} catch (Exception e) {
			return getResponseWithHeaders(e.getMessage(), HttpResponseCode.NOK);
		}
	}
	
	/**
	 * Define the info handler: This is used as to show information about the project
	 * @return The information of the project in HTML format
	 */
	@GET
	@Path("/")
	@Produces(MediaType.TEXT_HTML)
	public static Response getInfo() {
		String host;
		try {
			host = Utils.getRESTHost();
		} catch (Exception e) {
			host = "127.0.0.1";
		}
		int port;
		try {
			port = Utils.getRESTPort();
		} catch (Exception e) {
			port = 8080;
		}
		
		String body = new String();
		body = "<h1>DBtoREST</h1>\n";
		body += "<p><h4>In this project I created a service that allows having access to all the information stored in a ";
		body += "database. More specifically, I have implemented a RESTful service that allows any user to know which ";
		body += "databases and tables exist in the configured database manager as well as show the information contained ";
		body += "in any table. However, in order to skip database manager tables, a filtering mechanism to not show them ";
		body += "has been implemented.</h4></p>\n";
		body += "Possible requests:\n";
		body += "<ul>\n";
		body += "<li>http://" + host + ":" + port + "/DBtoREST/alldbs</li>";
		body += "<li>http://" + host + ":" + port + "/DBtoREST/alltables/&lt;dbName&gt;</li>";
		body += "<li>http://" + host + ":" + port + "/DBtoREST/table/&lt;dbName&gt;/&lt;tableName&gt;</li>";
		body += "</ul>\n";
		
		return getResponseWithHeaders(body, HttpResponseCode.OK);
	}
	
}
