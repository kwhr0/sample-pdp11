#include <stdio.h>
#include <time.h>

#define W	64
#define H	23

int buf0[W * H / 8];
int buf1[W * H / 8];
int *o;
int *n;
int bitmask[8];

int get(int x, int y) {
	int *p = o + (y << 3 | x >> 3); /* W==64 */
	int m = bitmask[x & 7];
	return (*p & m) != 0;
}

void put(int x, int y, int r) {
	int *p = n + (y << 3 | x >> 3); /* W==64 */
	int m = bitmask[x & 7];
	if (r & 1) *p = *p | m;
	else *p = *p & ~m;
}

unsigned long rndv;
int rand(void) { // xorshift
	rndv ^= rndv << 13;
	rndv ^= rndv >> 17;
	rndv ^= rndv << 5;
	return rndv & 0x7fff;
}

void putnum(int i) {
	putchar('0' + (i >> 9));
	putchar('0' + (i >> 6 & 7));
	putchar('0' + (i >> 3 & 7));
	putchar('0' + (i & 7));
}

void init(void) {
	int x, y;
	int i = 0, m = 1;
	rndv = time(NULL);
	while (i < 8) {
		bitmask[i++] = m;
		m <<= 1;
	}
	o = buf0;
	n = buf0;
	y = 0;
	while (y < H) {
		x = 0;
		while (x < W) {
			put(x, y, rand());
			x++;
		}
		y++;
	}
	n = buf1;
	putchar(27); putchar('['); putchar('2'); putchar('J');
}

int count(int i, int j) {
	int c = 0, u, v, x, y;
	v = j - 1;
	while (v != j + 2) {
		u = i - 1;
		while (u != i + 2) {
			if (u != i | v != j) {
				x = u;
				if (x & 04000) x += W;
				if (x >= W) x -= W;
				y = v;
				if (y & 04000) y += H;
				if (y >= H) y -= H;
				if (get(x, y)) c++;
			}
			u++;
		}
		v++;
	}
	return c;
}

void update(void) {
	int i, j, c, r;
	int *t;
	putchar(27); putchar('['); putchar(';'); putchar('H');
	j = 0;
	while (j < H) {
		i = 0;
		while (i < W) {
			c = count(i, j);
			r = 0;
			if (c == 2) r = get(i, j);
			if (c == 3) r = 1;
			put(i, j, r);
			putchar(r ? '*' : '.');
			i++;
		}
		putchar('\n');
		j++;
	}
	t = o;
	o = n;
	n = t;
}

void main(void) {
	init();
	while (1)
		update();
}

