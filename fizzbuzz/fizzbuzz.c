#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

char* returnChar[50];

char* fizzbuzz(int* test)
{
  long long x, y, n;
  if (test != NULL)
  {
    for (int i = 1; i<=test[2]; i++)
    {
      if (i%test[0] == 0 && i%test[1] == 0)
      {
        returnChar[i] = 'G';
      }
      else if (i%test[0] == 0)
      {
        returnChar[i] = 'F';
      }
      else if (i%test[1] == 0)
      {
        returnChar[i] = 'B';
      }
      else
      {
        returnChar[i] = i+'0';
      }
    }
  }
  else{
  while (scanf("%lld%lld%lld", &x, &y, &n) == 3 && test == NULL) {
    for (int i = 1; i<=n; i++)
    {
      if (i%x == 0 && i%y == 0)
        printf("FizzBuzz\n");
      else if (i%x == 0)
        printf("Fizz\n");
      else if (i%y == 0)
        printf("Buzz\n");
      else
        printf("%lld\n", i);
    }
    break;
  }
}
}

int main(int argc, const char* argv[])
{
  if (argc > 1 && argv[1] == "test")
  {
    char returnChar[50];
    int intArray1[] = {2,4,7};
    char* testPtr = fizzbuzz(intArray);
    assert(testPtr[1]=='1');
    assert(returnChar[2]=='F'); // Fizz
    assert(returnChar[3]=='3');
    assert(returnChar[4]=='G'); // 'G' means FizzBuzz
    assert(returnChar[5]=='5');
    assert(returnChar[6]=='F');
    assert(returnChar[7]=='7');

    intArray[0]=3;              // testing 3 5 7
    intArray[1]=5;
    intArray[2]=7;
    fizzbuzz(intArray);
    assert(returnChar[1]=='1');
    assert(returnChar[2]=='2');
    assert(returnChar[3]=='F');
    assert(returnChar[4]=='4');
    assert(returnChar[5]=='B'); //Buzz
    assert(returnChar[6]=='F');
    assert(returnChar[7]=='7');
    printf("all tests passed\n");
    exit(0);
  }
  fizzbuzz(NULL);
}
