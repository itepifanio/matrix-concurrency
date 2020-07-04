PROG = bin/exec
CC = g++ -pthread
CPPFLAGS = -O0 -g -W -Wall -pedantic -std=c++11
OBJS = main.o matrix.o handler.o

$(PROG) : $(OBJS)
	$(CC) $(OBJS) -o $(PROG)
	mv *.o build/

main.o : include/handler.h
	$(CC) $(CPPFLAGS) -c src/main.cpp

matrix.o: include/matrix.h
	$(CC) $(CPPFLAGS) -c src/matrix.cpp

handler.o : include/handler.h include/matrix.h
	$(CC) $(CPPFLAGS) -c src/handler.cpp

clean:
	rm -f build/*.o