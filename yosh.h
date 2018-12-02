#include <stdio.h>
#include <fcntl.h>
#include <errno.h>
#include <stdlib.h>
#include <unistd.h>
#include <dirent.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <sys/types.h>

#include "parse.h"

// print prompt and read input into buf
char *prompt_in(char *buf);

// execvp, including error checking
void run_cmd(char **args);
