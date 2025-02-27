SLL : libSLL.la
	@echo "SLL built"

libSLL.la : SLL.lo
	libtool --mode=link --tag=CC gcc -g -O -o $@ $+ -rpath /usr/lib

SLL.lo : SLL.c SLL.h
	libtool --mode=compile --tag=CC gcc -g -O -c $<

SLL.o : SLL.c SLL.h
