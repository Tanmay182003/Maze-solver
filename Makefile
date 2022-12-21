# ***
# *** Do NOT modify this file
# ***

CFLAGS = -std=c99 -g -Wall -Wshadow --pedantic -Wvla -Werror
#TESTFLAGS = -DTEST_SHUFFLE -DTEST_INTERLEAVE -DTEST_DIVIDE
GCC = gcc $(CFLAGS) #$(TESTFLAGS)
EXEC = hw11 
OBJS = list.o path.o maze.o mazehelper.o solver.o hw11.o
VALGRIND = valgrind --tool=memcheck --leak-check=yes --verbose

$(EXEC): $(OBJS) list.h maze.h mazehelper.h path.h solver.h
	$(GCC) $(OBJS) -o $(EXEC) 

test: $(EXEC)
	./$(EXEC) testcases/maze1 output1
	./$(EXEC) testcases/maze2 output2
	./$(EXEC) testcases/maze3 output3

testdif: test
	diff -w output1 expected/expected1
	diff -w output2 expected/expected2
	diff -w output3 expected/expected3

memory: $(EXEC)
	$(VALGRIND) --log-file=log1 ./$(EXEC) testcases/maze1 output1
	$(VALGRIND) --log-file=log2 ./$(EXEC) testcases/maze2 output2
	$(VALGRIND) --log-file=log3 ./$(EXEC) testcases/maze3 output3

%.o : %.c
	$(GCC) -c $< 

clean:
	rm -f path.o maze.o mazehelper.o solver.o hw11.o list.o
	rm -f output*
	rm -f $(EXEC)
	rm -f id? name? log?