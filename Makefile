CC=gcc
OBJS=befunge.o
CFLAGS=-O3 -DPLEASECOMPILE -Wall -fstack-protector-all
#CFLAGS=-xO5 -DPLEASECOMPILE -DSELFTEST

.c.o:
	$(CC) $(CFLAGS) -DSELFTEST -c $<

all: hbef _hbef.so

hbef: $(OBJS) befunge.h
	$(CC) $(CFLAGS) $(OBJS) -o $@
	rm *.o

hbef.py: _hbef.so

_hbef.so: befunge.i befunge.h
	swig -python -shadow befunge.i
	gcc $(CFLAGS) -fPIC -c befunge_wrap.c `python-config --includes`
	gcc $(CFLAGS) -fPIC -c befunge.c -o befunge-PIC.o
	#ld -shared befunge_wrap.o befunge-PIC.o -o _hbef.so
	gcc -Wl,-shared -fPIC befunge_wrap.o befunge-PIC.o -o _hbef.so -nostartfiles
	rm *.o


clean:
	rm *.o hbef.so befunge.py hbef befunge_wrap.*
