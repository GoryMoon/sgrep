#define _GNU_SOURCE

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "searcher.h"

#include "sgrep_data.h"


int search_string(char *indata, sgrep_data* sgd) {
	/* Check if args null */

	if (indata == NULL || sgd == NULL || sgd->reg_exp == NULL) {
		return SEARCHER_BAD_INDATA;
	}

  
	/*Note: You can use the GNU Libc function called strcasestr if you
	want to find a string in a string ignoring case.*/

	if (sgd->case_sensitive==1) {

		if (strstr(indata, sgd->reg_exp )==NULL) {
			return SEARCHER_OK_NO_MATCHES;
		} else {
			return SEARCHER_OK_MATCHES;
		}
	} else {
		if (strcasestr(indata, sgd->reg_exp )==NULL) {
			return SEARCHER_OK_NO_MATCHES;
		} else {
			return SEARCHER_OK_MATCHES;
		}

	}
}


int
search_file(sgrep_data *sgd)  {
	char *line_from_file;
	size_t len = 0;
	ssize_t read;
	int status;
	int returnStatus = SEARCHER_OK_NO_MATCHES;

	if (sgd == NULL || sgd->in == NULL || sgd->reg_exp == NULL) {
		return SEARCHER_BAD_INDATA;
	}

	line_from_file = (char *)malloc(sizeof(char *));
	if (line_from_file == NULL) {
		return SEARCHER_OUT_OF_MEM;
	}


	while ((read = getline(&line_from_file, &len, sgd->in)) != -1) {
		status = search_string(line_from_file, sgd);
		if (status == SEARCHER_OK_MATCHES) {
			if (sgd->mode == 0) {
				printf("%s", line_from_file);
			} else if (sgd->mode == 0) {
				sgd->matches = sgd->matches + 1;
			}
			returnStatus = status;
		}
	}

	return returnStatus;
}
