#include "yosh.h"

#define MAX_ARGS 16
#define MAX_LINE 256

char **_split( char *line, char *delims, int maxlen)
{
    char **args = calloc(maxlen, sizeof(char *)); 
    int i = 0;
    while(args[i++] = strsep(&line, delims));
    return args;
}

char **parse_args(char *line)
{
    _split(line, " ", MAX_ARGS);
}

int main(int argc, char *argv)
{
    char line[MAX_LINE];
    char **args;

    printf(">");
    fgets(line, MAX_LINE, stdin);
    line[strlen(line)-1] = '\0';
    args = parse_args(line);

    int i = 0;
    while(args[i])
        printf("\"%s\"\n", args[i++]);

    free(args);

    return 0;
}
