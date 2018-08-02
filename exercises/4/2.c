# include <stdio.h>
# include <ctype.h>

/*
convert string to double, handling sign, decimal, and scientific notation as in 123.45e-6.
*/


double atof_e(char s[]) {
  double val, power;
  int i;
  int exp_val, exp_sign;
  for(i = 0; isspace(s[i]); i++)
    ;
  int sign = (s[i] == '-') ? -1 : 1;
  if(s[i] == '+' || s[i] == '-')
    i++;
  for(val = 0.0; isdigit(s[i]); i++)
    val = val * 10 + (s[i] - '0');
  if(s[i] == '.')
    i++;
  for(power = 1.0; isdigit(s[i]); i++) {
    val = val * 10 + (s[i] - '0');
    power *= 10.0;
  }
  if(s[i] == 'e' || s[i++] == 'E') {
    exp_sign = (s[i++] == '-') ? -1 : 1;
    for(exp_val = 0; isdigit(s[i]); i++) {
      exp_val = exp_val * 10 + (s[i] - '0');
      printf("exp_val: %d\n", exp_val);
    }
    while(exp_val > 0) {
      val *= 10.0;
      exp_val--;
    }
    while(exp_val++ < 0)
      val /= 10.0;
  }
  return sign * val / power;
}


int main(int argc, char* argv[]) {
  /* take string argument from command line*/
  /* int arg_len = sizeof(argv[1])/sizeof(argv[1][0]); */
  double product = atof_e(argv[1]);
  printf("the string %s represents the float %3.1f\n",
         argv[1], product);
}
