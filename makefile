PROG = bin/exec
CC = g++ -pthread
CPPFLAGS = -O0 -g -W -Wall -pedantic -std=c++11
OBJS = main.o matrix.o

$(PROG) : $(OBJS)
	$(CC) $(OBJS) -o $(PROG)
	mv *.o build/

main.o : include/matrix.h
	$(CC) $(CPPFLAGS) -c src/main.cpp

matrix.o: include/matrix.h
	$(CC) $(CPPFLAGS) -c src/matrix.cpp

clean:
	rm -f build/*.o