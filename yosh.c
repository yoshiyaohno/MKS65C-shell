#include "yosh.h"

#define MAX_LINE 256

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
            args = parse_args(cmds[i]);
            
            // printf("args:\n");
            // char **oof = args;
            // while(*oof)
            //     printf("<%s>\n", *oof++);
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
