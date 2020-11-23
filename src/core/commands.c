/*
 * funcs.c - this file contains functions for console commands
 * 
 * (C) Dmitry Larionov <dlarionov51@gmail.com>
 *
 * This code is lice nsed under the GPL-3.0 License.
 */


#include <stdio.h>
#include <string.h>

#include "./commands.h"


command_t* findcmd(char* name) 
{
    int ptr;

    for (ptr = 0; ptr < sizeof(COMMANDS) / sizeof(command_t); ptr++)
    {
        command_t* cmd = &COMMANDS[ptr];
            if (0 == strcmp(cmd->name, name))
            {
                return cmd;
            }
    }

    return NULL;
}


int smg_help(char** args) 
{
    if (NULL == args[1]) 
    {
        fprintf(stdout, "usage: /help <command>\n");
        return 1;
    }
    
    command_t* cmd = findcmd(args[1]);
    if (NULL != cmd)
    {
        fprintf(stdout, "Help for %s:\n", cmd->name);
        fprintf(stdout, "path to help: %s\n", cmd->hpath); // TODO: read help from file
    } else 
    {
        fprintf(stdout, "Help: there is no %s command!\n", args[1]);
    }
    
    return 1;
}
