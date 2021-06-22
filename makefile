TARGET=nn.exe
export TARGET
.PHONY: all clean
all: clean $(TARGET)

$(TARGET): 
	g++ -c  backpropagation.cpp data_loader_instantiated.cpp
	g++ -o $@ backpropagation.o data_loader_instantiated.o

clean:
	del $(TARGET)