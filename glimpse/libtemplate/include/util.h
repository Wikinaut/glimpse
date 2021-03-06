/*
 *  util.h - Common utilities for the Essence system
 *
 *  Darren Hardy, hardy@cs.colorado.edu, April 1994
 *
 *  $Id: util.h,v 1.3 2006/02/03 16:56:35 golda Exp $
 *
 *  ----------------------------------------------------------------------
 *  Copyright (c) 1994, 1995.  All rights reserved.
 *  
 *          Mic Bowman of Transarc Corporation.
 *          Peter Danzig of the University of Southern California.
 *          Darren R. Hardy of the University of Colorado at Boulder.
 *          Udi Manber of the University of Arizona.
 *          Michael F. Schwartz of the University of Colorado at Boulder. 
 *  
 *  This copyright notice applies to all code in Harvest other than
 *  subsystems developed elsewhere, which contain other copyright notices
 *  in their source text.
 *  
 *  The Harvest software was developed by the Internet Research Task
 *  Force Research Group on Resource Discovery (IRTF-RD).  The Harvest
 *  software may be used for academic, research, government, and internal
 *  business purposes without charge.  If you wish to sell or distribute
 *  the Harvest software to commercial clients or partners, you must
 *  license the software.  See
 *  http://harvest.cs.colorado.edu/harvest/copyright,licensing.html#licensing.
 *  
 *  The Harvest software is provided ``as is'', without express or
 *  implied warranty, and with no support nor obligation to assist in its
 *  use, correction, modification or enhancement.  We assume no liability
 *  with respect to the infringement of copyrights, trade secrets, or any
 *  patents, and are not responsible for consequential damages.  Proper
 *  use of the Harvest software is entirely the responsibility of the user.
 *  
 *  For those who are using Harvest for non-commercial purposes, you may
 *  make derivative works, subject to the following constraints:
 *  
 *  - You must include the above copyright notice and these accompanying 
 *    paragraphs in all forms of derivative works, and any documentation 
 *    and other materials related to such distribution and use acknowledge 
 *    that the software was developed at the above institutions.
 *  
 *  - You must notify IRTF-RD regarding your distribution of the 
 *    derivative work.
 *  
 *  - You must clearly notify users that your are distributing a modified 
 *    version and not the original Harvest software.
 *  
 *  - Any derivative product is also subject to the restrictions of the 
 *    copyright, including distribution and use limitations.
 */
#ifndef _UTIL_H_
#define _UTIL_H_

#include <stdio.h>
#include "config.h"

/* Buffer structure for buffer management routines */
struct gbuf {			/* Growing and shrinking buffer */
	char *data;		/* Data buffer */
	int length;		/* Current length of data buffer */
	int size;		/* Size allocated in the Data buffer */
	int default_size;	/* Default size of the Data buffer */
};
typedef struct gbuf Buffer;	/* Growing buffer */

#define stradd_buffer(b,s)	add_buffer((b), (s), strlen(s))

#ifndef _PARAMS
#define _PARAMS(ARGS) ARGS
#endif /* _PARAMS */   

/* from buffer.c	Buffer manipulation routines */
Buffer *create_buffer _PARAMS((int));		/* New buffer */
void grow_buffer _PARAMS((Buffer *));		/* Increase buffer size */
void increase_buffer _PARAMS((Buffer *, int));	/* Increase buffer size */
void shrink_buffer _PARAMS((Buffer *));		/* Reduce buffer size */
void add_buffer _PARAMS((Buffer *, char *, int));/* Add data to a buffer */
void free_buffer _PARAMS((Buffer *));		/* Clean up a buffer */

/* from host.c */
char *getfullhostname _PARAMS(());		/* Fully qualified hostname */
char *getmylogin _PARAMS(());			/* getlogin(3) clone */
char *getrealhost _PARAMS((char *));		/* Real DNS hostname */

/* from log.c */
void init_log _PARAMS((FILE *, FILE *));	/* Initialize log routines */
void init_log3 _PARAMS((char *,FILE *,FILE *));	/* Initialize log routines */
void log_errno _PARAMS((char *));		/* Same as perror(3) */
void fatal_errno _PARAMS((char *));		/* Same as perror(3) & exit */
#include <stdarg.h>
void glimpselog _PARAMS((char *, ...));		/* Log a message */
void errorlog _PARAMS((char *, ...));		/* Log an error message */
void fatal _PARAMS((char *, ...));		/* Log error msg and exit */

#ifdef NO_STRDUP
/* from strdup.c */
char *strdup _PARAMS((const char *));		/* Duplicate a string */
#endif

/* from string.c */
void parse_argv _PARAMS((char **, char *));	/* Parse a command string */

/* from system.c */
int do_system _PARAMS((char *));		/* Wrapper for system(3) */
int run_cmd _PARAMS((char *));			/* Simple system(3) */
void do_system_lifetime _PARAMS((char *, int));	/* Limited system(3) */
void close_all_fds _PARAMS((int));		/* Closes all fd's */

/* from xmalloc.c */
void *xmalloc _PARAMS((size_t));		/* Wrapper for malloc(3) */
void *xrealloc _PARAMS((void *, size_t));	/* Wrapper for realloc(3) */
void xfree _PARAMS((void *));			/* Wrapper for free(3) */

/* from harvest.c */
char *harvest_bindir _PARAMS((void));
char *harvest_libdir _PARAMS((void));
char *harvest_topdir _PARAMS((void));
void harvest_add_path _PARAMS((char *));
#define harvest_add_gatherer_path() 	harvest_add_path("gatherer:")
#define harvest_add_broker_path() 	harvest_add_path("broker:")
#define harvest_add_cache_path() 	harvest_add_path("cache:")
#define harvest_add_replicator_path()	harvest_add_path("replicator:")

#endif /* _UTIL_H_ */
