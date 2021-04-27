CC = gcc
CFLAGS = -c
OBJS = add_floats.o
DEPS = add_floats.c
EXE = add_floats

all : $(EXE)

add_floats : $(OBJS)
	$(CC) $(OBJS) -o $(EXE)

add_floats.o : $(DEPS)
	$(CC) $(CFLAGS) $(DEPS)

clean :
	\rm *.o $(EXE)