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
	public static List<String> getDBs() {
		List<String> l = new ArrayList<String>();
		l.add("one");
		return l;
	}
	
	@GET
	@Path("/dbs/tables/")
	@Produces(MediaType.APPLICATION_JSON)
	public static String getTables(@PathParam("tableName") String tableName) {
		return tableName;
	}
	
}
