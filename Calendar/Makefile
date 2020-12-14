CC = gcc
CFLAGS = -ansi -Wall -g -O0 -Wwrite-strings -Wshadow \
-pedantic-errors -fstack-protector-all 
PUBTESTS = public01 public02 public03 public04 public05 student_tests

.PHONY: all clean backup

all: $(PUBTESTS)

clean:
	rm -f *.o $(PUBTESTS) a.out
 
$(PUBTESTS): calendar.o my_memory_checker_216.o

public%: public%.o
student_tests: student_tests.o

calendar.o: calendar.h event.h
my_memory_checker_216.o: my_memory_checker_216.h
public%.o: calendar.h event.h my_memory_checker_216.h
student_tests.o: calendar.h event.h my_memory_checker_216.h