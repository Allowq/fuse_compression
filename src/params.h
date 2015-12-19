/*
  This program can be distributed under the terms of the GNU GPLv3.
  See the file COPYING.

  There are a couple of symbols that need to be #defined before
  #including all the headers.
*/

#ifndef _PARAMS_H_
#define _PARAMS_H_

// The FUSE API has been changed a number of times.  So, our code
// needs to define the version of the API that we assume.  As of this
// writing, the most current API version is 26
#define FUSE_USE_VERSION 26

// need this to get pwrite().  I have to use setvbuf() instead of
// setlinebuf() later in consequence.
#define _XOPEN_SOURCE 500

// maintain bbfs state in here
#include <limits.h>
#include <stdio.h>

struct MINIZ_STATE {
	int be_compress;
	int bb_compress_type;
	int bb_compress_level;
	size_t be_offset;
};

struct bb_state {
    FILE *logfile;
    char *rootdir;
	struct MINIZ_STATE compress_state;
};

// be_compress == 1 if file is compressed
// be_compress == 0 if file not compresses

// be_execute == 1 if compression algorithm is executed
// be_execute == 0 if compression algorithm not executed

#define BB_DATA ((struct bb_state *) fuse_get_context()->private_data)

#endif
