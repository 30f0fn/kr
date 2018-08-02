# include <stdio.h>
# include <time.h>

clock_t time_taken;


/*
 A version of binary search with only one test inside the loop 
 if x has occurrence in v[0] <= ... <= v[n-1] return its index; else return -1
*/


int binSearchWeiss(int x, int v[], int n) {

  int retval = - 1;

  int sign(int);

  int bounds[3];
  /* lo, <null>, hi; */
  bounds[0] = 0;
  bounds[2] = n-1;
  int lo, mid, hi;
  int c;

  while ((lo = bounds[0]) <= (hi = bounds[2])) {
    mid = (lo + hi) / 2;
    /* int c = sign(x - v[mid]); */
    if (c = sign(x - v[mid])) {
      bounds[1 - c] = mid + c;
      // 1-c is 2 iff c < 0 iff x < v[mid];
    }
    else {
      retval = mid;
      break;      
    }

  }
  /* printf("Time used by SingleTestBinarySearch: %f\n", cpu_time_used); */
  return retval;
}


int binSearchGriffiths(int x, int v[], int n) {
    int low, high, mid;
    
    low = 0;
    high = n - 1;
    mid = (low+high) / 2;
    while ( low <= high && x != v[mid] ) {
        if ( x < v[mid] )
            high = mid - 1;
        else
            low = mid + 1;
        mid = (low+high) / 2;
    }
    if ( x == v[mid] )
        return mid;
    else
        return -1;
}

int sign(int x) {
  return (x > 0) - (0 > x);
}



int binSearchClassic(int x, int v[], int n) {

  
  int retval = -1;

  int lo, mid, hi;
  lo = 0; hi = n - 1;

  while (lo <= hi) {
    mid = (lo + hi) / 2;
    if (x < v[mid])
      hi = mid - 1;
    else if (x > v[mid])
      lo = mid + 1;
    else {
      retval = mid;
      break;
    }
  }
  /* printf("Time used by classicBinarySearch: %f\n", cpu_time_used); */
  return retval;
}

int main(int argc, int* argv[]) {


  for (int t = 0, time_taken = clock(); t < 10000; t++) {
    int a[1000];
    for (int i = 0; i < 1000; i++) 
      a[i] = i;
    binSearchGriffiths(-1, a, 1000);
  }
  time_taken = clock() - time_taken;
  printf("Time used by Griffiths: %d\n", time_taken);


  for (int t = 0, time_taken = clock(); t < 10000; t++) {
    int a[1000];
    for (int i = 0; i < 1000; i++) 
      a[i] = i;
    binSearchWeiss(-1, a, 1000);
  }
  time_taken = clock() - time_taken;
  printf("Time used by Weiss: %d\n", time_taken);

  for (int t = 0, time_taken = clock(); t < 10000; t++) {
    int a[1000];
    for (int i = 0; i < 1000; i++) 
      a[i] = i;
    binSearchClassic(-1, a, 1000);
  }
  time_taken = clock() - time_taken;
  printf("Time used by Classic: %d\n", time_taken);


}
