#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) 
{
    char extern **environ;

    for(; *environ != NULL ; printf("%s\n", *environ++));

    exit(EXIT_SUCCESS);
}
