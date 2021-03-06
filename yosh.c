#include "yosh.h"

#define MAX_LINE 512

// print the prompt and read input into @buf
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

    char *t = clock_time();

    if(isatty(0))
        printf(" %s \n[%s]$ ", cwd_out, t);
    fgets(buf, MAX_LINE, stdin);
    buf[strlen(buf)-1] = '\0';
    return buf;
}

// returns a string with the HH:MM:SS time
char *clock_time()
{
    // A+++ naming scheme
    time_t   t = time(NULL);
    char   *tt = ctime(&t);
    char **ttt = _split(tt, " ");
    return ttt[3];
}

// Runs the shell, until exited or interrupted
int main(int argc, char *argv)
{
    char line[MAX_LINE];
    char **args, **cmds, **pcmds;
    int child;
    int status = 0;
    int i, j;

    while(1) {
        if(isatty(0))
            printf("\n[E%03i]", WEXITSTATUS(status));
        prompt_in(line);
        cmds = split_cmds(line);
        i = -1; // classic technique
        while(cmds[++i]) {
            if(!cmds[i])
                break;
            pcmds = split_pipes(cmds[i]);
            if(!pcmds[0])
                break;
            if(!pcmds[1]) {
                args = parse_args(pcmds[0]);
                if(!args[0]) break;
                status = run_cmd(args);
                free(args);
                break;
            }
            else
                status = run_pipes(pcmds);
            free(pcmds);
        }
        free(cmds);
    }
    free(args);
    return 0;
}
