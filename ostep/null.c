#include <stddef.h>
int main()
{
  int integer = 4;
  int* null_ptr = &integer;
  null_ptr = NULL;
  int deref = *null_ptr;

  //This causes a segmentation fault
}
