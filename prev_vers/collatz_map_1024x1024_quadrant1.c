#include <stdio.h>
#include <math.h>


///////////#########################
void main() {
  int nlim=20, div=7;
  int a, b, step, escaped, n_curr_iter;
  /*First quadrant*/
  int amin=0 , amax=1024, bmin=0 , bmax=1024;
  double n_curr, n_min, sum_of_mins, n_max = 1000000000.;
  int counter_escaped, counter_ints;
  int collatz_map[bmax-bmin][amax-amin];
  double min_fix[nlim], escape_value = 3.14159;
  int calc_steps=100, mini_steps = 100;


  /*Collatz mapper to print to external file*/
  for (a = amin; a < amax; a++) {
    for (b = bmin; b < bmax; b++) {
      //min fix se inicializa
      /*printf("parameters: a=%d, b=%d\n", a, b);*/
      for (n_curr_iter = 1; n_curr_iter < nlim+1; n_curr_iter++) {
        n_curr = n_curr_iter;
        step = 1;
        escaped = 0;
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
        n_min = n_curr;
        while (step < mini_steps){
          /*printf("step: %d, n_min: %f, n_curr: %f\n", step, n_min, n_curr);*/
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
          if (n_curr < -n_max || n_curr > n_max) {
            /*printf("escaped\n");*/
            escaped = 1;
            break;
          }
          if (n_min > n_curr) {
            n_min = n_curr;
          }
        }
        if (escaped) {
          min_fix[n_curr_iter-1] = escape_value;
          escaped = 0;
        } else {
          min_fix[n_curr_iter-1] = n_min;
        }
      }
      //adding point to map

      /*
      printf("printing min_fix\n");
      for (size_t i = 0; i < nlim; i++) {
        printf("%f\t", min_fix[i]);
      }
      printf("\n");
      */
      //counting convergence
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
      /*
      printf("sum_of_mins=%d\n", sum_of_mins);
      printf("counter_ints=%d\n", counter_ints);
      float test = 1.0*sum_of_mins/counter_ints;
      printf("sum_of_mins/counter_ints=%f\n", test);
      printf("test == min_fix[0]: %d\n", sum_of_mins/counter_ints == min_fix[0]);
      */
      if (counter_escaped>0) {
        if (counter_escaped==nlim) {
          collatz_map[b-bmin][a-amin] = 0;
        } else {
          collatz_map[b-bmin][a-amin] = 1;
        }
      } else {
        if (1.0*sum_of_mins/counter_ints == min_fix[0]) {
          collatz_map[b-bmin][a-amin] = 3;
        } else {
          collatz_map[b-bmin][a-amin] = 2;
        }
      }
      //
      /*printf("collatz_map = %d\n", collatz_map[b+bmax][a+amax]);*/
    }
  }
  /**/
  for (size_t i = 0; i < bmax-bmin; i++) {
    for (size_t j = 0; j < amax-amin; j++) {
      printf("%d\t", collatz_map[i][j]);/**/
    }
    printf("\n");
  }
}
