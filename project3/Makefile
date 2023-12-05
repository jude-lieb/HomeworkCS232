CC = gcc
CFLAGS = -g
OBJS = crawler.o indexPage.o search.o readentries.o

all: webSearch
webSearch: webSearch.c $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) $< -o $@ -g -lm
%.o : %.c %.h
	$(CC) $(CFLAGS) -c $< -o $@ -lm
clean:
	rm *.o webSearch.exe
