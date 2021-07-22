TARGET=Main
INDIR = HBsolver
CXXFLAGS = -Wall
SRCS = Main.cpp HBsolver.cpp progress.cpp
OBJS := $(SRCS:.cpp=.o)
exe :$(TARGET).out
	./$<
$(TARGET): $(OBJS)
	$(CXX) -o $@ $(OBJS)
