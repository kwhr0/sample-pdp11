#include <stdio.h>

#define HALF		0
#define VIEW		1
#define DEPTH		12

typedef struct {
	unsigned int l, c, r, t, m;
} rec;

long n;

void output(rec *d) {
	int i, j;
	putchar(27); putchar('['); putchar(';'); putchar('H');
	printf("pattern %ld\n", n);
	for (i = 0; i < DEPTH; i++) {
		for (j = 0; j < DEPTH; j++) {
			putchar(' ');
			putchar(d[i].m & 1 << j ? 'Q' : '*');
		}
		putchar('\n');
	}
}

void srch(void) {
	rec d[DEPTH];
	rec *p = d;
	p->l = p->c = p->r = p->m = 0;
#if HALF
	p->t = (1 << (DEPTH + 1 >> 1)) - 1;
#else
	p->t = (1L << DEPTH) - 1;
#endif
	while (1) {
		if (p->t) {
			p->m = -p->t & p->t;
			p->t &= ~p->m;
			if (p - d < DEPTH - 1) {
				rec *p0 = p++;
				p->l = (p0->l | p0->m) << 1;
				p->c = p0->c | p0->m;
				p->r = (p0->r | p0->m) >> 1;
				p->t = ~(p->l | p->c | p->r) & (1L << DEPTH) - 1;
			}
			else {
#if HALF
				n += 1 + (!(DEPTH & 1) || d->t);
#else
				n++;
#endif
#if VIEW
				output(d);
#endif
			}
		}
		else if (--p < d) return;
	}
}

int main(void) {
#if VIEW
	putchar(27); putchar('['); putchar('2'); putchar('J');
#endif
	srch();
#if !VIEW
	printf("N=%ld\n", n);
#endif
	return 0;
}

