# MKS65C-shell

## implemented features

+ command separation w/ semicolons
+ one can be extremely liberal with spaces
    + except for within tokens, quotation marks don't work yet
+ redirection: `>`, `>>`, `&>`, `&>>`, `2>`, `2>>`, `<`
+ arbitrary numbers of pipes
+ cd and a hopefully nice prompt

## t o _ d o 

+ quotation mark and escape character handling
+ colors and an even nicer prompt
+ all the keyboard input related stuff would be super fun to do but I'm way behind and out of time, god dammit

## bugs

+ I'm pretty sure I covered all the weird token edge cases (at least I tried very hard to), but I may have missed some
    + feel free to try to break the command parsing
+ mixing both file redirectors and pipe redirection just ignores all but the last modifiers; this however happens in bash also

## functions

### yosh.c
#### the main shell loop and misc functions
```C
// print prompt and read input into buf
char *prompt_in(char *buf);

// returns a string with the HH:MM:SS time
char *clock_time(void);

// Runs the shell, until exited or interrupted
int main(int argc, char *argv);
```

### parse.c
#### functions for breaking down input
```C
/*
 *  _split() 
 *      generalized string splitting function
 *  
 *  splits @line along @delims (using strsep)
 *  mallocs a string array for the result, and returns a pointer to it.
 *      (remember to free!)
 *  supports arbitrary numbers of splitees, by making two passes
 *
 */
char **_split(char *line, char *delims);

/*
 *  split a single command into its arguments (removes spaces)
 *  works like _split(), i.e. remember to free the pointer you get.
 *
 */
char **parse_args(char *line);

// count the number of tokens in a command (helper function)
int count_args(char *line);

// _split(), on semicolons
char **split_cmds(char *cmds);

// _split(), on |
char **split_pipes(char *);

// remove leading empty strings from an argument array
void trim_lead_spaces(char **args);

// remove empty strings from an argument array
void trim_spaces(char **args);
```

### redirect.c
#### functions to handle redirection and command execution
```C
// process all redirects in an argument string; alters the file table
//   and does not change it back!
void proc_redirects(char **args);

// change directories, including error checking and ~ (i.e. cd)
void change_dir(char **args);

// handles all piping and redirects to execute a single command with
//   any number of pipes   A T   L E A S T   O N E 
int run_pipes(char **cmds);

// run a command (without redirection), and return its status
int run_cmd(char **args);

// remove @count strings from @args, starting at @from
//  (shift the rest of the array too)
void remove_args(char **args, int from, int count);
```
