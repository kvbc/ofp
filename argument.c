/**
*
* @file argument.c
* @brief Argument manipulation
*
*/


/* OFP headers */
#include "mem.h"
#include "state.h"
#include "argument.h"

/* C headers */
#include <string.h>


/**
 * Register a new argument.
 *
 * @param S    - OFP state
 * @param t    - argument type
 * @param prty - parsing priority
 * @param r    - required flag
 * @param ef   - error function
 * @param id   - identifier
 * @param len  - identifier's length
 * @param desc - description
 */
ofp_argument *ofp_argument_register
(
	ofp_state *S,
	ofp_argument_type t,
	ofp_argument_priority prty,
	int r,
	ofp_Cfunction ef,
	char *id,
	ofp_uint len,
	char *desc
)
{
	ofp_memory_array_admissible(S, S->udalt, S->maxuda, OFP_FERR_AL_MAX);
	ofp_argument *arg = S->udal + S->udalt++;

	arg->i = 0;
	arg->r = r;
	arg->t = t;
	arg->ef = ef;
	arg->id = id;
	arg->desc = desc;
	arg->prty = prty;
	arg->idlen = len;
	
	if(t == OFP_ARG_TYPE_FLAG)
		arg->v.f = 0;
	else
		arg->v.o = NULL;
	
	return arg;
}


/*
*
* Error
*
*/


/**
 * Push an error of code "ec" concerning argument "arg" onto the error stack.
 *
 * @param S   - OFP state
 * @param arg - argument
 * @param ec  - error code
 */
void ofp_argument_error_push (ofp_state *S, ofp_argument *arg, ofp_errorcode ec)
{
	ofp_memory_array_push(S->err, S->errtop, ((ofp_error)
	{
		ec,
		arg
	}));
}
