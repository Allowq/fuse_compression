/*
  This program can be distributed under the terms of the GNU GPLv3.
  See the file COPYING.

  There are a couple of symbols that need to be #defined before
  #including all the headers.
*/

#ifndef _MY_UTIL_H_
#define _MY_UTIL_H_

int ends_with(const char* haystack, const char* needle);
int is_compressed(char *path, int *index);

#endif
