#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
    int ret;

    for(int i = 1; i < argc; i++) {
	ret = remove(argv[i]);
	if(ret < 0) {
	    perror("Error: ");
	}
    }

    exit(EXIT_SUCCESS);
}
