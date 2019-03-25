#include <stdio.h>

int main(int argc, const char* argv[])
{
  long long sum=0;
  int k, num, set;
  scanf("%lld",&k);
  while(scanf("%lld%lld", &set,&num) == 2)
  {
    sum = ((num*num)+num)/2; //Sum of natural numbers from 1 to num,
                            //from https://stackoverflow.com/questions/50566681/sum-of-first-n-numbers-without-loops-or-recursion-or-multiplication;
    printf("%lld\n", sum);
    sum = (num*num);          //Sum of first (num) odd natural numbers
                              //derived from above formula using brain-power :)
    printf("%lld\n", sum);
    sum = (num*num)+num;    //Sum of first (num) even natural numbers
                            //basically the same as above formula
    printf("%lld\n", sum);
  }
}
