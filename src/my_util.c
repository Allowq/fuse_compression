/*
  This program can be distributed under the terms of the GNU GPLv3.
  See the file COPYING.

  There are a couple of symbols that need to be #defined before
  #including all the headers.
*/

#include <stdio.h>
#include <stdlib.h>

#include "my_util.h"
#include "miniz.h"

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

int is_compressed(const char *path) {
	if(ends_with(path, ".compr")) 
	    return 1;
		
	return 0;
}

int is_compressed_with_index(const char *path, int *index) {
	if(ends_with(path, ".compr")) {
		*index = strlen(path) - strlen(".compr");
	    return 1;
	} else 
		*index = -1;
		
	return 0;
}

int compress_block(const char *buf, const size_t size, unsigned char *pCmp, unsigned long *cmp_len, struct MINIZ_STATE *m_state) {
	int cmp_status = 0;
	*cmp_len = compressBound(size);
	uLong src_len = size;
			
	if (pCmp) {
		cmp_status = compress2(pCmp, cmp_len, (const unsigned char *)buf, src_len, m_state->bb_compress_level);
		if (cmp_status == Z_OK) {
			m_state->be_offset += *cmp_len;
			return 1;
		}
	}
		
	return 0;
}


int decompress_block(const char *buf, const size_t size, unsigned char *pUncomp, unsigned long *uncomp_len, struct MINIZ_STATE *m_state) {		
	int cmp_status = 0;
	uLong src_len = size;
			
	if (pUncomp) {
		cmp_status = uncompress(pUncomp, uncomp_len, (const unsigned char *)buf, src_len);
			
		if (cmp_status == Z_OK) {
			m_state->be_offset += *uncomp_len;
			return 1;
		}
	}
	
	return 0;
}