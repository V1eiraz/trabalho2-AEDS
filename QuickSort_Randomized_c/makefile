# ──────────────────────────────────────────────
#  Makefile - Randomized Quick Sort
# ──────────────────────────────────────────────

CC      = gcc
FLAGS   = -O2 -Wall
TARGET  = RandomizedQuickSort
SOURCES = mainRandomized.c RandomizedQuickSort.c

all: $(TARGET)

$(TARGET): $(SOURCES)
	$(CC) $(FLAGS) -o $(TARGET) $(SOURCES)

run: $(TARGET)
	./$(TARGET)

clean:
	rm -f $(TARGET) output.dat