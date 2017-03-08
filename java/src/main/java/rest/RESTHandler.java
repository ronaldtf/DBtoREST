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

@Path("/")
public class RESTHandler {
	
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
	
	@GET
	@Path("/alldbs")
	@Produces(MediaType.APPLICATION_JSON)
	public static String getDBs() {
		try {
			System.out.println("Aqui1");
			Vector<String> dbs = DBExecutor.getDBs();
			return JSONGenerator.getJson("tables", dbs);
		} catch (Exception e) {
			return e.getMessage();
		}
	}
	
	@GET
	@Path("/alltables/{dbName}")
	@Produces(MediaType.APPLICATION_JSON)
	public static String getTables(@PathParam("dbName") String dbName) {
		try {
			System.out.println("Aqui2");
			Vector<String> dbs = DBExecutor.getTables(dbName);
			return JSONGenerator.getJson("databases", dbs);
		} catch (Exception e) {
			return e.getMessage();
		}
	}
	
	@GET
	@Path("/table/{dbName}/{tableName}")
	@Produces(MediaType.APPLICATION_JSON)
	public static String getTableInfo(@PathParam("dbName") String dbName, @PathParam("tableName") String tableName) {
		try {
			System.out.println("Aqui3");
			Column table = DBExecutor.getTableInfo(dbName, tableName);
			return JSONGenerator.getJson("table", table);
		} catch (Exception e) {
			return e.getMessage();
		}
	}
	
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
