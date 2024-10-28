CPP_FILES = lcs.cpp

all: test

clean:
	rm -f *.o

test: clean
	g++ main.cpp lcs_test.cpp $(CPP_FILES) -c -O3
	g++ -O3 *.o -o test.out

time:	clean
	g++ timetest.cpp $(CPP_FILES) -c -O3
	g++ -O3 *.o -o time.out
	./time.out > time.txt