/*
 *  [ p a r s e . h ] 
 *  contains all functions necessary to parse entered commands
 *    split_cmds() splits on semicolons
 *    parse_args() turns a single command into an argument array
 *                 (incl. space removal)
 *
 */
#include <stdio.h>
#include <fcntl.h>
#include <errno.h>
#include <stdlib.h>
#include <unistd.h>
#include <dirent.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <sys/types.h>

/*
 *  _split() 
 *      generalized string splitting function
 *  
 *  splits @line along @delims (using strsep)
 *  mallocs a string array for the result, and returns a pointer to it.
 *      (remember to free!)
 *  supports arbitrary numbers of splitees, by making two passes
 *
 */
char **_split(char *line, char *delims);

/*
 *  split a single command into its arguments (removes spaces)
 *  works like _split(), i.e. remember to free the pointer you get.
 *
 */
char **parse_args(char *line);

// count the number of tokens in a command (helper function)
int count_args(char *line);

// _split(), on semicolons
char **split_cmds(char *cmds);

// _split(), on |
char **split_pipes(char *);

// remove leading empty strings from an argument array
void trim_lead_spaces(char **args);

// remove empty strings from an argument array
void trim_spaces(char **args);
