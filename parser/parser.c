#include <stdio.h>
#include <string.h>

#include "parser.h"
#include "sgrep_data.h"

int parse(int arguments, char **args, sgrep_data *data) {
	int i;
	int size;
	
	if (arguments < 1 || args == NULL)
	{
		return PARSE_BAD_INDATA;
	}

	/*   arguments: 3
	   args: ----> [1] [2] [3]
	               |  |  |
	               |  |  + "fil.txt"
	               |  + "hejsan"
	               + "-i"
	*/

	/* Default values */
	data->case_sensitive = 1; /* set case INsensitive as default */
	data->mode 			 = 0;
	data->matches		 = 0;
	data->in             = stdin;
	data->reg_exp		 = NULL;

	size = sizeof(args) / sizeof(char *);

	for (i = 0; i < arguments; i++) {
		if (i == size && data->reg_exp != NULL) {
			return PARSE_MISSING_FILE;
		}

		if (strcmp("-i", args[i]) == 0) {
		 	data->case_sensitive = 0; /* set case insensitive */
		} else if (strcmp("-c", args[i]) == 0) {
			data->mode = 1;
		} else if (data->reg_exp == NULL) {
			data->reg_exp = args[i];
		} else {
			data->in = fopen(args[i], "r");
			if (data->in == NULL) {
				return PARSE_MISSING_FILE;
			}
		}
	}

	/*
	The function shall NOT print anything. Really NO printing. 

	The function shall NOT do the searching of string in string (matching). 

	The function shall parse the command line and fiddle with the
	sgrep_data struct passed as an argument (data)

	*/

	return PARSE_OK;
}


