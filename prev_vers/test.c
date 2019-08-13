#include <stdio.h>

void main() {
  int step=0, max_steps=40;
  long long int n=1, a=-4, b=-3, div=2;
  while (step<max_steps) {
    if (n%div==0) {
      if (n==0) {
        break;
      } else {
        n = n/2;
      }
    } else {
      n = a*n + b;
    }
    step++;
    printf("%lld\n", n);
  }
}
