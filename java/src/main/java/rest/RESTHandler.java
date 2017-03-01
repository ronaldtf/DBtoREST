package main.java.rest;

import java.util.ArrayList;
import java.util.List;

import javax.ws.rs.GET;
import javax.ws.rs.Path;
import javax.ws.rs.PathParam;
import javax.ws.rs.Produces;
import javax.ws.rs.core.MediaType;

@Path("/")
public class RESTHandler {

	@GET
	@Path("/dbs")
	@Produces(MediaType.APPLICATION_JSON)
	public static String getDBs() {
		return "dbs";
	}
	
	@GET
	@Path("/alltables/{dbName}")
	@Produces(MediaType.APPLICATION_JSON)
	public static String getTables(@PathParam("dbName") String dbName) {
		return dbName;
	}
	
	@GET
	@Path("/table/{dbName}/{tableName}")
	@Produces(MediaType.APPLICATION_JSON)
	public static String getTableInfo(@PathParam("dbName") String dbName, @PathParam("tableName") String tableName) {
		return dbName + " " + tableName;
	}
	
}
