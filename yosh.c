#include "yosh.h"

#define MAX_ARGS 16
#define MAX_CMDS 256
#define MAX_LINE 256

/*
 *  _split() 
 *      generalized string splitting function
 *      (do not use directly)
 *  
 *  splits @line along @delims (using strsep)
 *  results are stored in @args
 *  if @bofflen is exceeded, separation stops.
 *
 */
char **_split(char *line, char *delims, int bofflen)
{
    char **args = calloc(bofflen, sizeof(char *));
    int i = bofflen;
    while(i--) args[i] = 0;
    i++;
    while(args[i++] = strsep(&line, delims)) {
        if(i == bofflen) {
            args[i] = 0;
            break;
        }
    }
    return args;
}

char **split_cmds(char *cmds)
{
    return _split(cmds, ";", MAX_CMDS);
}

char **parse_args(char *line)
{
    return _split(line, " ", MAX_ARGS);
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
    char **args;
    int child, status;

    while(1) {
        prompt_in(line);
        args = parse_args(line);

        // int i = 0;
        // printf("\nArgs:\n");
        // while(i < MAX_ARGS)
        //     printf("[%s], ", args[i++]);
        // printf("\n");
        
        if(!strcmp("exit", args[0])) 
            exit(0);

        if((child = fork()) == 0)
            run_cmd(args);

        waitpid(child, &status, 0);
        printf("\nexit status: %i\n", WEXITSTATUS(status));
        free(args);
    }

    free(args);
    return 0;
}
