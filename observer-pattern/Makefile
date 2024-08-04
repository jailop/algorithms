CXXFLAGS = -Wall -g

all: example

main: weathersubject.o weatherobserver.o observer.o subject.o

weatherobserver.o: observer.o

weathersubject.o: subject.o

clean:
	rm -f main
	rm -f *.o
