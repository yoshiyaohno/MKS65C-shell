/* * * * * * * * * ** * * * * * * * * */
/* jesus christ is this function ugly */
/* * * * * * * * ** * * * * * * * * * */

#include "parse.h"

// deals with all redirection, and runs the command in @args
int ooof(char **args);

// run a command (without redirection), and return its status
int run_cmd(char **args);

// remove @count strings from @args, starting at @from
//  (shift the rest of the array too)
void remove_args(char **args, int from, int count);
