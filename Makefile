.PHONY:	all doc clean
all:
	cd cxx && make -f cxx.mk all
	cd java && mvn compiler:compile; mvn war:war
doc:
	cd cxx && make -f cxx.mk doxygen
	
clean:
	cd cxx && make -f cxx.mk clean
	cd java && mvn clean
runcxx:
	cd cxx && make -f cxx.mk run 
runjava:
	cd java && mvn exec:java
runall:
	./runall.sh
