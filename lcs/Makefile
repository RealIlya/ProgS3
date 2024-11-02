CPP_FILES = lcs.cpp

all: test

clean:
	rm -f *.o

test: 
	g++ main.cpp lcs_test.cpp $(CPP_FILES) -c -O3
	g++ -O3 main.o lcs_test.o lcs.o -o test.out

time:	
	g++ timetest.cpp $(CPP_FILES) -c -O3
	g++ -O3 timetest.o lcs.o -o time.out
	./time.out > time.txt