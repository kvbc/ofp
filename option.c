/**
*
* @file option.c
* @brief Option helpers
*
*/


/* OFP headers */
#include "ofp.h"
#include "argument.h"

/* C headers */
#include <stdarg.h>
#include <string.h>


/**
 * Simulates an "enum" behaviour.																\n
 * If argument's identifier matches one of the given entries, return it's corresponding value.	\n
 * Otherwise, if no matching entries were found, return -1.
 *
 * Entry has the following structure
 *
 * |     #1     |         #2        |  #3   |
 * | :--------: | :---------------: | :---: |
 * | identifier | identifier length | value |
 * | char*      | ofp_uint          | int   |
 *
 * ### Example
 * ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~{.c}
 * ofp_option_enumval(argment, 3,    // 3 entries
 *                    "one",   3, 1,
 *                    "two",   3, 2,
 *                    "three", 5, 3);
 * ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 *
 * @param arg   - argument
 * @param count - entry count
 * @param ...   - entries
 */
int ofp_option_enumval (ofp_argument *arg, ofp_uint count, ...)
{
	/*
	 * Argument must be an option
	 */
	if(arg->t == OFP_ARG_TYPE_FLAG)
	{
		return -4;
	}

	/*
	 * Argument must be present
	 */
	if(!arg->i)
	{
		return -3;
	}

	/*
	 * Argument must have a value
	 */
	if(arg->v.o == NULL)
	{
		return -2;
	}

	va_list ent;
	va_start(ent, count);

	/*
	 * Calculating identifier length.
	 * In case of "ofp_option_enumval" getting called multiple times, this will cause efficiency loss.
	 * As there's no need for calling it more than one time and
	 * the function either does or doesn't get called,
	 * this solution is the most efficient.
	 */
	ofp_uint arg_idlen = strlen(arg->v.o);

	for(ofp_uint i = 0; i < count; ++i)
	{
		char *id = va_arg(ent, char*);
		ofp_uint idlen = va_arg(ent, ofp_uint);
		int val = va_arg(ent, int);

		/*
		 * Given identifier matches option's one
		 */
		if(idlen == arg_idlen &&
			strcmp(arg->v.o, id) == 0)
		{
			va_end(ent);
			return val;
		}
	}

	va_end(ent);
	return -1;
}