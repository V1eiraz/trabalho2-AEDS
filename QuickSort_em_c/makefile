# ──────────────────────────────────────────────
#  Makefile - Quick Sort Mediana de Tres
# ──────────────────────────────────────────────

CC      = gcc
FLAGS   = -O2 -Wall
TARGET  = QuickSort
SOURCES = main.c QuickSort.c

all: $(TARGET)

$(TARGET): $(SOURCES)
	$(CC) $(FLAGS) -o $(TARGET) $(SOURCES)

run: $(TARGET)
	./$(TARGET)

clean:
	rm -f $(TARGET) output.dat