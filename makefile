TARGET=Main
INDIR = HBsolver
exe : Main.out
	./Main.out
Main.out : Main.o HBsolver.o progress.o
	g++  Main.o HBsolver.o progress.o -o Main.out
Main.o :Main.cpp
	g++ -c  Main.cpp -I . -o Main.o
HBsolver.o : HBsolver.hpp HBsolver.cpp
	g++ -c HBsolver.cpp -I . -o HBsolver.o
progress.o : progress.hpp progress.cpp
	g++ -c progress.cpp -I . -o progress.o