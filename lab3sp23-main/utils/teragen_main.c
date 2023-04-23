#define _OPEN_SOURCE 500

#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include <string.h>
#include <sys/stat.h>
#include <getopt.h>
#include "terarec.h"


#define USAGE \
"usage:\n"                                                                     \
"  teragen [options]\n"                                                        \
"options:\n"                                                                   \
"  -f [filename]       Filename (Default: data.dat)\n"                         \
"  -c [count]    	   Number of elements to generate (Default: 400)\n"\
"  -h                  Show this help message\n"

extern int zerocount;

int main (int argc, char *argv[]){

	char * filename = "data.dat"; 
	long nrecs = 400;
	int c;

	while ((c = getopt (argc, argv, "hf:c:")) != -1){
		switch (c){
			case 'f':
				filename = optarg;
				break;
			case 'c':
				nrecs = atol(optarg);
				break;
			case 'h':
				fprintf(stderr, USAGE);
				exit(EXIT_SUCCESS);
			default:
				fprintf(stderr, USAGE);
				exit(EXIT_FAILURE);
		}
	}

	//Generating Data
	srand(0);
	// TODO need to fix teraGenerate
	terarec_t *data = teraGenerate(nrecs);

	int fd;
	if(0 > (fd = open(filename, O_CREAT | O_RDWR, S_IRUSR | S_IWUSR))){
		fprintf(stderr, "Failed to open file %s.", filename);
		exit(EXIT_FAILURE);
	}

	// TODO need to fix teraWriteToFile
	teraWriteToFile(fd, nrecs, data);

	close(fd);

	return EXIT_SUCCESS;
}
