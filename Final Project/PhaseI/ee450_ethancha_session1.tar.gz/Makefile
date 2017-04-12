#Name: Ethan Chan
#email: ethancha@usc.edu

CC = g++
CFLAGS = -Wall
CSOCK = -lsocket -lnsl -lresolv

all:Captain1 Captain2 Major

Captain1: Captain1.o
	$(CC) $(CFLAGS) -o Captain1 Captain1.o $(CSOCK)

Captain1.o: Captain1.cpp Captain1.h
	$(CC) $(CFLAGS) -c Captain1.cpp $(CSOCK)

Captain2: Captain2.o
	$(CC) $(CFLAGS) -o Captain2 Captain2.o $(CSOCK)

Captain2.o: Captain2.cpp Captain2.h
	$(CC) $(CFLAGS) -c Captain2.cpp $(CSOCK)


Major: Major.o
	$(CC) $(CFLAGS) -o Major Major.o $(CSOCK)

Major.o: Major.cpp Major.h
	$(CC) $(CFLAGS) -c  Major.cpp $(CSOCK)


clean:
	rm -f *.o Major *~
	rm -f *.o Captain *~
