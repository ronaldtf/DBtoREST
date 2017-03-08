package main.java.rest;

import java.util.Vector;

import javax.ws.rs.GET;
import javax.ws.rs.Path;
import javax.ws.rs.PathParam;
import javax.ws.rs.Produces;
import javax.ws.rs.core.MediaType;

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
	
	/**
	 * Publish the swagger settings file
	 */
	@GET
	@Path("/swagger.json")
	@Produces(MediaType.APPLICATION_JSON)
	public static String getSwaggerJson() {
		try {
			return Utils.readFile("conf/swagger.json");
		} catch (Exception e) {
			return e.getMessage();
		}
	}
	
	/**
	 * Define the handler when looking for the databases in the database manager in the JSON format
	 */
	@GET
	@Path("/alldbs")
	@Produces(MediaType.APPLICATION_JSON)
	public static String getDBsJSON() {
		try {
			Vector<String> dbs = DBExecutor.getDBs();
			return JSONGenerator.getJson("databases", dbs);
		} catch (Exception e) {
			return e.getMessage();
		}
	}
	
	/**
	 * Define the handler when looking for the databases in the database manager in the XML format
	 */
	@GET
	@Path("/alldbs")
	@Produces(MediaType.APPLICATION_XML)
	public static String getDBsXml() {
		try {
			Vector<String> dbs = DBExecutor.getDBs();
			return JSONGenerator.getXml("databases", dbs);
		} catch (Exception e) {
			return e.getMessage();
		}
	}
	
	/**
	 * Define the handler when looking for the tables in a database in the JSON format
	 */
	@GET
	@Path("/alltables/{dbName}")
	@Produces(MediaType.APPLICATION_JSON)
	public static String getTablesJson(@PathParam("dbName") String dbName) {
		try {
			Vector<String> dbs = DBExecutor.getTables(dbName);
			return JSONGenerator.getJson("tables", dbs);
		} catch (Exception e) {
			return e.getMessage();
		}
	}
	
	/**
	 * Define the handler when looking for the tables in a database in the XML format
	 */
	@GET
	@Path("/alltables/{dbName}")
	@Produces(MediaType.APPLICATION_XML)
	public static String getTablesXml(@PathParam("dbName") String dbName) {
		try {
			Vector<String> dbs = DBExecutor.getTables(dbName);
			return JSONGenerator.getXml("tables", dbs);
		} catch (Exception e) {
			return e.getMessage();
		}
	}
	
	/**
	 * Define the handler when looking for a table content in the JSON format
	 */
	@GET
	@Path("/table/{dbName}/{tableName}")
	@Produces(MediaType.APPLICATION_JSON)
	public static String getTableInfoJson(@PathParam("dbName") String dbName, @PathParam("tableName") String tableName) {
		try {
			Column table = DBExecutor.getTableInfo(dbName, tableName);
			return JSONGenerator.getJson("table", table);
		} catch (Exception e) {
			return e.getMessage();
		}
	}
	
	/**
	 * Define the handler when looking for a table content in the XML format
	 */
	@GET
	@Path("/table/{dbName}/{tableName}")
	@Produces(MediaType.APPLICATION_XML)
	public static String getTableInfoXml(@PathParam("dbName") String dbName, @PathParam("tableName") String tableName) {
		try {
			Column table = DBExecutor.getTableInfo(dbName, tableName);
			return JSONGenerator.getXml("table", table);
		} catch (Exception e) {
			return e.getMessage();
		}
	}
	
	/**
	 * Define the info handler: This is used as to show information about the project
	 */
	@GET
	@Path("/")
	@Produces(MediaType.TEXT_HTML)
	public static String getInfo() {
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
		
		return body;
	}
	
}
