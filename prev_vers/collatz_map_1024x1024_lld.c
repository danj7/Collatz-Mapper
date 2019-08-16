#include <stdio.h>
#include <math.h>


///////////#########################
void main() {
  long long a, b, n_curr, n_min, sum_of_mins, n_min_init=999999, n_max = 1000000000, div=2;
  int step, escaped, n_curr_iter, nlim=20;
  /*All quadrants*/
  int amin=-16 , amax=16, bmin=-8 , bmax=8;
  int counter_escaped, counter_ints;
  double min_fix[nlim], escape_value = 3.14159;
  int calc_steps=200, max_mini_steps = 100;


  /*Collatz mapper to print to external file*/
  for (a = amin; a < amax; a++) {
    for (b = bmin; b < bmax; b++) {
      /**/
      for (n_curr_iter = 1; n_curr_iter < nlim+1; n_curr_iter++) {
        n_curr = n_curr_iter;
        step = 1;
        escaped = 0;
        /*Calculating stage*/
        while (step < calc_steps) {
          if ( fmod(n_curr,div)==0 ){
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
        }
        step = 1;
        n_min = n_curr + n_min_init;
        /*Minimization stage*/
        while (n_min != n_curr){
          if ( fmod(n_curr,div)==0 ) {
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
          if (n_curr < -n_max || n_curr > n_max || step > max_mini_steps) {
            escaped = 1;
            break;
          }
          if (n_min > n_curr) {
            n_min = n_curr;
          }
        }
        /*Adding to the array of smallest fixed points*/
        if (escaped) {
          min_fix[n_curr_iter-1] = escape_value;
          escaped = 0;
        } else {
          min_fix[n_curr_iter-1] = 1.0*n_min;
        }
      }
      /*Finding convergence and adding point to map*/
      counter_escaped=0;
      counter_ints=0;
      sum_of_mins=0;
      for (size_t i = 0; i < nlim; i++) {
        if (min_fix[i] == escape_value) {
          counter_escaped++;
        }
        else {
          sum_of_mins += min_fix[i];
          counter_ints++;
        }
      }
      if (counter_escaped>0) {
        if (counter_escaped==nlim) {
          printf("%d\t", 0);
        } else {
          printf("%d\t", 1);
        }
      } else {
        if (1.0*sum_of_mins/counter_ints == min_fix[0]) {
          printf("%d\t", 3);
        } else {
          printf("%d\t", 2);
        }
      }
    }
    printf("\n");
  }
}
