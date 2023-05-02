# Calculator
Simple calculator use GTK+ 

To setup in Linux:

g++ `pkg-config --cflags gtk+-3.0` -o calculator calc.cpp `pkg-config --libs gtk+-3.0` 
./calculator
