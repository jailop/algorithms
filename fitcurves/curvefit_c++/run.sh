#!/bin/sh

./sampledata -m 0 -d 0.1 -n 100 > data.txt
gnuplot sampledata.gnuplot
