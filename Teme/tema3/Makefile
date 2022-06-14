.phony: clean

G = gcc -Wall

OUTPUT_DIR = outputs
OFILES = main.o task1.o task2.o task3.o
HFILES = header.h

all: build

build: obj
	touch blockdag.out
	$(G) $(OFILES) -o blockdag

obj: $(HFILES)
	$(G) -c main.c -g
	$(G) -c task1.c -g
	$(G) -c task2.c -g
	$(G) -c task3.c -g

run: build

all: 
	./blockdag -c2 H

clean:
	rm -f *.o blockdag
	clear