#include <stdio.h>

typedef double FLOAT;

int main(void) {
	int i, x, y, x0 = 39, y0 = 12;
	for (y = -y0; y <= y0; y++) {
		FLOAT cb = .083333f * y;
		for (x = -x0; x <= x0; x++) {
			FLOAT ca = .0458f * x, a = ca, b = cb;
			for (i = 0; i <= 15; i++) {
				FLOAT t = a * a - b * b + ca;
				b = 2.f * a * b + cb;
				a = t;
				if ((a * a + b * b) > 4.f) {
					putchar(i < 10 ? '0' + i : 'A' + i - 10);
					break;
				}
			}
			if (i > 15) putchar(' ');
		}
		putchar('\n');
	}
	return 0;
}

