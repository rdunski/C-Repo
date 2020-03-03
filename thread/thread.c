//Contex Switch Program for OS Design.
//Created By: Robert J Dunski
//Some conceptual help from https://github.com/skeeto/pure-linux-threads-demo/blob/master/threads-x86_64.s
//Program SEG Faults on standard execution (work in progress) but runs fine as a gdb process.
//Compiled with: gcc -masm=intel thread.c -o thread

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

#define STACK_SIZE (sizeof(u_int8_t)*64000)

typedef void (*funPtr)(int);

u_int8_t* stack1 = NULL;
u_int8_t* stack2 = NULL;

int count=0;

u_int8_t* stack_create()
{
  u_int8_t *stackPtr = (u_int8_t *)malloc(STACK_SIZE);
  return stackPtr;
}

void startThread(u_int8_t* stack_ptr,funPtr ptr)
{
  asm("mov r15, rsp"); //Save Main/Init stack
  asm("mov rsp, rax"); //Switch to stack_ptr
  ptr(0); //Execute on new stack
}

void shareToMain(int thread)
{
    asm(".intel_syntax noprefix");
    asm(
        "push rbp;\n"
        "push rsi;\n"
        "push rdi;\n"
        "mov r14, rsp;\n"
        "mov rsp, r15;\n"
        "mov r15, r14;\n"
        "pop rsi;\n"
        "pop rdi;\n"
        //Don't need to add "pop rbp" and "ret" because main1/main2 have that at end of function.
      );
}

void shareToMain1(int thread)
{
  //sleep(1);
    asm(".intel_syntax noprefix");
    asm(
      "push rbp;\n"
      "push rbx;\n"
      "push rsi;\n"
      "push rdi;\n"
        "mov rsp, r14;\n"
        "pop rdi;\n"
        "pop rsi;\n"
        "pop rbx;\n"
        //Don't need to add "pop rbp" and "ret" because main1/main2 have that at end of function.
      );
}

void shareToMain2(int thread)
{
  //sleep(1);
    asm(".intel_syntax noprefix");
    asm(
        "push rbp;\n"
        "push rsi;\n"
        "push rdi;\n"
        "mov rsp, r13;\n"
        "pop rdi;\n"
        "pop rsi;\n"
        //Don't need to add "pop rbp" and "ret" because main1/main2 have that at end of function.
      );
}

funPtr main1(int whoami) {
  while (1) {
    printf("%s","Main 1 says Hello\n");
    if (count <= 0){
      count++;
    shareToMain(whoami);
    }
    else {
      asm("mov r14,rsp;"); //Save surrent stack
      shareToMain2(whoami);
    }

  }
}
funPtr main2(int whoami) {
  while (1) {
    printf("%s","Main 2 says Hello\n");
    asm("mov r13,rsp;"); //save current stack
    shareToMain1(whoami);
  }
}

int main(int whoami) {
  stack1=stack_create();
  stack2=stack_create();
  startThread(stack1,main1);
  startThread(stack2,main2);
  return 0;
}
