#include "yosh.h"

#define MAX_LINE 512

char *prompt_in(char *buf)
{
    printf(">");
    fgets(buf, MAX_LINE, stdin);
    buf[strlen(buf)-1] = '\0';
    return buf;
}

int run_cmd(char **args)
{
    int child, status;
    if(!strcmp("exit", args[0])) 
        exit(0);
    if((child = fork()) == 0) {
        execvp(args[0], args);
        // only continues if no error
        perror(args[0]);
        exit(1);
    }
    waitpid(child, &status, 0);
    return status;
}

void remove_args(char **args, int from, int count)
{
    while(args[from] = args[count + from++]);
}

void process_redirects(char **args)
{
    int i = 0;
    int sav_stdin  = dup(0);
    int sav_stdout = dup(1);
    int sav_stderr = dup(2);
    int file;
    while(args[i]) {
        if(!strcmp(args[i], ">")) {
            //printf("args[i]: %s\nargs[i+1]: %s\n", args[i], args[i+1]);
            file = open(args[i+1], O_WRONLY | O_CREAT | O_TRUNC);
            if(file == -1) {
                perror("\">\"");
                return;
            }
            dup2(file, 1);
            remove_args(args, i, 2);
        }
        else
            ++i;
    }

    int status = run_cmd(args);

    dup2(sav_stdin,  0);
    dup2(sav_stdout, 1);
    dup2(sav_stderr, 2);
    close(sav_stdin);
    close(sav_stdout);
    close(sav_stderr);
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
            // printf("args:\n");
            // char **oof = args;
            // while(*oof)
            //     printf("<%s>\n", *oof++);
            // printf("done args\n\n");
            if(!args[0]) continue;

            process_redirects(args);

            free(args);
        }

        printf("\nexit status: %i\n", WEXITSTATUS(status));
        free(cmds);
    }

    free(args);
    return 0;
}
