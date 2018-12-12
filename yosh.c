#include "yosh.h"

#define MAX_LINE 512

char *prompt_in(char *buf)
{
    char *cwd_out; // this is a little stupid
    char cwd[256];
    if(getcwd(cwd, 256) == NULL) { // you died
        char you_died[1024];
        getcwd(you_died, 1024);
        cwd_out = you_died;
    }
    else
        cwd_out = cwd;
    printf("[%s]\n  > ", cwd_out);
    fgets(buf, MAX_LINE, stdin);
    buf[strlen(buf)-1] = '\0';
    return buf;
}

int main(int argc, char *argv)
{
    char line[MAX_LINE];
    char **args, **cmds;
    int child;
    int status = 0;
    int i = 0;

    while(1) {
        printf("\n[E%03i]", WEXITSTATUS(status));
        prompt_in(line);
        cmds = split_cmds(line);
        i = -1;
        while(cmds[++i]) {
                // yeah
            args = parse_args(cmds[i]);
                        // i
            if(!args[0]) continue;
                    // do
            status = ooof(args);
                // spacing
            free(args);
        }

        free(cmds);
    }

    free(args);
    return 0;
}
