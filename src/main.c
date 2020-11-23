/*
 * main.c - main file of somgirc
 *
 * (C) Dmitry Larionov <dlarionov51@gmail.com>
 *
 * This code is licensed under the GPL-3.0 License.
 */


#include <stdio.h>
#include <ncurses.h>

#include "./core/core.h"


int main()
{
    // initscr();            /* Start curses mode           */
    // printw("Hello World !!!");    /* Print Hello World          */
    // refresh();            /* Print it on to the real screen */
    // getch();            /* Wait for user input */
    // endwin();            /* End curses mode          */


    // fprintf(stdout, "%s\n", COMMANDS[0].name);
    // fprintf(stdout, "%s\n", COMMANDS[0].hpath);

    // har* buff_1[1] = {"test_arg"};
    // COMMANDS[0].func(1, buff_1);

    // char* buff_2[1] = {"smg_help"};
    // COMMANDS[0].func(1, buff_2);

    smg_loop();

    return 0;
}
