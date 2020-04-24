#include <stdio.h>
#include <stdlib.h>
int main(int argc, char *argv[]){
  if(argc == 2)
  {
    int size = (int) argv[1];
    int *array = (int*)malloc(size*1024*1024);
    if (array == NULL) {
        printf("Memory not allocated\n");
        exit(0);
    }
    for (int i = 0; i < size; ++i) {
            printf("%d, ", array[i]);
        }
  }
  else
  {
    printf("Usage: ./memory-user [int-memory-size]\n");
  }
}
