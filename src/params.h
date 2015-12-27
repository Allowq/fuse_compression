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

#define s_inbuf_size 4096
#define s_outbuf_size 16382

typedef struct MINIZ_STATE_STRUCT {
	int bb_compress_type;
	int bb_compress_level;
	size_t be_offset;

	int flate_init;
	int bb_write_final_block;
	unsigned char s_inbuf[s_inbuf_size];	// нам приходят блоки максимум по 4 кбайта (задано в системе)
	unsigned char s_outbuf[s_outbuf_size];	// попробуем собирать буфер более 4 кбайт
	void *stream_struct;
} MINIZ_STATE;

typedef struct bb_state {
    FILE *logfile;
    char *rootdir;
	char *mount_dir;
	MINIZ_STATE compress_state;
} bb_state;

// be_compress == 1 if file is compressed
// be_compress == 0 if file not compresses

// be_execute == 1 if compression algorithm is executed
// be_execute == 0 if compression algorithm not executed

#define BB_DATA ((struct bb_state *) fuse_get_context()->private_data)

#endif
