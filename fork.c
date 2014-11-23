//fork always gives 2^3 childs remember sadde

#include<stdio.h>
#include<sys/types.h>

int main()
{
pid_t pid;

fork();

printf("hi this is a fork");


}

