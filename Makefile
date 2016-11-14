all: main
	./main 2>log_file.txt

clean:
	rm -f *.exe model/*.exe data/*.txt gnuplot/*.plt graphs/*.png

main:
	g++ -std=gnu++11 -ggdb -mthreads main.cpp -o main

run: main
	./main

test: main
	./main test

test_run: main
	./main test_run
