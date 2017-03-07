package main.java.rest;

import java.io.IOException;
import java.net.InetAddress;
import java.net.URI;
import java.net.UnknownHostException;
import java.util.Properties;

import javax.ws.rs.core.UriBuilder;

import com.sun.jersey.api.container.httpserver.HttpServerFactory;
import com.sun.jersey.api.core.PackagesResourceConfig;
import com.sun.jersey.api.core.ResourceConfig;
import com.sun.net.httpserver.HttpServer;

import main.java.rest.RESTHandler;
import main.java.utils.Utils;

 
@SuppressWarnings("restriction")
public class Server {
 	
    public static void main(String[] args) throws IOException {

    	String host;
    	int port;
    	
    	try {
    		host = Utils.getRESTHost();
    	} catch (Exception e) {
    		System.err.println("[ERROR] " + e.getMessage() + "\nUsing default host <127.0.0.1>");
    		host = "127.0.0.1";
    	}
    	try {
    		port = Utils.getRESTPort();
    	} catch (Exception e) {
    		System.err.println("[ERROR] " + e.getMessage() + "\nUsing a default one <8080>");
    		port = 8080;
    	}

        // Define handler path
        ResourceConfig resourceConfig = new PackagesResourceConfig("main.java.rest");
        // Start the server
        URI uri = getURI(host, port);
        HttpServer httpServer =  HttpServerFactory.create(uri, resourceConfig);
        //httpServer.createContext("/DBtoREST/swagger.json", new SwaggerJSONStandaloneHandler());
        
        System.out.println("Starting server on " + uri.toString() + "... (see application.wadl for further details)");
        httpServer.start();
        
    }
 
    private static URI getURI(String host, int port) {
        return UriBuilder.fromUri("http://" + host + "/DBtoREST").port(port).build();
    }
 
}