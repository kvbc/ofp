/**
*
* @file mem.c
* @brief Memory helpers
*
*/


/* OFP headers */
#include "ofp.h"
#include "mem.h"
#include "state.h"
#include "error.h"

/* C headers */
#include <stdlib.h>


/*
*
* Memory
*
*/


/**
 * Allocates "size" bytes of uninitialized storage.									\n
 * If allocation succeds, return a pointer to the beggining of allocated memory.	\n
 * On failure throw an fatal "out of memory" error.
 *
 * @param S    - OFP state
 * @param size - number of bytes to allocate
 */
void *ofp_memory_allocate (ofp_state *S, ofp_uint size)
{
	if(size == 0)
		return NULL;
	void *b = malloc(size);
	if(b == NULL)
		ofp_state_error_throw(S, OFP_FERR_MEM_OUT);
	return b;
}


/*
*
* Array
*
*/


/**
 * Check if an array with the given top has hit the limit.	\n
 * If it has, throw an fatal error of code "ferr".
 *
 * @param S     - OFP state
 * @param top   - array's top
 * @param limit - array's limit
 * @param ferr  - error code
 */
void ofp_memory_array_admissible (ofp_state *S, ofp_uint top, ofp_uint limit, ofp_errorcode ferr)
{
	if(top >= limit)
	{
		ofp_state_error_throw(S, ferr);
	}
}