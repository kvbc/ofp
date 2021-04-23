/**
*
* @file state.c
* @brief OFP State
*
*/


/* OFP headers */
#include "ofp.h"
#include "state.h"
#include "limits.h"

/* C headers */
#include <stdlib.h>


/*
*
* State
*
*/


/**
 * Allocates and initialize a new OFP state.	\n
 * Returns an pointer to it.
 *
 * @param argv    - argument vector
 * @param argc    - argument count
 * @param prty    - default parsing priority
 * @param maxargs - maximum argument count that the state can handle 
 */
ofp_state *ofp_state_new (char **argv, int argc, ofp_argument_priority prty, ofp_uint maxuda)
{
	ofp_state *S = (ofp_state*)malloc(sizeof(*S));

	if(S == NULL)
	{
		return NULL;
	}

	/*
	 * Initialize the pointers with NULL,
	 * so the state doesn't free an "random"
	 * memory adress
	 */
	S->udal = NULL;
	S->uuial = NULL;
	S->nal = NULL;
	S->err = NULL;

	/* Allocate memory for the lists */
	S->udal  = (ofp_argument*)	ofp_memory_allocate(S, sizeof(*S->udal) * maxuda);
	S->uuial = (char**)			ofp_memory_allocate(S, sizeof(*S->uuial) * argc);
	S->nal   = (char**)			ofp_memory_allocate(S, sizeof(*S->nal) * argc);
	S->err   = (ofp_error*)		ofp_memory_allocate(S, sizeof(*S->err) * maxuda);

	/* Initialize counts */
	S->nac   = 0;
	S->uuiac = 0;

	/* Initialize the top indices */
	S->udalt  = 0;
	S->uuialt = 0;
	S->nalt   = 0;
	S->errtop = 0;

	/* Initialize defaults */
	S->prty = prty;
	S->maxuda = maxuda;
	S->argv = argv;
	S->argc = argc;
	S->p = OFP_PREFIX_DEFAULT;

	return S;
}


/**
 * Free the OFP state.
 *
 * @param S - OFP state
 */
void ofp_state_free (ofp_state *S)
{
	free(S->udal);
	free(S->uuial);
	free(S->nal);
	free(S->err);
	free(S);
}


/*
*
* Error
*
*/


/**
 * Throw an fatal error of code "ec".
 *
 * @param S  - OFP state
 * @param ec - error code
 */
void ofp_state_error_throw (ofp_state *S, ofp_errorcode ec)
{
	S->ferr = ec;
	longjmp(S->ferrbuf, ec);
}
