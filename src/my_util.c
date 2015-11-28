/*
  This program can be distributed under the terms of the GNU GPLv3.
  See the file COPYING.

  There are a couple of symbols that need to be #defined before
  #including all the headers.
*/

#include "my_util.h"

typedef unsigned char uint8;
typedef unsigned short uint16;
typedef unsigned int uint;

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

int is_compressed(char *path, int *index) {
	if(ends_with(path, ".compr")) {
		*index = strlen(path) - strlen(".compr");
	    return 1;
	} else 
		*index = -1;
		
	return 0;
}