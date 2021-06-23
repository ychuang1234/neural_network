TARGET=nn.exe
export TARGET
.PHONY: all clean
all: clean $(TARGET)

$(TARGET): 
	g++ -c  backpropagation.cpp interface.cpp
	g++ -o $@ backpropagation.o interface.o

clean:
	del $(TARGET)