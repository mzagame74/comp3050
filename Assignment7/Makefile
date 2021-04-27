CC = gcc
CFLAGS = -c -g -Wall -Werror 
OBJS = main.o
DEPS = main.c
EXE = a7

all: $(EXE)

$(EXE): $(OBJS)
	$(CC) -o $(EXE) $(OBJS)

$(OBJS): $(DEPS)
	$(CC) $(CFLAGS) $(DEPS)

clean:
	rm -f $(EXE) $(OBJS)
