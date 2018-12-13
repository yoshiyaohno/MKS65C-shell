#include <time.h>
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
#include "redirect.h"

// print prompt and read input into buf
char *prompt_in(char *buf);

// return a string of the time today
char *clock_time(void);
