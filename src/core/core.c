/*
 * core.c - core part of somgirc that is actually a command line interpreter
 *
 * (C) Dmitry Larionov <dlarionov51@gmail.com>
 *
 * This code is licensed under the GPL-3.0 License.
 */


#include <sys/wait.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "commands.h"



/**
 @brief Execute shell built-in or launch program.
 @param args Null terminated list of arguments.
 @return 1 if the shell should continue running, 0 if it should terminate
 */
int smg_execute(char** args)
{
    char* name = args[0];
    if (NULL == name)
    {
        return 1;
    }

    command_t* cmd = findcmd(name);
    if (NULL == cmd) 
    {
        fprintf(stderr, "There is no %s command!\n", name);
        return 1;
    }

    return (cmd->func)(args);
}


/**
 @brief Read a line of input from stdin.
 @return The line from stdin.
 */
char *lsh_read_line(void)
{
#ifdef LSH_USE_STD_GETLINE
    char *line = NULL;
    ssize_t bufsize = 0; // have getline allocate a buffer for us
    if (getline(&line, &bufsize, stdin) == -1) {
        if (feof(stdin)) {
            exit(EXIT_SUCCESS);  // We recieved an EOF
        } else  {
            perror("lsh: getline\n");
            exit(EXIT_FAILURE);
        }
    }
    return line;
#else
#define LSH_RL_BUFSIZE 1024
    int bufsize = LSH_RL_BUFSIZE;
    int position = 0;
    char *buffer = malloc(sizeof(char) * bufsize);
    int c;
    
    if (!buffer) {
        fprintf(stderr, "lsh: allocation error\n");
        exit(EXIT_FAILURE);
    }
    
    while (1) {
        // Read a character
        c = getchar();
        
        if (c == EOF) {
            exit(EXIT_SUCCESS);
        } else if (c == '\n') {
            buffer[position] = '\0';
            return buffer;
        } else {
            buffer[position] = c;
        }
        position++;
        
        // If we have exceeded the buffer, reallocate.
        if (position >= bufsize) {
            bufsize += LSH_RL_BUFSIZE;
            buffer = realloc(buffer, bufsize);
            if (!buffer) {
                fprintf(stderr, "lsh: allocation error\n");
                exit(EXIT_FAILURE);
            }
        }
    }
#endif
}

#define LSH_TOK_BUFSIZE 64
#define LSH_TOK_DELIM " \t\r\n\a"
/**
 @brief Split a line into tokens (very naively).
 @param line The line.
 @return Null-terminated array of tokens.
 */
char **lsh_split_line(char *line)
{
    int bufsize = LSH_TOK_BUFSIZE, position = 0;
    char **tokens = malloc(bufsize * sizeof(char*));
    char *token, **tokens_backup;
    
    if (!tokens) {
        fprintf(stderr, "lsh: allocation error\n");
        exit(EXIT_FAILURE);
    }
    
    token = strtok(line, LSH_TOK_DELIM);
    while (token != NULL) {
        tokens[position] = token;
        position++;
        
        if (position >= bufsize) {
            bufsize += LSH_TOK_BUFSIZE;
            tokens_backup = tokens;
            tokens = realloc(tokens, bufsize * sizeof(char*));
            if (!tokens) {
                free(tokens_backup);
                fprintf(stderr, "lsh: allocation error\n");
                exit(EXIT_FAILURE);
            }
        }
        
        token = strtok(NULL, LSH_TOK_DELIM);
    }
    tokens[position] = NULL;
    return tokens;
}

/**
 @brief Loop getting input and executing it.
 */
void smg_loop(void)
{
    char* line;
    char** args;
    int status;
    
    do {
        printf("> ");
        line = lsh_read_line();

        if (line[0] == '/')
        {
            args = lsh_split_line(line + 1);
            status = smg_execute(args);
            free(args);
        } else {
            // TODO: msg from @
            fprintf(stderr, "%s\n", line);
            status =  1;
        }

        free(line);
    } while (status);
}

