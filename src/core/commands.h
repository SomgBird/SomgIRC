/*
 * commands.h - this file contains array of all commands
 * 
 * (C) Dmitry Larionov <dlarionov51@gmail.com>
 *
 * This code is lice nsed under the GPL-3.0 License.
 */


#ifndef __COMMANDS_H_
#define __COMMANDS_H_ 1

typedef struct command_t
{
    char* name;
    char* hpath;
    int (*func)(char** args);
} command_t;


command_t* findcmd(char*);
int smg_help(char**);


static command_t COMMANDS[] = {
    {
        .name = "help",
        .hpath = "hpath",
        .func = &smg_help
    }
};

#endif
