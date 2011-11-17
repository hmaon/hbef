CC=gcc
OBJS=befunge.o
CFLAGS=-O3 -DPLEASECOMPILE -Wall
#CFLAGS=-xO5 -DPLEASECOMPILE -DSELFTEST

.c.o:
	$(CC) $(CFLAGS) -DSELFTEST -c $<

all: hbef _hbef.so

hbef: $(OBJS) befunge.h
	$(CC) $(CFLAGS) $(OBJS) -o $@

hbef.py: _hbef.so

_hbef.so: befunge.i befunge.h
	swig -python -shadow befunge.i
	gcc $(CFLAGS) -fPIC -c befunge.c befunge_wrap.c -I/usr/local/include `python-config --includes`
	ld -shared *.o -o _hbef.so
	rm *.o


clean:
	rm *.o hbef.so befunge.py hbef befunge_wrap.*
