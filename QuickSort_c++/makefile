CC      = g++
FLAGS   = -O0 -Wall
TARGET  = QuickSort
SOURCES = main.cpp 

all: $(TARGET)

$(TARGET): $(SOURCES)
	$(CC) $(FLAGS) -o $(TARGET) $(SOURCES)

run: $(TARGET)
	./$(TARGET)

clean:
	rm -f $(TARGET) output.dat