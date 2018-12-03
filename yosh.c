#include "yosh.h"

#define MAX_LINE 512

char *prompt_in(char *buf)
{
    printf(">");
    fgets(buf, MAX_LINE, stdin);
    buf[strlen(buf)-1] = '\0';
    return buf;
}

int main(int argc, char *argv)
{
    char line[MAX_LINE];
    char **args, **cmds;
    int child, status;
    int i = 0;

    while(1) {
        prompt_in(line);
        cmds = split_cmds(line);
        i = -1;
        while(cmds[++i]) {

            args = parse_args(cmds[i]);

            if(!args[0]) continue;

            status = ooof(args);

            free(args);
        }

        printf("\nexit status: %i\n", WEXITSTATUS(status));
        free(cmds);
    }

    free(args);
    return 0;
}
