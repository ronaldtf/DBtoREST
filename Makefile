.PHONY:	all doc clean
all:
	cd cxx && make -f cxx.mk all
doc:
	cd cxx && make -f cxx.mk doxygen
	
clean:
	cd cxx && make -f cxx.mk clean

exec:
	cd cxx && make -f cxx.mk run 
runall:
	./runall.sh
