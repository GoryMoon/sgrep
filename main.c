#include <stdio.h>

#include "parser.h"
#include "searcher.h"


int main(int argc, char **argv) {

  sgrep_data sgd;
  int status = 0;

  /* Parser: get user information - store sgd*/
  /* sgrep -i hejsan fil.txt */
  /*   argc: 4
       argv: ----> [0] [1] [2] [3]
                   |  |  |  |
                   |  |  |  + "fil.txt"
                   |  |  + "hejsan"
                   |  + "-i"
                   + "sgrep"
  */
  /*   argc-1: 3
       argv: ----> [1] [2] [3]
                   |  |  |
                   |  |  + "fil.txt"
                   |  + "hejsan"
                   + "-i"
  */
	status = parse(argc-1, ++argv, &sgd);
	if (status != 0) {
		if (status == 1) {
			printf("Bad input\n");
		} else {
			printf("File not found\n");
		}
		return 2;
	}

	/*printf ("Case sensitive: %d\n",
			sgd.case_sensitive);
	*/
	/* Searcher: Call search_file */
	status = search_file(&sgd);
	if (status == 0) {
		if (sgd.mode == 1) {
			printf("%d\n", sgd.matches);
		}
	}

	/*
	* make sure to return according to specification
	*/
	return status;
}
