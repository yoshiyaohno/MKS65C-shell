#include "yosh.h"

char **parse_args( char *line )
{
    char **args = calloc(8, sizeof(char *)); 
    int i = 0;
    while( line ) {
        args[i] = strsep( &line, " " );
        i++;
    }
    return args;
}

int main(int argc, char *argv)
{
    return 0;
}
