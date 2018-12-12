#include "ooof.h"

// // dear god is this function ugly
// int ooof(char **args)
// {
//     int i = 0;
//     int sav_stdin  = dup(0);
//     int sav_stdout = dup(1);
//     int sav_stderr = dup(2);
//     int file;
//     while(args[i]) {
//         if(!strcmp(args[i], ">")) {
//             file = open(args[i+1], O_WRONLY | O_CREAT | O_TRUNC);
//             if(file == -1) {
//                 perror("\">\"");
//                 return -1;
//             }
//             dup2(file, 1);
//             remove_args(args, i, 2);
//         }
//         else if(!strcmp(args[i], ">>")) {
//             file = open(args[i+1], O_WRONLY | O_CREAT | O_APPEND);
//             if(file == -1) {
//                 perror("\">>\"");
//                 return -1;
//             }
//             dup2(file, 1);
//             remove_args(args, i, 2);
//         }
//         else if(!strcmp(args[i], "2>")) {
//             file = open(args[i+1], O_WRONLY | O_CREAT | O_TRUNC);
//             if(file == -1) {
//                 perror("\"2>\"");
//                 return -1;
//             }
//             dup2(file, 2);
//             remove_args(args, i, 2);
//         }
//         else if(!strcmp(args[i], "2>>")) {
//             file = open(args[i+1], O_WRONLY | O_CREAT | O_APPEND);
//             if(file == -1) {
//                 perror("\"2>>\"");
//                 return -1;
//             }
//             dup2(file, 2);
//             remove_args(args, i, 2);
//         }
//         else if(!strcmp(args[i], "&>")) {
//             file = open(args[i+1], O_WRONLY | O_CREAT | O_TRUNC);
//             if(file == -1) {
//                 perror("\"&>\"");
//                 return -1;
//             }
//             dup2(file, 2);
//             dup2(file, 1);
//             remove_args(args, i, 2);
//         }
//         else if(!strcmp(args[i], "&>>")) {
//             file = open(args[i+1], O_WRONLY | O_CREAT | O_APPEND);
//             if(file == -1) {
//                 perror("\"&>>\"");
//                 return -1;
//             }
//             dup2(file, 2);
//             dup2(file, 1);
//             remove_args(args, i, 2);
//         }
//         else if(!strcmp(args[i], "<")) {
//             file = open(args[i+1], O_RDONLY);
//             if(file == -1) {
//                 perror("\"<\"");
//                 return -1;
//             }
//             dup2(file, 0);
//             remove_args(args, i, 2);
//         }
//         else
//             ++i;
//     }
// 
//     int status = run_cmd(args);
// 
//     dup2(sav_stdin,  0);
//     dup2(sav_stdout, 1);
//     dup2(sav_stderr, 2);
//     close(file);
//     close(sav_stdin);
//     close(sav_stdout);
//     close(sav_stderr);
// 
//     return status;
// }

void proc_redirects(char **args)
{
    int i = 0;
    int sav_stdin  = dup(0);
    int sav_stdout = dup(1);
    int sav_stderr = dup(2);
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

// run a command (without redirection), and return its status
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
