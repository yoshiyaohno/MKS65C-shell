#include "parse.h"

/*
 *  _split() 
 *  splits @line along @delims
 *  returns a pointer to a string array with the results
 *  (remember to free!)
 *  supports an arbitrary number of splitees
 *
 */
char **_split(char *line, char *delims)
{
    int i = 0;
    // first pass to find necessary length
    char oof[strlen(line)]; // make a backup, which is annoying
    strcpy(oof, line);
    char *line2 = oof; // oh god oh fuck
    // printf("[split] pre-split0, line2 is %s\n", line2);
    while(strsep(&line2, delims)) ++i; //actualy find the length
    // printf("[split] i is %i\n", i);
    char **args = malloc((i+1) * sizeof(char *));
    args[i] = NULL;
    // printf("[split] pre-split1, line is %s\n", line);
    // now actually fill the array
    i = 0;
    while(args[i++] = strsep(&line, delims));
    // printf("[split] separated <%s>\n\tline is %s\n", args[i-1], line);
    return args;
}

char **split_cmds(char *cmds)
{
    // printf("[split_cmds] ");
    return _split(cmds, ";");
}

char **parse_args(char *line)
{
    // printf("[parse_args] ");
    char **args = _split(line, " ");
    trim_spaces(args);
    return args;
}

void trim_lead_spaces(char **args)
{
    if(!args) return; // null case
    int i = 0;
    int j = 0;
    while(args[i] && !strcmp(args[i], "")) i++;
    // i is now the index of the first non-empty string (or null)
    // now copy over till we hit the end null
    while(args[j++] = args[i++]);
}

void trim_spaces(char **args)
{
    trim_lead_spaces(args); // lol
    char **i = args;
    while(*i)
        if(strcmp(*i, ""))
            i++;
        else // i is on an empty string
            trim_lead_spaces(i);
}
