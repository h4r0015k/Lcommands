#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

struct commands {
    char show_tabs;
    char show_nline;
    char show_end;
};

void process_args(char **argv, int argc, struct commands *coms)
{
    char *args = "TEn";
    char tmp;

    while((tmp = getopt(argc, argv, args)) != -1) {
	switch(tmp) {
	    case 'T':
		coms->show_tabs = 1;
		break;
	    case 'n':
		coms->show_nline = 1;
		break;
	    case 'E':
		coms->show_end = 1;
		break;
	    default:
		exit(EXIT_FAILURE);
	}
	
    }
    
}

void print_con(char ch, int *line, int next, int nch, struct commands *coms) 
{
    if(coms->show_tabs) {
	if(ch == '\t') {
	    printf("^I");
	    return;
	}
    }
    
    if(coms->show_nline) {
	if(nch == 0) {
	    printf("    %3d  ",*line);
	}
	if(ch == '\n' && next != EOF) {
	    ++(*line);
	    if(!coms->show_end) {
		printf("\n    %3d  ",*line);
		return;
	    }
	    else {
		printf("$\n    %3d  ",*line);
		return;
	    }
	}
    }

    if(coms->show_end) {
	if(ch == '\n') {
	    ++(*line);
	    printf("$\n");
	    return;
	}
    }
    
    printf("%c", ch);
}

void std_in() 
{
    int str;
    while(1) {
	str = getchar();
	printf("%c", str);
    }

}

void print_fc(char *filename, int *line, struct commands *coms)
{
    int tmp, curr, next;
    int nch = 0;
    FILE *f;
    f = fopen(filename, "r");

    if(f != NULL) {
	while((tmp = fgetc(f)) != EOF) {
	    curr = ftell(f);
	    
	    next = fgetc(f);
	    fseek(f, curr, SEEK_SET); // Getting back to the current position after getting the next character;
	    print_con(tmp, line, next, nch, coms);
	    ++nch;
	}

    }
    else if(filename[0] == '-') {
	    if(strlen(filename) == 1) {
		std_in();
	    }
    }
    else {
	printf("File %s not found.\n", filename);
	exit(EXIT_FAILURE);
    }
}

int main(int argc, char *argv[]) 
{
    if(argc <= 1)
	std_in();

    struct commands coms = {0,0};
    process_args(argv, argc, &coms);

    int i, line = 1;
    for(i = 1; i < argc; i++) {
	print_fc(argv[i], &line, &coms);
    }
    
    exit(EXIT_SUCCESS);
}
