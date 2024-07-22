CXXFLAGS = -Wall -g -std=c++1z -fpic
LDLIBS = 
OBJ = vector.o vector_io.o matrix.o matrix_io.o block.o

all: linalg_test

linalg_test: linalg_test.cc liblinalg.so
	g++ -Wall -llinalg -lboost_unit_test_framework -o linalg_test linalg_test.cc

liblinalg.so: ${OBJ} linalg.h
	g++ -shared -o liblinalg.so ${OBJ}

install: liblinalg.so linalg.h
	cp liblinalg.so /usr/local/lib
	cp linalg.h /usr/local/include

clean:
	rm -f liblinalg.so
	rm -f linalg_test
	rm -f *.o
