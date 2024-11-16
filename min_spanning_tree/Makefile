all: build

clean:
	rm -f *.o

test: min_spanning_tree
	g++ main.o graph.o min_spanning_tree_test.o min_spanning_tree.o -o Test

min_spanning_tree:
	g++ min_spanning_tree.cpp -c

build: 
	g++ main.cpp graph.cpp min_spanning_tree_test.cpp -c
	
time:	
	g++ timetest.cpp -c -O3
	g++ -O3 timetest.o min_spanning_tree.o graph.o -o time.out
	./time.out > time.txt

time2:	
	g++ timetest.cpp -c -O3
	g++ -O3 timetest.o min_spanning_tree.o graph.o -o time2.out
	./time2.out > time2.txt