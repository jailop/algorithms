set terminal png size 640,480 enhanced font "Sans Serif,10";
set output "basicplot.png";
set xlabel "x";
set ylabel "y";
set title "Polynomial regression";
plot "<cat" title "x ~ y";
