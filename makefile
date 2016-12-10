all:tresenraya

tresenraya: main.c
	gcc main.c -Wall -ansi -pedandic -o tresenraya
.PHONY: clean

clean:
	rm -f tresenraya