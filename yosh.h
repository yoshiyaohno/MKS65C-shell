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

char **_split(char *line, char *delims, int maxlen);
char **parse_args(char *line);
char *prompt_in(char *buf);
