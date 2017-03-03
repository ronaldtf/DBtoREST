.PHONY:	all doc clean
all:
	cd cxx && make -f cxx.mk all
	cd java && mvn compiler:compile; mvn war:war
doc:
	@mkdir -p doc
	@rm -rf doc/*
	cd cxx && make -f cxx.mk doxygen
	cd java && mvn javadoc:javadoc	
clean:
	cd cxx && make -f cxx.mk clean
	cd java && mvn clean
runcxx:
	cd cxx && make -f cxx.mk run 
runjava:
	cd java && mvn exec:java
runallcxx:
	./runall.sh cxx
runalljava:
	./runall.sh java
