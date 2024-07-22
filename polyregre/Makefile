CFLAGS = -Wall -g -ansi -pedantic -O2
LDLIBS = -lm -lcblas -lgsl

all: basicplot.png polyregre

basicplot.png: basicplot.plt data/train.txt
	cat data/train.txt | gnuplot basicplot.plt

data/train.txt:
	make -C gendata
	gendata/gendata --seed 1 --examples 1000 > data/train.txt

data/test.txt:
	make -C gendata
	gendata/gendata --seed 2 --examples 200 > data/test.txt

clean:
	make -C gendata clean
	make -C randperm clean
	rm -f data/*
	rm -f basicplot.png
