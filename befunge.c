/* copyright 1999 Greg Velichansky */
/* This work is publically displayed for your personal amusement.
   Use of this work for any commercial or otherwise for-profit purposes without
   permission of the autor is prohibited. Inclusion of this work in any non-GPL 
   projects without the author's permission is prohibited. */
/* this program is guaranteed not to be suitable for any particular purpose */
/* talk to me. gvelicha@wam.umd.edu */

#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include <time.h>

#ifndef PLEASECOMPILE
#error Not in the mood to compile right now.
#endif

#include "befunge.h"


int trace = 0;
int tick = 0, noptick = 0, stringtick = 0;


void strepl (stackt *i, int n) {
	i -> stack [i -> sp] = n;
}

void breplace (bef_interp *i, int n) {
	strepl (i -> stack, n);
}
	
void stpush (stackt *i, int n) {
	static int overflow = 0;
	if (i -> sp < i -> stacksize - 1) {
		i -> sp ++;
	} else {
		if (!overflow) {
			fprintf (stderr, "stack overflow (only reported once)\n");
			overflow = -1;
		}
	}
	i -> stack [i -> sp] = n;
}


void push (bef_interp *i, int n) {
	stpush (i -> stack, n);
}


int stpeek (stackt *i) {
	return (i -> stack) [i -> sp];
}

int bpeek (bef_interp *i) {
	return stpeek (i -> stack);
}

int stpop (stackt *i) {
	register int n;
	n = (i -> stack) [i -> sp];
	if (i -> sp > 0) {
		if (trace) printf ("i -> sp == %d, dec pending.\n", i -> sp);
		i -> sp --;
	}
	return n;
}

int pop (bef_interp *i) {
	return stpop (i -> stack);
}

int stdig (stackt *i, int depth) {
	static int underflow = 0;
	int from;

	from = i -> sp - depth;
	if (from < 0 || from > i -> stacksize - 1) {
		if (!underflow) {
			fprintf (stderr, "stdig() stack underflow (only reported once)");
			underflow = -1;
		}
		return stpeek (i);
	}
	return (i -> stack) [from];
}



void bef_checkpc (bef_interp *i) {
	if (i -> ip .x >= i -> size .x) i -> ip .x = 0;
	if (i -> ip .y >= i -> size .y) i -> ip .y = 0;

	if (i -> ip .x < 0) i -> ip .x = i -> size .x - 1;
	if (i -> ip .y < 0) i -> ip .y = i -> size .y - 1;
}


void bef_walk (bef_interp *i) {
	i -> ip .x += i -> delta .x;
	i -> ip .y += i -> delta .y;

	if (i -> ip .x >= i -> size .x) i -> ip .x = 0;
	if (i -> ip .y >= i -> size .y) i -> ip .y = 0;

	if (i -> ip .x < 0) i -> ip .x = i -> size .x - 1;
	if (i -> ip .y < 0) i -> ip .y = i -> size .y - 1;
}

void bef_do (bef_interp *i, char c) {
	int n, m, o;
	char *tmp;
	char t;
	char numtemp[2] = "0";


	if (isxdigit ((int) c)) {
		numtemp[0] = c;
		o = strtoul (numtemp, NULL, 16);
		push (i, o);
		return;
	}
		
		

	switch (c) {
	case ' ':
		++noptick;
		break;

	case '+':
		n = pop (i);
		m = pop (i);
		push (i, m + n);
		break;

	case '-':
		n = pop (i);
		m = pop (i);
		push (i, m - n);
		break;

	case '*':
		n = pop (i);
		m = pop (i);
		push (i, m * n);
		break;

	case '/':
		n = pop (i);
		m = pop (i);
		push (i, m / n);
		break;

	case '%':
		n = pop (i);
		m = pop (i);
		push (i, m % n);
		break;

	case '!':
		if (pop (i)) {
			push (i, 0);
		} else  push (i, 1);
		break;

	case '`':
		n = pop (i);
		m = pop (i);
		if (m > n) {
			push (i, 1);
		} else  push (i, 0);
		break;

	case '>':
		i -> delta .x = 1;
		i -> delta .y = 0;
		break;

	case '<':
		i -> delta .x = -1;
		i -> delta .y = 0;
		break;

	case '^':
		i -> delta .x = 0;
		i -> delta .y = -1;
		break;

	case 'v':
		i -> delta .x = 0;
		i -> delta .y = 1;
		break;

	case '?':
		n = random () % 4;
		tmp = "<>^v";
		t = tmp[n];
		bef_do (i, t); 
		break;

	case '_':
		if (pop (i)) {
			i -> delta .x = -1;
		} else  i -> delta .x = 1;
		i -> delta .y = 0;
		break;

	case '|':
		if (pop (i)) {
			i -> delta .y = -1;
		} else  i -> delta .y = 1;
		i -> delta .x = 0;
		break;

	case '"':
		i -> mode = i -> mode ^ mSTRING;
		if (trace) puts ("mode change mSTRING");
		break;

	case ':':
		if (!trace ) {
			push (i, bpeek (i));
		} else {
			o = bpeek (i);
			printf ("dup: %c  (%d)\n", o, o);
			push (i, o);
		}
		break;

	case '\\':
		n = pop (i);
		m = pop (i);
		push (i, n);
		push (i, m);
		break;

	case '$':
		m = pop (i);
		break;

	case '.':
		printf ("%d ", pop (i));
		fflush (stdout);
		break;

	case ',':
		o = pop (i);
		o = o ? o : ' ';
		printf ("%c", o);
		/*fflush (stdout);*/
		break;

	case '#':
		bef_walk (i);
		break;

	case 'g':
		n = pop (i); /* y */
		m = pop (i); /* x */
		if (n < 0 || n >= i -> size .y || m < 0 || m >= i -> size .x) {
			printf ("%d, %d out of bounds at %d, %d\n", m, n, i -> ip .x, i -> ip .y);
			o = 0;
		} else  o = i -> mem [n][m];
		push (i, o);
		break;

	case 'p':
		n = pop (i);
		m = pop (i);
		o = pop (i);
		if (n < 0 || n >= i -> size .y || m < 0 || m >= i -> size .x) {
			printf ("%d, %d out of bounds at %d, %d\n", m, n, i -> ip .x, i -> ip .y);
		} else  i -> mem[n][m] = o;
		break;

	case '&':
		/*scanf ("%i%*1[\n]", &o);*/
		scanf ("%i", &o);
		push (i, o);
		break;

	case '~':
		/*fflush (stdin);*/
		o = getchar ();
		if (o == EOF) puts ("EOF on getchar()");
		push (i, o);
		break;

	case '@':
		i -> mode |= mTERM;
		break;

#ifndef STRICTBEF93
	
	case 'j':
		n = pop (i);
		m = pop (i);
		if (trace) printf ("from (%d,%d) to (%d,%d)\n", i -> ip.x, i -> ip.y, m, n);
		i -> ip .x = m;
		i -> ip .y = n;
		bef_checkpc (i);
		i -> teleport = -1;
		break;

	case 'J':
		n = pop (i);
		m = pop (i);
		i -> ip .x = m;	
		i -> ip .y = n;
		bef_checkpc (i);
		n = pop (i);
		m = pop (i);
		i -> delta .x = m;
		i -> delta .y = n;
		i -> teleport = -1;
		break;

	case '[':
		o = i -> delta .x * (-1);
		i -> delta .x = i -> delta .y;	
		i -> delta .y = o;
		break;

	case ']':
		o = i -> delta .y * (-1);
		i -> delta .y = i -> delta .x;
		i -> delta .x = o;
		break;

	case '{':
		o = pop (i) - 1;
		push (i, o);
		if (o < 0) bef_do (i, '[');
		break;

	case '}':
		o = pop (i) - 1;
		push (i, o);
		if (o < 0) bef_do (i, ']');
		break;

	case 'o':
		o = pop (i) - 1;
		push (i, o);
		if (o < 0) bef_do (i, '#');
		break;

	case 's':
		n = pop (i);
		m = pop (i);
		if (trace) printf ("from (%d,%d) to (%d,%d)\n", i -> ip.x, i -> ip.y, m, n);
		stpush (i -> call, i -> delta .x);
		stpush (i -> call, i -> delta .y);
		stpush (i -> call, i -> ip .x);
		stpush (i -> call, i -> ip .y);
		i -> ip .x = m;
		i -> ip .y = n;
		bef_checkpc (i);
		i -> teleport = -1;
		break;

	case 'S':
		n = pop (i);
		m = pop (i);
		if (trace) printf ("from (%d,%d) to (%d,%d)\n", i -> ip.x, i -> ip.y, m, n);
		stpush (i -> call, i -> delta .x);
		stpush (i -> call, i -> delta .y);
		stpush (i -> call, i -> ip .x);
		stpush (i -> call, i -> ip .y);
		i -> ip .x = m + stdig (i -> CTX, 1);
		i -> ip .y = n + stpeek (i -> CTX);
		bef_checkpc (i);
		i -> teleport = -1;
		break;

	case 'r':
		n = stpop (i -> call);
		m = stpop (i -> call);
		if (trace) printf ("from (%d,%d) to (%d,%d)\n", i -> ip.x, i -> ip.y, m, n);
		i -> ip .x = m;
		i -> ip .y = n;
		i -> delta .y = stpop (i -> call);
		i -> delta .x = stpop (i -> call);
		bef_checkpc (i);
		if (!(i -> delta .y) && !(i -> delta .x)) {
			fprintf (stderr, "Damn! PC frozen by 'r'.\n");
			exit (99);
		}
		/* i -> teleport = -1; ACK! NO! BAD Cut&Paste! :) */
		break;

	case 'x':
		stpush (i -> CTX, i -> ip .x);
		stpush (i -> CTX, i -> ip .y);
		break;

	case 'X':
		stpop (i -> CTX);
		stpop (i -> CTX);
		break;

	case ';':
		pop (i);
		break;

		
#endif



	default:
		printf ("unknown opcode %c (%d) at %d, %d\n", c, c, i -> ip .x, i -> ip .y);
	}
}

stackt *alloc_stackt (int stacksize) {
	stackt *i;

	i = malloc (sizeof (stackt));

	if (i == NULL) return NULL;

	i -> stack = malloc (stacksize * sizeof (int));
	if (i -> stack == NULL) {
		free (i);
		return NULL;
	}

	i -> stacksize = stacksize;
	i -> sp = 0;
	strepl (i, 0);

	return i;
}


bef_interp *bef_allocinterp (int stack, int w, int h) {
	bef_interp *i;
	int n;

	srandom (time (NULL));

	i = malloc (sizeof (bef_interp));

	if (i == NULL) return NULL;

	if ((i -> stack = alloc_stackt (stack)) == NULL) return NULL; /* MEM LEAK */
	if ((i -> CTX = alloc_stackt (stack)) == NULL) return NULL; /* MEM LEAK */
	if ((i -> call = alloc_stackt (stack)) == NULL) return NULL; /* MEM LEAK */

	i -> befungespace = malloc (w * h * sizeof (int));
	if (i -> befungespace == NULL) {
		free (i -> stack);
		free (i);
		return NULL;
	}

	for (n = 0; n < w * h; ++n) {
		i -> befungespace[n] = ' ';
	}

	i -> mem = malloc (h * sizeof (int *));
	if (i == NULL) {
		free (i -> stack);
		free (i -> befungespace);
		free (i);
		return NULL;
	}

	for (n = 0; n < h; ++n) {
		i -> mem[n] = i -> befungespace + (n * w);
	}

	i -> size.x = w;
	i -> size.y = h;

	i -> ip.x = 0;
	i -> ip.y = 0;

	i -> delta.x = 1;
	i -> delta.y = 0;

	i -> mode = 0;

	return i;
}

int bef_step (bef_interp *i) {
	int c;

	/* get current instruction */
	c = i -> mem[i -> ip .y][i -> ip .x];

	if (trace) {	
		printf (".trace. op: %c (%d)  at %d,%d   mode %d\n", c, c, i -> ip .x, i -> ip .y, i -> mode);
	}
	
	if (i -> mode & mSTRING && (c != '"' || i -> prevstrchar == '\\')) {
		++stringtick;
		if (i -> prevstrchar == '\\') {
			push (i, c);
			i -> prevstrchar = ' ';
		} else {
			i -> prevstrchar = c;
			if (c == '\\') {
				i -> prevstrchar = c;
			} else {
				push (i, c);
			}
		}
	} else { /* exec */
		bef_do (i, c);
	}

	if (i -> mode & mTERM) {
		if (trace) puts ("mTERM");
		return 1;
	}

	if (! i -> teleport) {
		bef_walk (i);
	} else  i -> teleport = 0;

	return 0;
}


int bef_run (bef_interp *i) {
	int n;

	while (!(n = bef_step (i))) ++tick;

	return n;
}

void bef_free (bef_interp *i) {
	if (i == NULL) return;
	free (i -> stack -> stack);
	free (i -> stack);
	free (i -> call -> stack);
	free (i -> call);
	free (i -> CTX -> stack);
	free (i -> CTX);
	free (i -> befungespace);
	free (i -> mem);
	free (i);
}


int strtoicpy (int *n, char *c) {
	int i;

	i = 0;

	while (c[i] != 0) {
		n[i] = c[i];
		i++;
	}
	return i;
}


int bef_loadcode (bef_interp *i, FILE *f) {
	int x, y;
	int c = 0;

	for (y = 0; y < i -> size .y; ++y) {
		for (x = 0; x < i -> size .x; ++x) {
			c = fgetc (f);
			if (trace) printf ("%c", c);
			if (c == EOF) return y;
			if (c == '\n') break;
			i -> mem [y][x] = c;
		}
		if (c != '\n') {
			printf ("line extends past edge of charted space. y == %d\n", y);
		}
	}
	return y;
}
			
int bef_load93 (bef_interp *i, char *name) {
	FILE *f;
	char line[90];
	int n, m;
	int y;

	y = 0;

	if (i == NULL) return -1;
	if (i -> mem == NULL) return -1;

	f = fopen (name, "r");
	if (f == NULL) {
		puts ("could not open file.");
		return -1;
	}
	do {
		n = fscanf (f, "%80[^\n]", line);
		m = fscanf (f, "%2[\n]", &(line[85]));
		if (n != 0 && n != EOF) {
			if (trace) puts (line);
			strtoicpy ((i -> mem)[y], line);
		} else {
			fclose (f);
			return !y;
		}
		++y;
	} while (1);
}

/* load hbef formatted befunge source into new interpreter */
bef_interp *bef_loadh (char *name) {
	FILE *f;
	int n, m = 1024;
	int w = 80, h = 25;
	bef_interp *i = NULL;

	char command[90];

	*command = 0;

	f = fopen (name, "r");
	if (f == NULL) {
		perror ("could not open file");
		return NULL;
	}

	while ((n = fscanf (f, "%80s", command)) != EOF) {
		if (n) {
			if (trace) printf ("command: %s\n", command);
			if (!strcmp (command, "wid")) {
				fscanf (f, "%d", &w);
				if (trace) printf ("w == %d\n", w);
			} else if (!strcmp (command, "hei")) {
				fscanf (f, "%d", &h);
				if (trace) printf ("h == %d\n", h);
			} else if (!strcmp (command, "stack")) {
				fscanf (f, "%d", &m);
				if (trace) printf ("stack == %d\n", m);
			} else if (!strcmp (command, "hb")) {
				i = bef_allocinterp (m, w, h);
				do { n = fgetc (f); } while (n != '\n' && n != EOF);
				n = bef_loadcode (i, f);
				if (trace) printf ("bef_loadcode() returned %d\n", n);
				return i;
			}
		}
	}

	printf ("no hb directive encountered... no code in file?\n");
	bef_free (i);
	return NULL;
}





#ifdef SELFTEST

char *sample = "\"!dlrow olleH\",,,,,,,,,,,,@";

int main (int argc, char **argv) {
	bef_interp *i;
	int r;
	int load93 = 0;
	int report = 0;
	char *file = "test.hbf";

	for (r = 1; r < argc; ++r) {
		if (!strcmp (argv[r], "--trace")) {
			trace = -1;
		} else if (!strcmp (argv[r], "--93")) {
			load93 = -1;
		} else if (!strcmp (argv[r], "--report")) {
			report = -1;
		} else {
			file = argv[r];
		}
		
	}
	
	/*printf ("stack test %d %d %d %d\n", pop(i), bpeek(i), pop(i), bpeek(i));*/

	/*bef_do (i, '.');*/

	/* strtoicpy ((i -> mem)[0], sample); */
	if (load93) {
		i = bef_allocinterp (1024, 80, 25);
		if (bef_load93 (i, file)) puts ("error?");
	} else {
		i = bef_loadh (file);
		if (i == NULL) {
			puts ("bef_loadh() returned NULL");
			exit (1);
		}
	}

	/*printf ("%c\n\n", i -> mem[0][4]);*/

	bef_run (i);

	printf ("\nDONE: %d ops. %d string, %d nop, %d other.\n", tick, stringtick, noptick, ((tick - stringtick) - noptick));

	bef_free (i);
	return 0;
}
#endif
