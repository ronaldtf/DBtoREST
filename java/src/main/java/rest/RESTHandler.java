package main.java.rest;

import java.util.ArrayList;
import java.util.List;
import java.util.Vector;

import javax.ws.rs.GET;
import javax.ws.rs.Path;
import javax.ws.rs.PathParam;
import javax.ws.rs.Produces;
import javax.ws.rs.core.MediaType;

import main.java.db.connection.DBExecutor;
import main.java.db.table.Column;

@Path("/")
public class RESTHandler {

	@GET
	@Path("/dbs")
	@Produces(MediaType.APPLICATION_JSON)
	public static String getDBs() {
		try {
			Vector<String> dbs = DBExecutor.getDBs();
			return "dbs";
		} catch (Exception e) {
			return "";
		}
	}
	
	@GET
	@Path("/alltables/{dbName}")
	@Produces(MediaType.APPLICATION_JSON)
	public static String getTables(@PathParam("dbName") String dbName) {
		try {
			Vector<String> dbs = DBExecutor.getTables(dbName);
			return "dbs";
		} catch (Exception e) {
			return "";
		}
	}
	
	@GET
	@Path("/table/{dbName}/{tableName}")
	@Produces(MediaType.APPLICATION_JSON)
	public static String getTableInfo(@PathParam("dbName") String dbName, @PathParam("tableName") String tableName) {
		try {
			Column table = DBExecutor.getTableInfo(dbName, tableName);
			return "dbs";
		} catch (Exception e) {
			return "";
		}
	}
	
}
