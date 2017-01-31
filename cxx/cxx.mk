FLAGS = -std=c++11 -Wall
EXTRA_INC = -I$(MYSQL_CONNECTOR_HOME)/include 
EXTRA_LIB = -L$(MYSQL_CONNECTOR_HOME)/lib -lmysqlcppconn 
all:
	g++ $(FLAGS) -o utils/Utils.o -c utils/Utils.cpp
	g++ $(FLAGS) $(EXTRA_INC) -o db/DBConnectionPool.o -c db/DBConnectionPool.cpp
	g++ $(FLAGS) $(EXTRA_INC) -o db/DBConnector.o -c db/DBConnector.cpp
	g++ $(FLAGS) $(EXTRA_INC) $(EXTRA_LIB) -o test/test db/DBConnectionPool.o db/DBConnector.o utils/Utils.o test/test.cpp
