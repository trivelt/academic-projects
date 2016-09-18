reset
set term postscript
set output "montercarloDelta.ps"
set title "Zaleznosc bledu wzglednego od liczby losowan"
set xlabel "Liczba losowan"
set ylabel "Blad wzgledny"
set logscale x
set logscale y
plot 'montecarloDelta' using 1:2
