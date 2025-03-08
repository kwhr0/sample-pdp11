#include <stdio.h>
#define N 3500
int main(void) {
   short r[N + 1], i, k, b, c;
   long d;
   c = 0;
   for (i = 1; i <= N; i++)
      r[i] = 2000;
   for (k = N; k > 0; k -= 14) {
      d = 0;
      i = k;
      for(;;) {
         d += r[i]*10000L;
         b = i*2 - 1;
         r[i] = d%b;
         d /= b;
         i--;
         if (i == 0) break;
         d *= i;
      }
      printf("%.4d", (int)(c + d/10000));
      c = d%10000;
   }
   putchar('\n');
}
