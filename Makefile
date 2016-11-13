all: main
	./main

clean:
	rm -f *.exe model/*.exe data/*.txt gnuplot/*.plt graphs/*.png

main:
	g++ -std=gnu++11 -ggdb -mthreads main.cpp -o main

run: main
	./main

test: main
	./main test
