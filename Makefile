CC = gcc

CFLAGS = -O3 -std=gnu99

SOURCES = myShell.c utilities.c interactive_shell.c batchmode.c built_in.c execute.c

EXE = myshell

#OBJECTS = $(SOURCES:.c=.o)

#$(EXE): $(OBJECTS)
#	$(CC) $(CFLAGS) -o $@ $^
all:
	$(CC) $(CFLAGS) $(SOURCES) -o $(EXE)


#all:
#	$(CC) myShell.c utilities.c interactive_shell.c batchmode.c built_in.c execute.c -o $OBJ

.PHONY: clean

clean:
	@rm -f $(EXE) core 
