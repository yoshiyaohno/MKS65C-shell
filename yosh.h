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

// _split(), on spaces
char **parse_args(char *line);

// _split(), on semicolons
char **split_cmds(char *cmds);

// remove leading empty strings from an argument array
void trim_lead_spaces(char **args);

// remove empty strings from an argument array
void trim_spaces(char **args);

// print prompt and read input into buf
char *prompt_in(char *buf);

// execvp, including error checking
void run_cmd(char **args);
