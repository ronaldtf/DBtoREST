# DBtoREST
In this project I created a service that allows having access to all the information stored in a database. More specifically, I have implemented a RESTful service that allows any user to know which databases and tables exist in the configured database manager as well as show the information contained in any table. However, in order to skip database manager tables, a filtering mechanism to not show them have been implemented

___

This project consists of a service which uses two main components:
* <b>Database</b>: This is an essential component because it is the one that has all data. Without a database or with an empty database, no information will be available.
* <b>REST Service</b>: This is the interface to the user. Through the service, the user can interact with the system, such as requesting the information for a specific table or indicating the format used to return the results.  

## Implementation Details

Below I show briefly the main implementation details:

* Database: 

  - Connection Pool: This pool of connections has been defined in order to not exceed the maximum number of connections to the database. In this case, the class <code>DBConnectionPool</code> implements the Object Pool and Singleton design patterns.

  - MySQL Adapter: Although in this project I have used a MySQL database, I made an extensible implementation by using the Adapter design pattern (<code>DBConnectionAdapter</code>). This way, in case we need to use a different database (e.g. Oracle), we simply need to create another adapter class that extends from the <code>DBConnection</code> class and call it in the <code>DBConnectionPool</code> instead of the existing one. <code>DBExecutor</code> is a class that mainly delegates its functionality in the Adapter.

  - Dynamic Tables: A priori we do not know what are the contents of any table in the database. Therefore, we need a dynamic mechanism in order to save the contents of the table into a class. the <code>Column</code> class provides a mechanism to save all the rows and columns of a table, regardless of the size and number of columns of the table.

* Service: 

  - REST: A RESTful service has been implemented as a way to interact with the system. The <code>Server</code> class implements the service and the REST handlers are implemented in the <code>RESTHandler</code> class.

  - JSON/XML: It is possible to provide the information to the user through the REST interface in two different formats: JSON and XML. Using one or the other depends on the request. In any case, although format changes, the data displayed is the same for both cases. <code>JsonGenerator</code> formats the data in the JSON style. In <code>JsonToXml</code> class, data in JSON format is converted to XML. Note that, although we could have used a library to do the conversion from JSON to XML, I opted here to implement my own converter because I have not found any "standard" one. Although the JSON to XML converter implemented works quite well, it has the limitation that multiple spaces are not allowed and are converted to a single space (this limitation should not be a problem).

* Configuration:

  - DB: A properties file with the parameters to get connected to the database has been defined. This avoids to recompile the project when changing the settings.

  - REST: Host name and port of the REST service which is being created is defined in a properties file. This avoids to recompile the project when changing the settings.


## Requirements
The project has been created in C++ an using a set of libraries. The set of libraries/APIs used here are mainly standard:

1. MySQL (<https://www.mysql.com/>): In this project I opted to use the MySQL database, although any other kind of database should be possible. In order to execute the project, the MySQL database has to be installed on the system. Note that </code>db.properties</code> file has to be aligned with the database settings.

2. MySQL connector (<https://www.mysql.com/products/connector/>): This is the plugin used to connect to the MySQL database.

3. Restbed (<https://github.com/Corvusoft/restbed>): This library is used to create the REST service.

4. RapidJson (<http://rapidjson.org/>): This library is used to create JSON documents. However, note that, as mentioned above, in order to generate XML documents, a customized converter has been used.

5. Swagger-UI (optional) (<http://swagger.io/swagger-ui/>): This API provides a friendly interface to access to a REST service.

6. http-server (optional) (<https://www.npmjs.com/package/http-server>): This application provides a generic web service (used together with swagger-ui).

## Compilation and Execution


