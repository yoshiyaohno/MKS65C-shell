#include "yosh.h"

#define MAX_ARGS 16
#define MAX_CMDS 256
#define MAX_LINE 256

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
    return _split(line, " ");
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

char *prompt_in(char *buf)
{
    printf(">");
    fgets(buf, MAX_LINE, stdin);
    buf[strlen(buf)-1] = '\0';
    return buf;
}

void run_cmd(char **args)
{
    execvp(args[0], args);
    // only continues if no error
    perror(args[0]);
    exit(1);
}

int main(int argc, char *argv)
{
    char line[MAX_LINE];
    char **args, **cmds, **jef;
    int child, status;
    int i = 0;

    while(1) {
        prompt_in(line);
        cmds = split_cmds(line);
        i = -1;
        while(cmds[++i]) {
            //printf("[[CMD %i]]: %s\n", i, cmds[i]);
            args = parse_args(cmds[i]);
            //trim_lead_spaces(args);
            trim_spaces(args);
            
            // printf("args:\n");
            // char **oof = args;
            // while(*oof)
            //     printf("[%s]\n", *oof++);
            // printf("done args\n\n");

            if(!args[0]) continue;

            if(!strcmp("exit", args[0])) 
                exit(0);
            if((child = fork()) == 0)
                run_cmd(args);
            waitpid(child, &status, 0);
            free(args);
        }

        printf("\nexit status: %i\n", WEXITSTATUS(status));
        free(cmds);
    }

    free(args);
    return 0;
}
