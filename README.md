# DBtoREST
This project consists of implementing a service that shows the information contained in a database. Specifically, I have implemented a RESTful service that allows the user to know which databases and tables exist in the database as well as the information contained in a given table.

## C++
I have implemented a RESTful service that shows the information contained in a MySQL database. In order to build the project, we need a set of libraries/applications:

1. MySQL (<https://www.mysql.com/>): I have opted for a MySQL database to save the information. However, other types of databases could be used.
2. MySQL connector: (<https://www.mysql.com/products/connector/>) This is the plugin used to connect to the MySQL database
3. Restbed (<https://github.com/Corvusoft/restbed>) This library is used to create the RESTful service.
4. RapidJson (<http://rapidjson.org/>) This library is used to create JSON documents. Note that, however, in order to generate XML documents, a customized converter has been used (even though libraries are publicly available, there is no any "official" one).
5. Swagger-UI (optional) (<http://swagger.io/swagger-ui/>) This API can be used to offer a REST interface.
6. http-server (optional) (<https://www.npmjs.com/package/http-server>) This application provides a generic web service.
