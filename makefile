TARGET=Main
INDIR = HBsolver
exe : $(TARGET).out
	./$<
$(TARGET).out : $(TARGET).cpp $(INDIR).hpp  $(INDIR).cpp 
	g++ $< $(INDIR).cpp  -o $@ -I .
