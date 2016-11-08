all: main
	./main

clean:
	rm main *.exe model/*.exe

clean_all: clean
	rm data/* gnuplot/* graphs/*

main:
	g++ -std=gnu++11 main.cpp -o main

run: main
	./main

test: main
	./main test
