TARGET=Main
exe : $(TARGET).out
	./$<
$(TARGET).out : $(TARGET).cpp
	g++ $< -o $@
