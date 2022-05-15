# SFML Libs
SFML_DIR=./libs/SFML
LIBDIR=$(SFML_DIR)/lib

LIBS=-lsfml-graphics -lsfml-window -lsfml-system

# Compiler flags
CFLAGS=-I$(SFML_DIR)/include

# First function to run
all: compile clean

# Create the executable file
compile: main.o Sortable.o SortAlgorithms.o SortController.o Utils.o
	g++ -o sorting-visualizer -L$(LIBDIR) $(LIBS) main.o Sortable.o SortAlgorithms.o SortController.o Utils.o

	@echo
	@echo Done! Run ./sort-controller to open

# Compile source files
main.o: main.cpp
	g++ -c main.cpp $(CFLAGS) -o main.o

Sortable.o: Sortable.cpp
	g++ -c Sortable.cpp $(CFLAGS) -o Sortable.o

SortAlgorithms.o: SortAlgorithms.cpp
	g++ -c SortAlgorithms.cpp $(CFLAGS) -o SortAlgorithms.o

SortController.o: SortController.cpp
	g++ -c SortController.cpp $(CFLAGS) -o SortController.o

Utils.o: Utils.cpp
	g++ -c Utils.cpp $(CFLAGS) -o Utils.o

# Clean object files after building
clean:
	@rm *.o