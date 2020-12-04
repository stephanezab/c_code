# provide a makefile with a target called shell_jr that 
# creates the executable shell_jr
CC = gcc
CFLAGS = -ansi -Wall -g -O0 -Wwrite-strings -Wshadow \
-pedantic-errors -fstack-protector-all

PUBTESTS =  shell_jr

.PHONY: all clean backup

all: $(PUBTESTS)

clean:
	rm -f *.o $(PUBTESTS) a.out
 
shell_jr: shell_jr.o
