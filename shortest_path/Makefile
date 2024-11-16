all: build

clean:
	rm -f *.o

test: shortest_path
	g++ main.o graph.o shortest_path_test.o shortest_path.o -o Test

shortest_path:
	g++ shortest_path.cpp -c

build: 
	g++ main.cpp graph.cpp shortest_path_test.cpp -c
	
time:	
	g++ timetest.cpp -c -O3
	g++ -O3 timetest.o shortest_path.o graph.o -o time.out
	./time.out > time.txt