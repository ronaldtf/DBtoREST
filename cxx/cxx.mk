FLAGS = -std=c++11 -Wall
EXTRA_INC = -I$(MYSQL_CONNECTOR_HOME)/include -I$(RESTBED_HOME)/include
EXTRA_LIB = -L$(MYSQL_CONNECTOR_HOME)/lib -L$(RESTBED_HOME)/library -lmysqlcppconn -lrestbed
all:
	g++ $(FLAGS) -o utils/Utils.o -c utils/Utils.cpp
	g++ $(FLAGS) -o db/table/Column.o -c db/table/Column.cpp
	g++ $(FLAGS) $(EXTRA_INC) -o db/pool/DBConnectionPool.o -c db/pool/DBConnectionPool.cpp
	g++ $(FLAGS) -o db/connection/DBExecutor.o -c db/connection/DBExecutor.cpp
	g++ $(FLAGS) $(EXTRA_INC) -o db/connection/DBConnectionAdapter.o -c db/connection/DBConnectionAdapter.cpp
	g++ $(FLAGS) -o db/table/Column.o -c db/table/Column.cpp
	g++ $(FLAGS) $(EXTRA_INC) -o rest/RESTHandler.o -c rest/RESTHandler.cpp 
	g++ $(FLAGS) -o rest/JsonGenerator.o -c rest/JsonGenerator.cpp
	g++ $(FLAGS) -o rest/JsonToXml.o -c rest/JsonToXml.cpp
	g++ $(FLAGS) $(LDFLAGS) $(CPPFLAGS) $(EXTRA_INC) $(EXTRA_LIB) -o rest/Server \
							db/connection/DBConnectionAdapter.o \
							db/connection/DBExecutor.o \
							db/pool/DBConnectionPool.o \
							db/table/Column.o \
							rest/RESTHandler.o \
							rest/JsonGenerator.o \
							rest/JsonToXml.o \
							rest/Server.cpp \
							utils/Utils.o
clean:
	rm -rf rest/Server */*.o */*/*.o
