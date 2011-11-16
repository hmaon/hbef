CC=gcc
OBJS=befunge.o
CFLAGS=-O2 -DPLEASECOMPILE -march=athlon -finline-functions -g -Wall
#CFLAGS=-xO5 -DPLEASECOMPILE -DSELFTEST

.c.o:
	$(CC) $(CFLAGS) -DSELFTEST -c $<

all: hbef hbefc.so

hbef: $(OBJS) befunge.h
	$(CC) $(CFLAGS) $(OBJS) -o $@

hbefc.so: befunge.i befunge.h
	swig -python -shadow befunge.i
	gcc $(CFLAGS) -c befunge.c befunge_wrap.c -I/usr/local/include -I/usr/include/python2.1
	ld -shared *.o -o hbefc.so
	rm *.o


clean:
	rm *.o hbef.so befunge.py hbef befunge_wrap.*
