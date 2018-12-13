/* * * * * * * * * ** * * * * * * * * */
/* jesus christ is this function ugly */
/* * * * * * * * ** * * * * * * * * * */

/* EDIT: we did it */

#include "parse.h"

// deals with all redirection, and runs the command in @args
int ooof(char **args);

// process all redirects in an argument string; alters the file table
//   and does not change it back!
void proc_redirects(char **args);

// change directories, including error checking and ~ (i.e. cd)
void change_dir(char **args);

// handles all piping and redirects to execute a single command with
//   any number of pipes   A T   L E A S T   O N E 
int run_pipes(char **cmds);

// run a command (without redirection), and return its status
int run_cmd(char **args);

// remove @count strings from @args, starting at @from
//  (shift the rest of the array too)
void remove_args(char **args, int from, int count);
