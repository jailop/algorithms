set terminal png
set output "plot.png"
set style circle radius screen 0.01 
plot "data.txt" using 1:2 with lines title "", \
     "data.txt" using 1:3 with points title ""
