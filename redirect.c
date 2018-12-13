#include "redirect.h"

#define PIPE_RD 0
#define PIPE_WR 1

// process all redirects in an argument string; alters the file table
//   and does not change it back!
void proc_redirects(char **args)
{
    int i = 0;
    // int sav_stdin  = dup(0);
    // int sav_stdout = dup(1);
    // int sav_stderr = dup(2);
    int file;
    while(args[i]) {
        if(!strcmp(args[i], ">")) {
            file = open(args[i+1], O_WRONLY | O_CREAT | O_TRUNC);
            if(file == -1) {
                perror("\">\"");
                return;
            }
            dup2(file, 1);
            remove_args(args, i, 2);
        }
        else if(!strcmp(args[i], ">>")) {
            file = open(args[i+1], O_WRONLY | O_CREAT | O_APPEND);
            if(file == -1) {
                perror("\">>\"");
                return;
            }
            dup2(file, 1);
            remove_args(args, i, 2);
        }
        else if(!strcmp(args[i], "2>")) {
            file = open(args[i+1], O_WRONLY | O_CREAT | O_TRUNC);
            if(file == -1) {
                perror("\"2>\"");
                return;
            }
            dup2(file, 2);
            remove_args(args, i, 2);
        }
        else if(!strcmp(args[i], "2>>")) {
            file = open(args[i+1], O_WRONLY | O_CREAT | O_APPEND);
            if(file == -1) {
                perror("\"2>>\"");
                return;
            }
            dup2(file, 2);
            remove_args(args, i, 2);
        }
        else if(!strcmp(args[i], "&>")) {
            file = open(args[i+1], O_WRONLY | O_CREAT | O_TRUNC);
            if(file == -1) {
                perror("\"&>\"");
                return;
            }
            dup2(file, 2);
            dup2(file, 1);
            remove_args(args, i, 2);
        }
        else if(!strcmp(args[i], "&>>")) {
            file = open(args[i+1], O_WRONLY | O_CREAT | O_APPEND);
            if(file == -1) {
                perror("\"&>>\"");
                return;
            }
            dup2(file, 2);
            dup2(file, 1);
            remove_args(args, i, 2);
        }
        else if(!strcmp(args[i], "<")) {
            file = open(args[i+1], O_RDONLY);
            if(file == -1) {
                perror("\"<\"");
                return;
            }
            dup2(file, 0);
            remove_args(args, i, 2);
        }
        else
            ++i;
    }
}

// change directories, including error checking and ~ (i.e. cd)
void change_dir(char **args)
{
    char *home = getenv("HOME");
    if(!args || strcmp("cd", args[0]))
        return; // why would you do this
    if(!args[1] || !strcmp("~", args[1])) {
        if(chdir(home) == -1)
            perror("cd");
    }
    else {
        if(chdir(args[1]) == -1)
            perror("cd");
    }
}

// handles all piping and redirects to execute a single command with
//   any number of pipes   A T   L E A S T   O N E 
int run_pipes(char **cmds)
{
    // maybe this is bad coding but beacuse of how this is used
    //   in the main shell function I can assume there is at least
    //   one pipe in the input
    int i = 0;
    int child, status;
    int p[2];
    int sav_stdin = dup(0);
    while(cmds[i+1]) {
        if(pipe(p) == -1)
            perror("pipe");
        if(fork() == 0) {
            char **l_args = parse_args(cmds[i]);
            if(close(p[PIPE_RD]) == -1)
                perror("pipe close");
            if(dup2(p[PIPE_WR], 1) == -1)
                perror("dup2");
            run_cmd(l_args);
            free(l_args);
            exit(0);
        }
        else {
            if(close(p[PIPE_WR]) == -1)
                perror("pipe close");
            if(dup2(p[PIPE_RD], 0) == -1)
                perror("dup2");
        }
        ++i;
    }
    char **args = parse_args(cmds[i]);
    status = run_cmd(args);
    dup2(sav_stdin, 0);
    return status;
}

// run a command (now with redirection), and return its status
int run_cmd(char **args)
{
    int child, status;
    if(!strcmp("exit", args[0])) 
        exit(0);
    else if(!strcmp("cd", args[0])) 
        change_dir(args);
    else if((child = fork()) == 0) {
        proc_redirects(args);
        execvp(args[0], args);
        // only continues if no error
        perror(args[0]);
        exit(1);
    }
    //printf("[run_cmd] command is run\n");
    waitpid(child, &status, 0);
    return status;
}

// remove @count strings from @args, starting at @from
//  (shift the rest of the array too)
void remove_args(char **args, int from, int count)
{
    while(args[from] = args[count + from++]);
}
