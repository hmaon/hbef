/* befunge.i ... by hmaon */
%module hbef
%{
#include "befunge.h"
%}


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
	%addmethods {
		bef_interp(int stack, int w, int h) { return bef_allocinterp(stack, w, h); }
		~bef_interp() { bef_free(self); }
		void push(int n) { push(self, n); }
		int pop() { return pop(self); }
		void do(char c) { bef_do(self, c); }
	}
} bef_interp;


extern int tick, stringtick, noptick, btrace;

extern void strepl (stackt *, int);
extern void stpush (stackt *, int);
extern int stpeek (stackt *);
extern int stpop (stackt *);
extern int stdig (stackt *, int depth);

extern void breplace (bef_interp *, int);
extern void push (bef_interp *, int);
extern int bpeek (bef_interp *);
extern int pop (bef_interp *);

%new extern bef_interp *bef_allocinterp (int stack, int w, int h);
extern void bef_free (bef_interp *);

extern void bef_reset (bef_interp *);

extern void bef_do (bef_interp *, char);
extern int bef_step (bef_interp *);
extern int bef_run (bef_interp *);

extern int strtoicpy (int *, char *);

extern int bef_loadcode (bef_interp *, FILE *);
extern int bef_load93 (bef_interp *, char *name);
%new extern bef_interp *bef_loadh (char *name);
