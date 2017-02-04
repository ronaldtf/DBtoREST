FLAGS = -std=c++11 -Wall
EXTRA_INC = -I$(MYSQL_CONNECTOR_HOME)/include -I$(RESTBED_HOME)/include
EXTRA_LIB = -L$(MYSQL_CONNECTOR_HOME)/lib -L$(RESTBED_HOME)/library -lmysqlcppconn -lrestbed
all:
	g++ $(FLAGS) -o utils/Utils.o -c utils/Utils.cpp
	g++ $(FLAGS) -o db/table/Column.o -c db/table/Column.cpp
	g++ $(FLAGS) $(EXTRA_INC) -o db/DBConnectionPool.o -c db/DBConnectionPool.cpp
	g++ $(FLAGS) $(EXTRA_INC) -o db/DBConnector.o -c db/DBConnector.cpp
	g++ $(FLAGS) $(EXTRA_INC) -o rest/JsonGenerator.o -c rest/JsonGenerator.cpp
	g++ $(FLAGS) $(LDFLAGS) $(CPPFLAGS) $(EXTRA_INC) $(EXTRA_LIB) -o rest/Server db/DBConnectionPool.o db/DBConnector.o utils/Utils.o rest/JsonGenerator.o rest/Server.cpp
clean:
	rm -rf rest/Server */*.o */*/*.o
