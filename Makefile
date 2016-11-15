all: main
	./main 2>log.txt

clean:
	-rm -f *.exe model/*.exe *log.txt main

clean_results:
	-rm -f temp_data/*.txt temp_gnuplot/*.plt temp_graphs/*.png

clean_all: clean clean_results

main:
	g++ -std=gnu++11 -ggdb main.cpp -o main

plot:
	python data_analyse.py

run: main
	./main

test: main
	./main test

test_run: main
	./main test_run

bot: 
	python bot_code.py 1>1.txt 2>2.txt &
