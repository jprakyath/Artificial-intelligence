EXECUTABLE = MazeSearch

OUTPUT_FILES = output/*
#output/smallMaze.txt output/mediumMaze.txt output/bigMaze.txt

COMPILER = g++ -std=c++11
COMPILER_OPTS = -c -g

LINKER = g++
LINKER_OPTS = -o $(EXECUTABLE)
#CFLAGS = -DDEBUG_LOGS

OBJS = main.o search.o

#  linking the program.
$(EXECUTABLE) : $(OBJS)
	$(LINKER) $(LINKER_OPTS) $(CFLAGS) $(OBJS)

# Rules for performing the compilation.
search.o : search.h search.cpp
	$(COMPILER) $(COMPILER_OPTS) $(CFLAGS) search.cpp

main.o : main.cpp search.o
	$(COMPILER) $(COMPILER_OPTS) main.cpp

clean:
	-rm *.o $(EXECUTABLE) $(OUTPUT_FILES)


