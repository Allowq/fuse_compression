/*
  This program can be distributed under the terms of the GNU GPLv3.
  See the file COPYING.

  There are a couple of symbols that need to be #defined before
  #including all the headers.
*/

#include <stdio.h>
#include <stdlib.h>
#include "my_util.h"

int ends_with(const char* haystack, const char* needle) {
    int hlen;
    int nlen;
    /* find the length of both arguments - 
    if needle is longer than haystack, haystack can't end with needle */
    hlen = strlen(haystack); 
    nlen = strlen(needle);
    if(nlen > hlen) return 0;

    /* see if the end of haystack equals needle */
    return (strcmp(&haystack[hlen-nlen], needle)) == 0;
}

int get_compress_set(const char* root_dir, int *type, int *level) {
	FILE *cmprs_set = NULL;
	char buff[255] = {0}, re_path[255] = {0}, compr_type[255] = {0}, cmpr_value[15] = {0};

	strcpy(re_path, root_dir);
	strcat(re_path, "/.cmprs_set");
    
    cmprs_set = fopen(re_path, "r");
	
    if (cmprs_set == NULL) {
		perror("cannot read file with compression settings");
		return 0;
    } else
		rewind (cmprs_set);

	while ( fgets ( buff, 255, cmprs_set ) != NULL ) 
        // if it contains the data we expect
        if ( sscanf( buff, "%s %s", &compr_type, &cmpr_value ) > 0 ) 
			break;

	*level = atoi(cmpr_value);

	if ( ( strcmp(compr_type, "zlib") == 0 ) && (*level >= 1 && *level <= 9) ) {
		fprintf(stderr, "Compression type: %s\n", compr_type); 
		type = 0;
		return 1;
	}

    return 0;
}

int is_compressed(char *path, int *index) {
	if(ends_with(path, ".compr")) {
		*index = strlen(path) - strlen(".compr");
	    return 1;
	} else 
		*index = -1;
		
	return 0;
}