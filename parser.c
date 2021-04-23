/**
*
* @file parser.c
* @brief State parsing
*
*/


/* OFP headers */
#include "ofp.h"
#include "mem.h"
#include "state.h"
#include "error.h"

/* C headers */
#include <string.h>


#define PRTY_ABS_IDX(i,t,p) ((p) == OFP_ARG_PRTY_FIRST) ? (i) : ((t) - 1 - (i))
		/*
		* i (index)    - ofp_uint
		* t (top)      - ofp_uint
		* p (priority) - ofp_argument_priority
		*/


/*
 * Initialize state lists for parsing
 */
static void init_lists (ofp_state *S)
{
	for(int argi = 0; argi < S->argc; ++argi)
	{
		char *arg = S->argv[argi];
		if(arg[0] == S->p)
		{
			/* push to UUIAL */
			S->uuiac++;
			ofp_memory_array_push(S->nal, S->nalt, NULL);
			ofp_memory_array_push(S->uuial, S->uuialt, arg + 1);
		}
		else
		{
			/* push to NAL */
			S->nac++;
			ofp_memory_array_push(S->uuial, S->uuialt, NULL);
			ofp_memory_array_push(S->nal, S->nalt, arg);
		}
	}
}


/*
 * Check for argument errors
 */
static void arg_check (ofp_state *S, ofp_argument *arg)
{
	/* argument not included but required */
	if(!arg->i && arg->r)
	{
		ofp_argument_error_push(S, arg, OFP_ERR_ARG_REQ);
	}
}


/*
 * Handle argument error
 */
static void arg_handleerr (ofp_argument *arg, ofp_errorcode ec)
{
	arg->ef(arg, ec);
}


/*
 * "Pass" argument errors
 */
static void pass_argerrs (ofp_state *S)
{
	for(int i = 0; i < S->errtop; ++i)
	{
		ofp_error *e = S->err + i;
		arg_handleerr(e->arg, e->ec);
	}
}


/**
 * Parse the OFP state.
 *
 * @param S - OFP state
 */
void ofp_parser_parse (ofp_state *S)
{
	init_lists(S);

	/*
	 * Iterate through user-defined arguments
	 */
	for(int ali = 0; ali < S->uuialt; ++ali)
	{
		ofp_argument *a = S->udal + ali;

		/* determine the parsing priority */
		ofp_argument_priority prty = a->prty;
		if(prty == OFP_ARG_PRTY_INHERIT)
			prty = S->prty;

		/*
		 * Iterate through user-inputed arguments
		 */
		for(int i = 0; i < S->argc; ++i)
		{
			int argi = PRTY_ABS_IDX(i, S->argc, prty);
			char *arg = S->argv[argi];

			/*
			 * Contains the right prefix,
			 * qualificates as an argument
			 */
			if(arg[0] == S->p)
			{
				int argl = strlen(arg + 1);

				/*
				 * User-inputed argument
				 * contains the user-defined one
				 */
				if(argl >= a->idlen &&
				   strncmp(arg + 1, a->id, a->idlen) == 0)
				{
					/*
					 * Argument has already been
					 * processed, update the UL
					 */
					if(a->i)
						goto exists;
					a->i = 1;

					/*
					 * argl == a->idlen:
					 *					> flag
					 *					> DA option
					 *                  ! no value
					 * argl != a->idlen:
					 *					> SA option
					 *                  ? unknown
					 */
					if(argl == a->idlen)
					{
						if(a->t == OFP_ARG_TYPE_FLAG)
						{
							/* flag */
							a->v.f = 1;
						}
						else if(a->t == OFP_ARG_TYPE_DUIA_OPTION)
						{
							/* double-UIA option */
							if(argi + 1 < S->argc)
							{
								a->v.o = S->argv[argi + 1];
								S->uuial[argi + 1] = NULL;
								S->nal[argi + 1] = NULL;
							}
							else ofp_argument_error_push(S, a, OFP_ERR_ARG_NOVAL);
						}
						else ofp_argument_error_push(S, a, OFP_ERR_ARG_NOVAL);
					}
					else
					{
						if(a->t == OFP_ARG_TYPE_SUIA_OPTION)
						{
							/* single-UIA option */
							a->v.o = arg + 1 + a->idlen;
						}
						else
						{
							/* argument unknown */
							a->i = 0;
							continue;
						}
					}
				exists:
					/*
					 * Argument is known,
					 * update the UUIAL
					 */
					S->uuial[argi] = NULL;
				}
			}
		}

		arg_check(S, a);
	}

	pass_argerrs(S);
}
