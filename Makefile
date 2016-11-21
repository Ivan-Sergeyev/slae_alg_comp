all: build
	./main 2>log.txt

build:
	g++ -std=gnu++11 -ggdb model\linear_algebra.cpp main.cpp -o main

clean:
	-rm -f *.exe model/*.exe test/*.exe *log.txt main

clean_results:
	-rm -f .progress*
	-rm -rf temp_data

clean_all: clean clean_results

plot:
	python data_analyze.py

run: build
	./main

test: build
	./main test

test_mu_generator: build
	./main test_mu_generator

test_run: build
	./main test_run

bot:
	python bot_code.py 1>1.txt 2>2.txt &
