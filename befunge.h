#ifndef ___BEFUNGE_H
#define ___BEFUNGE_H

#include<stdio.h>
#include<stdlib.h>

typedef struct {
	int x, y;
} coord;

typedef struct {
	int *stack;
	int stacksize;
	int sp;
} stackt;

typedef struct{
	int *befungespace;
	int **mem;
	coord size;
	coord ip;
	coord delta;
	stackt *stack;
	stackt *call;
	stackt *CTX;
	int mode; /* bitfield */
	int prevstrchar; /* previoius character in string, for \ escaping */
	int teleport;
} bef_interp;

/* bits for the mode bitfield */
#define mSTRING 0x1	           
#define mTERM 0x2
#define m93 0x4

void strepl (stackt *, int);
void stpush (stackt *, int);
int stpeek (stackt *);
int stpop (stackt *);
int stdig (stackt *, int depth);

void breplace (bef_interp *, int);
void push (bef_interp *, int);
int bpeek (bef_interp *);
int pop (bef_interp *);

bef_interp *bef_allocinterp (int stack, int w, int h);
void bef_free (bef_interp *);

void bef_reset (bef_interp *);

void bef_do (bef_interp *, char);
int bef_step (bef_interp *);
int bef_run (bef_interp *);

int strtoicpy (int *, char *);

int bef_loadcode (bef_interp *, FILE *);
int bef_load93 (bef_interp *, char *name);
bef_interp *bef_loadh (char *name);

extern int tick, noptick, stringtick, btrace;

#endif
