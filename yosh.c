#include "yosh.h"

#define MAX_ARGS 16
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
char **_split(char **args, char *line, char *delims, int bofflen)
{
    //char **args = calloc(maxlen, sizeof(char *)); 
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

char **parse_args(char **boff, char *line)
{
    _split(boff, line, " ", MAX_ARGS);
}

char *prompt_in(char *buf)
{
    char line[MAX_LINE];
    printf(">");
    fgets(line, MAX_LINE, stdin);
    line[strlen(line)-1] = '\0';
    strcpy(buf, line);
    return buf;
}

void child_content(char **args)
{
    printf("let's execvp\n");
    execvp(args[0], args);
    printf("finished execvp\n");
}

int main(int argc, char *argv)
{
    char line[MAX_LINE];
    char **args = calloc(MAX_ARGS, sizeof(char *));
    int child, status;

    while(1) {
        prompt_in(line);
        parse_args(args, line);

        int i = 0;
        printf("\nArgs:\n");
        while(i < MAX_ARGS)
            printf("[%s], ", args[i++]);
        printf("\n");
        
        if(!strcmp("exit", args[0])) 
            exit(0);

        if((child = fork()) == 0)
            child_content(args);

        waitpid(child, &status, 0);
        printf("\nexit status: %i\n", WEXITSTATUS(status));
    }

    free(args);
    return 0;
}
