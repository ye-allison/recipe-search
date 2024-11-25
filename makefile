CC = gcc

# All files that will be compiled
all: q1 q2 

# Make object files
q1: q1.c
	$(CC) -o q1 q1.c -lpthread

q2: q2.c
	$(CC) -o q2 q2.c 

# Clean files at the end
clean:
	rm -f q1 q2 
