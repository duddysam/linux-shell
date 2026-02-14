CC=gcc
CFLAGS= -I.
DEPS = functions.h

%.o: %.c $(DEPS)
	$(CC) -c $< -o $@ $(CFLAGS)
	
shell: shell.o
	$(CC) shell.o -o shell

clean:
	rm -f shell shell.o
