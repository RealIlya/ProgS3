all: build

clean:
	rm -f *.o

test: tsp
	g++ main.o graph.o tsp_test.o tsp.o -o Test

tsp:
	g++ tsp.cpp -c

build: 
	g++ main.cpp graph.cpp tsp_test.cpp -c
	
time:	
	g++ timetest.cpp -c -O3
	g++ -O3 timetest.o tsp.o graph.o -o time.out
	./time.out > time.txt

time2:	
	g++ timetest.cpp -c -O3
	g++ -O3 timetest.o tsp.o graph.o -o time2.out
	./time2.out > time2.txt