#include "yosh.h"

#define MAX_ARGS 16
#define MAX_LINE 256

/*
 *  _split() 
 *      generalized string splitting function
 *      (do not use directly)
 *  
 *  splits @line along @delims (using strsep)
 *  results are stored in @boff
 *  @bofflen is used only for zeroing out @boff
 *  (i.e. there is no check while strsepping)
 *      BE VERY CAREFUL
 *
 */
char **_split(char **boff, char *line, char *delims, int bofflen)
{
    //char **args = calloc(maxlen, sizeof(char *)); 
    int i = bofflen;
    while(i--) boff[i] = 0;
    i++;
    while(boff[i++] = strsep(&line, delims));
    return boff;
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

int main(int argc, char *argv)
{
    char line[MAX_LINE];
    char **args = calloc(MAX_ARGS, sizeof(char *));

    while(1) {
        prompt_in(line);
        parse_args(args, line);

        int i = 0;
        while(args[i])
            printf("\"%s\"\n", args[i++]);
    }

    free(args);
    return 0;
}
