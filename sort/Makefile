all: test

clean:
	rm -f *.o *.gch

test: clean
	g++ main.cpp sort_test.cpp sort.cpp -c
	g++ *.o -o test.out

time: clean
	g++ timetest.cpp sort.cpp -c -O3
	g++ *.o -O3 -o time.out
	./time.out > times.txt