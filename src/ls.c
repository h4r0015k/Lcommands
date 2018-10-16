#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <dirent.h>

int compare(const void *a, const void *b)
{
    return strcmp(((char*)a),((char*)b));
}

void print_dir(char *dir) 
{
    DIR *d = opendir(dir);

    if(d == NULL) {
	perror(dir);
	return;
    }

    struct dirent *p;

    while((p = readdir(d)) != NULL) {
	printf("%s\t",p->d_name);
    }
    printf("\n");
    
    closedir(d);
}

void process_args(int argc, char **argv)
{
    int tmp = 1;
    while(tmp < argc) {
	print_dir(argv[tmp]);
	++tmp;
    }
}

int main(int argc, char *argv[]) 
{
    char buf[50];
    
    if(argc > 1) {
	process_args(argc, argv);
	exit(EXIT_SUCCESS);
    }

    getcwd(buf, 50);
    print_dir(buf);

    exit(EXIT_SUCCESS);
}
