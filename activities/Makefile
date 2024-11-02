CPP_FILES = activity.cpp activities.cpp

all: test

clean:
	rm -f *.o

test: 
	g++ main.cpp activities_test.cpp $(CPP_FILES) -c -O3
	g++ -O3 main.o activities_test.o activities.o activity.o -o test.out

time:	
	g++ timetest.cpp $(CPP_FILES) -c -O3
	g++ -O3 timetest.o activities.o activity.o -o time.out
	./time.out > time.txt