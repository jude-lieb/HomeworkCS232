CC = gcc
CFLAGS = -g
OBJS = add_sub.o mul_dis.o

all: simple_calculations
simple_calculations: simple_calculations.c $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) $< -o $@ -lm
%.o : %.c %.h
	$(CC) $(CFLAGS) -c $< -o $@
clean:
	rm *.o simple_calculations.exe
