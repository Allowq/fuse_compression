/*
  This program can be distributed under the terms of the GNU GPLv3.
  See the file COPYING.

  There are a couple of symbols that need to be #defined before
  #including all the headers.
*/

#ifndef _MY_UTIL_H_
#define _MY_UTIL_H_

#include "params.h"

int compress_block(const char *buf, const size_t size, unsigned char *pCmp, unsigned long *cmp_len, struct MINIZ_STATE *m_state);
int decompress_block(const char *buf, const size_t size, unsigned char *pUncomp, unsigned long *uncomp_len, struct MINIZ_STATE *m_state);
int ends_with(const char* haystack, const char* needle);
int get_compress_set(const char* root_dir, int *type, int *level);
int is_compressed(const char *path);
int is_compressed_with_index(const char *path, int *index);

#endif
