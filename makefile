TARGET=Main
INDIR = HBsolver
CXXFLAGS = - Wall
SRCS = Main.cpp HBsolver.cpp progress.cpp
OBJS := $(SRCS:.cpp=.o)
exe :$(TARGET).out
	./$<
$(TARGET): $(OBJS)
	$(CXX) -o $@ $(OBJS)
Main.out : Main.o HBsolver.o progress.o
	$(CXX)  Main.o HBsolver.o progress.o -o Main.out
Main.o :Main.cpp
	$(CXX) -c  Main.cpp -I . -o Main.o
HBsolver.o : HBsolver.hpp HBsolver.cpp
	$(CXX) -c HBsolver.cpp -I . -o HBsolver.o
progress.o : progress.hpp progress.cpp
	$(CXX) -c progress.cpp -I . -o progress.o
clean:
	$(RM) *.o