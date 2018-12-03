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
    char *line2 = oof; // mmmmmmmmmm
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

// split a string on semicolons, i.e. separate commands
char **split_cmds(char *cmds)
{
    // printf("[split_cmds] ");
    return _split(cmds, ";");
}

// counts the tokens in a string (= single command)
int count_tokens(char *line)
{
    int count = 0;
    while(*line) {
        // oh boy
        switch(*line) {
            case '>' :
                if(*(line+1) == '>') ++line;
                ++count;
                break;
            case '&' :
                if(*(line+1) == '>') {
                    ++line;
                    ++count;
                    if(*(line+1) == '>') ++line;
                }
                break;
            case '2' :
                if(*(line+1) == '>') {
                    ++line;
                    ++count;
                    if(*(line+1) == '>') ++line;
                }
                break;
            case '<' :
                ++count;
                break;
            case ' ' :
                break;
            default :
                if(*(line+1) == ' ' || *(line+1) == '\0')
                    ++count;
        } // end switch
        ++line;
    }
    return count;
}

/*
 *  split a command into its arguments (removes spaces)
 *  works like _split(), i.e. remember to free the pointer you get.
 *
 */
char **parse_args(char *line)
{
    // printf("[parse_args] ");
    // char **args = _split(line, " ");
    // trim_spaces(args);
    char *token = line;
    int i = count_tokens(line);
    // printf("[parse_args] number of tokens: %i\n", i);
    char **args = malloc((i+1)*sizeof(char *));
    args[i] = NULL;
    i = 0; // reusing variables, woo
    char *oof = line; // for the beginning of tokens
    // uh oh here comes the switch statement again
    while(*line) {
        switch(*line) {
            case '>' :
                *line = '\0';
                if(*(line+1) == '>') {
                    args[i++] = ">>";
                    ++line;
                }
                else
                    args[i++] = ">";
                break;
            case '&' :
                if(*(line+1) == '>') {
                    *line = '\0';
                    ++line;
                    if(*(line+1) == '>') {
                        args[i++] = "&>>";
                        ++line;
                    }
                    else
                        args[i++] = "&>";
                }
                break;
            case '2' :
                if(*(line+1) == '>') {
                    *line = '\0';
                    ++line;
                    if(*(line+1) == '>') {
                        args[i++] = "2>>";
                        ++line;
                    }
                    else
                        args[i++] = "2>";
                }
                break;
            case '<' :
                *line = '\0';
                args[i++] = "<";
                break;
            case ' ' :
                *line = '\0';
                oof = line+1;
                break;
            default :
                // end of word?
                if(*(line+1) == ' ' || *(line+1) == '\0')
                    args[i++] = oof;
        } // end switch
        ++line;
    } // end while
    return args;
}

// remove leading empty strings from an argument array
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

// remove all empty strings from an argument array 
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
