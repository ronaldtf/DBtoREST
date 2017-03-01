package main.java.rest;

import java.io.IOException;
import java.net.InetAddress;
import java.net.URI;
import java.net.UnknownHostException;

import javax.ws.rs.core.UriBuilder;

import com.sun.jersey.api.container.httpserver.HttpServerFactory;
import com.sun.jersey.api.core.PackagesResourceConfig;
import com.sun.jersey.api.core.ResourceConfig;
import com.sun.net.httpserver.HttpServer;

 
@SuppressWarnings("restriction")
public class Server {
 
    public static void main(String[] args) throws IOException {
        System.out.println("Starting HTTPServer...\n");
        // Define handler path
        ResourceConfig resourceConfig = new PackagesResourceConfig("main.java.rest");
        // Start the server
        HttpServer httpServer =  HttpServerFactory.create(getURI(), resourceConfig);
        
        System.out.println("Starting server at " + getURI() + " (see application.wadl for further details)");
        httpServer.start();
    }
 
    private static URI getURI() {
        return UriBuilder.fromUri("http://localhost/").port(8080).build();
    }
 
}