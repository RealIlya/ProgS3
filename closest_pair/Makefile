CPP_FILES = closest_pair.cpp point.cpp

all: test

clean:
	rm -f *.o

test: clean
	g++ main.cpp closest_pair_test.cpp point_test.cpp $(CPP_FILES) -c
	g++ *.o -o test.out

time:	clean
	g++ timetest.cpp $(CPP_FILES) -O3 -c
	g++ *.o -O3 -o time.out
	./time.out > time.txt