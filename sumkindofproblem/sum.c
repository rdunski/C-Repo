// Sum Kind of Problem

// Written by: Robert Dunski
// Date: 03/25/2019

// Kattis Problem Description: https://open.kattis.com/problems/sumkindofproblem

// This program solves the Sum Kind of Problem provided by Kattis using direct
// mathematics rather than looping or recursion. The program first finds the sum
// of all natural numbers from 1 to N (positive), then the sum of the first N
// odd numbers (if N is 3, then the sum = 1+3+5 = 9), and lastly the sum of the
// first N even numbers (if N is 3, then the sum = 2+4+6 = 12). There is also
// built-in testing functionality for the exceptionally paranoid [ :) ]

#include <stdio.h>
#include <assert.h>

int* sumProblem(int* test, long long testnum)
{
  long long sum=0;
  long long n, num, set;

  if (test == NULL && testnum == 0)
  {
    scanf("%lld",&n);         //Read how many lines of input we have
    while(set < n && scanf("%lld%lld", &set,&num) == 2)   //Keep running until \
          //the set has reached n and there are exactly 2 integers in the input
    {
      printf("%lld ", set);
      sum = ((num*num)+num)/2; //Sum of natural numbers from 1 to num,
                              //from https://stackoverflow.com/questions/50566681/sum-of-first-n-numbers-without-loops-or-recursion-or-multiplication;
      printf("%lld ", sum);
      sum = (num*num);          //Sum of first (num) odd natural numbers
                                //derived from above formula using brain-power :)
      printf("%lld ", sum);
      sum = (num*num)+num;    //Sum of first (num) even natural numbers
                              //basically the same as above formula
      printf("%lld\n", sum);
    }
    return NULL;
  }
  else                        //Testing
    {
      test[0] = ((testnum*testnum)+testnum)/2;
      test[1] = testnum*testnum;
      test[2] = (testnum*testnum)+testnum;
      return test;
    }
}

void test()
{
  int test1[3];
  int test2[3];
  int test3[3];

  int* testPtr = sumProblem(test1, 10000); //Test 10000 aka max possible value
  assert(test1[0]==50005000);
  assert(test1[1]==100000000);
  assert(test1[2]==100010000);

  testPtr = sumProblem(test2, 5000); //Test 5000
  assert(test2[0]==12502500);
  assert(test2[1]==25000000);
  assert(test2[2]==25005000);

  testPtr= sumProblem(test3, 1234); //Test 1234
  assert(test3[0]==761995);
  assert(test3[1]==1522756);
  assert(test3[2]==1523990);

  printf("all tests passed\n"); //Huzzah
}

int main(int argc, char* argv[])
{
  if (argc > 1 && strncmp(argv[1], "test", 4) == 0)
  {
    test();
    return 0;
  }

  sumProblem(NULL,0);
}
