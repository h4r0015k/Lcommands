#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>

#define BUFF_SIZE 512

void check_args(int argc)
{
    if(argc < 2) {
	printf("Missing arguments!");
	exit(EXIT_FAILURE);
    }
    else if(argc < 3) {
	printf("Missing destination!");
	exit(EXIT_FAILURE);
    }
}

void copy_file(int sf, int df)
{
    int r;
    char data[BUFF_SIZE];
    while((r = read(sf, data, BUFF_SIZE)) > 0) {
	write(df, data, r);
    }
}

int main(int argc, char *argv[])
{
    check_args(argc);
    
    // Open source file
    int sf = open(argv[1], O_RDONLY);

    if(sf < 0)
	perror("Error");

    // Open destination file
    int df = open(argv[2], O_CREAT | O_EXCL | O_WRONLY, S_IRUSR | S_IWUSR);

    if(errno == EEXIST) {
	char in;
	printf("Destination file exists, replace? [y/n] :");
	scanf("%c", &in);

	switch(in) {
	    case 'y':
		df = open(argv[2], O_CREAT | O_TRUNC | O_WRONLY, S_IRUSR | S_IWUSR);
		break;
	    case 'n':
		close(sf);
		exit(EXIT_SUCCESS);
		break;
	    default:
		exit(EXIT_FAILURE);
		break;
	}
    }
    else if(df < 0){
	close(sf);
	perror("Error");
    }

    copy_file(sf, df);
    close(sf);
    close(df);

    exit(EXIT_SUCCESS);
}
