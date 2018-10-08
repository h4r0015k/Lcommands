#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int commands[10] = {0}; // commands[0] : show tabs, commands[1] : line numbers... 

void process_args(char **argv, int argc)
{
    int i;
    for(int i = 1; i < argc; i++) {
	if(strncmp("-", argv[i], 1) == 0 && strlen(argv[i]) > 1) {
	    int j;
	    for(j = 1; argv[i][j] != '\0'; j++) {
		switch(argv[i][j]) {
		    case 'T':
			commands[0] = 1;
			break;
		    case 'n':
			commands[1] = 1;
			break;
		    default:
			printf("%c is an invalid option.\n", argv[i][j]);
			exit(EXIT_FAILURE);
		}
	    }
	}
    }
}

void print_con(char ch, int n, int next, int nch) 
{
    if(commands[0]) {
	if(ch == '\t') {
	    printf("^I");
	    return;
	}
    }
    
    if(commands[1]) {
	if(nch == 0) {
	    printf("   %3d  ",n);
	}
	if(ch == '\n' && next != EOF) {
	    printf("\n    %2d  ",n);
	    return;
	}
    }
    
    printf("%c", ch);
}

void print_fc(char *filename, int *line)
{
    int tmp, curr, next;
    int nch = 0;
    FILE *f;
    f = fopen(filename, "r");

    if(f != NULL) {
	while((tmp = fgetc(f)) != EOF) {
	    curr = ftell(f);
	    if(tmp == '\n') {
		++(*line);
	    }
	    
	    next = fgetc(f);
	    fseek(f, curr, SEEK_SET); // Getting back to the current position after getting the next character;
	    print_con(tmp, *line, next, nch);
	    ++nch;
	}

    } else if(strncmp("-", filename, 1) == 0) {
	if(strlen(filename) == 1) {
	    int str;
	    while(1) {
		str = getchar();
		printf("%c", str);
	    }
	}
    }
    else {
	printf("%s not found", filename);
	exit(EXIT_FAILURE);
    }
}

int main(int argc, char *argv[]) 
{
    if(argc <= 1)
	exit(EXIT_SUCCESS);

    process_args(argv, argc);

    int i, line = 1;
    for(i = 1; i < argc; i++) {
	print_fc(argv[i], &line);
    }
    
    exit(EXIT_SUCCESS);
}
