all: main
	./main 2>log_file.txt

clean:
	rm -f *.exe model/*.exe *log.txt data/*.txt gnuplot/*.plt graphs/*.png main

main:
	g++ -std=gnu++11 -ggdb main.cpp -o main

run: main
	./main

test: main
	./main test

test_run: main
	./main test_run
