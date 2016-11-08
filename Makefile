all: main
	./main

clean:
	rm -f data/*.txt gnuplot/*.plt graphs/*.png

main:
	g++ -std=gnu++11 main.cpp -o main

run: main
	./main

test: main
	./main test
