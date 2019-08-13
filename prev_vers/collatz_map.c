#include <stdio.h>
#include <math.h>


///////////#########################
void main() {
  int nlim=10;
  int a, b, step, escaped;
  long long int n_curr, n_min, n_curr_iter, amax=4, bmax=4, div=2;
  int counter_escaped, counter_ints, sum_of_mins;
  int collatz_map[2*bmax][2*amax];
  float min_fix[nlim], escape_value = 3.14159;
  int n_min_init=999999, max_steps=200;

  /*Collatz mapper to print to external file*/
  for (a = -amax; a < amax; a++) {
    for (b = -bmax; b < bmax; b++) {
      //min fix se inicializa
      printf("parameters: a=%d, b=%d\n", a, b);
      for (n_curr_iter = 1; n_curr_iter < nlim+1; n_curr_iter++) {
        /* code */
        n_curr = n_curr_iter;
        step = 1;
        n_min = n_curr + n_min_init;
        escaped = 0;
        while (n_min != n_curr) {
          printf("step: %d, n_min: %lld, n_curr: %lld\n", step, n_min, n_curr);
          if (n_min > n_curr) {
            n_min = n_curr;
          }
          //n_min = fmin(n_min, n_curr);
          if (n_curr%div==0) {
            if (n_curr == 0) {
              n_min = 0;
              break;
            } else {
              n_curr = n_curr / div;
            }
          } else {
            n_curr = a*n_curr + b;
          }
          step++;
          if (step > max_steps) {
            escaped = 1;
            break;
          }
        }
        if (escaped) {
          min_fix[n_curr_iter-1] = escape_value;
          escaped = 0;
        } else {
          min_fix[n_curr_iter-1] = 1.0*n_min;
        }
      }
      //adding point to map


      printf("printing min_fix\n");
      for (size_t i = 0; i < nlim; i++) {
        printf("%f\t", min_fix[i]);
      }
      printf("\n");
      /**/
      //counting convergence
      counter_escaped=0, counter_ints=0, sum_of_mins=0;
      for (size_t i = 0; i < nlim; i++) {
        if (min_fix[i] == escape_value) {
          counter_escaped++;
        }
        else {
          sum_of_mins += min_fix[i];
          counter_ints++;
        }
      }
      /*
      printf("sum_of_mins=%d\n", sum_of_mins);
      printf("counter_ints=%d\n", counter_ints);
      float test = 1.0*sum_of_mins/counter_ints;
      printf("sum_of_mins/counter_ints=%f\n", test);
      printf("test == min_fix[0]: %d\n", sum_of_mins/counter_ints == min_fix[0]);
      */
      if (counter_escaped>0) {
        if (counter_escaped==nlim) {
          collatz_map[b+bmax][a+amax] = 0;
        } else {
          collatz_map[b+bmax][a+amax] = 1;
        }
      } else {
        if (1.0*sum_of_mins/counter_ints == min_fix[0]) {
          collatz_map[b+bmax][a+amax] = 3;
        } else {
          collatz_map[b+bmax][a+amax] = 2;
        }
      }
      //
    }
  }
  /**/
  for (size_t i = 0; i < 2*bmax; i++) {
    for (size_t j = 0; j < 2*amax; j++) {
      printf("%lld\t", collatz_map[i][j]);
    }
    printf("\n");
  }
}
