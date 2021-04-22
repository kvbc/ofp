@page text_to_number Text to Number

A little example of the ::ofp_option_enumval function and error handling.

> `Usage: <exe> /txt <one-ten>`

~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~{.c}
/* OFP headers */
#include "ofp.h"
#include "error.h"
#include "state.h"
 
/* C headers */
#include <stdio.h>
#include <stdlib.h>
 
 
/*
 * UDA error handling
 */
void arg_error (ofp_argument *arg, ofp_errorcode ec)
{
    printf("ofp: error for arg \"%s\": ", arg->id);
    switch(ec)
    {
    case OFP_ERR_ARG_REQ:
        printf("argument required");
        break;
    case OFP_ERR_ARG_NOVAL:
        printf("argument requires value");
        break;
    }
    puts("");
}
 
 
/*
 * Main program entry
 */
int main (int argc, char **argv)
{
    /*
     * Allocate a new state with the following properites:
     * default parsing priority : last
     * maximum argument count   : 1
     */
    ofp_state *S = ofp_state_new(argv + 1, argc - 1, OFP_ARG_PRTY_LAST, 1);
    
    /*
     * Allocating the state has failed,
     * handle an fatal "out of memory" error
     */
    if(S == NULL)
    {
        printf("ofp: fatal error: out of memory");
        return EXIT_FAILURE;
    }

    /* UDA "txt" */
    ofp_argument *arg_txt;

    /*
     * In case of an fatal error,
     * output the error code and
     * clean up the application
     */
    ofp_on_ferror(S)
    {
        printf("ofp: fatal error: 0x%02X\n", S->ferr);
        goto clean_up;
    }
 
    /*
     * Register an new argument for the state "S" with the following properties:
     * arg type          : double-argument option
     * parsing priority  : first
     * required          : yes
     * error function    : "arg_error"
     * identifier        : "txt"
     * identifier length : 3
     * description       : none
     */
    arg_txt = ofp_argument_register(S, OFP_ARG_TYPE_DUIA_OPTION, OFP_ARG_PRTY_FIRST, OFP_ARG_REQUIRED, arg_error, "txt", 3, NULL);
    ofp_parser_parse(S);
 
    /*
     * If any error has been
     * encountered, print the usage
     * and clean up the application
     */
    if(ofp_any_error(S))
    {
        printf("usage: %s /txt <one-ten>", *argv);
        goto clean_up;
    }

    /*
     * There are no errors,
     * print the input and
     * return the "enumval" of arg "txt"
     */
    printf("input: %s\n", arg_txt->v.o);
    printf("output: %d\n",
        ofp_option_enumval(arg_txt, 10,
                           "zero",  4, 0,
                           "one",   3, 1,
                           "two",   3, 2,
                           "three", 5, 3,
                           "four",  4, 4,
                           "five",  4, 5,
                           "six",   3, 6,
                           "seven", 5, 7,
                           "eight", 5, 8,
                           "nine",  4, 9,
                           "ten",   3, 10));
 
clean_up:
    ofp_state_free(S);

    return EXIT_SUCCESS;
}
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~