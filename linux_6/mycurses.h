#ifndef MYCURSES_H
#define MYCURSES_H

#include <curses.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
using namespace std;

namespace my_curses
{
    inline void hello()
    {
        initscr();
        move(5,15);
        printw("%s","hello world");
        refresh();
        sleep(2);
        endwin();
    }

    inline void curses_test()
    {
        const char witch_one[] = "first witch";
        const char witch_two[] = "second witch";
        const char *scan_ptr;
        initscr();
        move(5,15);
        attron(A_BOLD);
        printw("%s","macheth");
        attroff(A_BOLD);
        refresh();
        sleep(1);
        move(8,15);
        attron(A_STANDOUT);
        printw("%s","thnder and lighting");
        attroff(A_STANDOUT);
        refresh();
        sleep(1);

        move(10,10);
        printw("%s","when shall we three meet again");
        move(11,23);
        printw("%s","in thunder ,lighting or in rain?");
        move(13,10);
        printw("%s","when the");
        refresh();
        sleep(1);

        attron(A_DIM);
        scan_ptr = witch_one +strlen(witch_one)-1;
        while (scan_ptr != witch_one) {
            move(10,10);
            insch(*scan_ptr--);
        }
        scan_ptr = witch_two +strlen(witch_two)-1;
        while (scan_ptr != witch_two) {
            move(13,10);
            insch(*scan_ptr--);
        }
        attroff(A_DIM);
        move(LINES-1,COLS-1);
        refresh();
        sleep(1);
        endwin();
        strlen(witch_one);
        //scan_ptr = witch_one+strlen(witch_one)-1;
    }
#define PW_LEN 256
#define NAME_LEN 256
    void keyboard()
    {
        char name[NAME_LEN];
        char password[PW_LEN];
        const char *real_password = "xyxyz";
        int i=0;
        initscr();
        move(5,10);
        printw("%s","please login");

        move(7,10);
        printw("%s","usr name");
        move(8,10);
        getstr(name);
        move(9,10);
        printw("%s","password");
        refresh();

        cbreak();
        noecho();
        memset(password,0,sizeof(password));
        while (i<PW_LEN) {
            password[i] = getch();
            if(password[i]=='\n') break;
            move(10,10+i);
            addch('*');
            refresh();
            i++;
        }
        echo();
        nocbreak();
        move(11,10);
        if(strcmp(password,real_password)==0)
            printw("%s","crrect");
        else {
            printw("%s","wrong");
        }
        refresh();
        sleep(2);
        endwin();

    }

    void multiw()
    {
        WINDOW *new_window_ptr;
        WINDOW *popup_window_ptr;
        int x_loop;
        int y_loop;
        char a_letter = 'a';
        initscr();
        move(5,5);
        printw("%s","testing multiple windows");
        refresh();
        for(y_loop=0;y_loop<LINES-1;y_loop++)
        {
            for(x_loop=0;x_loop<COLS-1;x_loop++)
            {
                mvwaddch(stdscr,y_loop,x_loop,a_letter);
                a_letter++;
                if(a_letter>'z') a_letter = 'a';
            }
        }
        refresh();
        sleep(2);
        new_window_ptr = newwin(10,20,5,5);
        mvwprintw(new_window_ptr,2,2,"%s","hello world");
        mvwprintw(new_window_ptr,5,2,"%s","notice how very ong lines wrap inside the window");
        wrefresh(new_window_ptr);
        sleep(2);

        a_letter = '0';
        for(y_loop=0;y_loop<LINES-1;y_loop++)
        {
            for(x_loop=0;x_loop<COLS-1;x_loop++)
            {
                mvwaddch(stdscr,y_loop,x_loop,a_letter);
                a_letter++;
                if(a_letter>'9') a_letter = '0';
            }
        }
        refresh();
        sleep(2);

        wrefresh(new_window_ptr);
        sleep(2);

        touchwin(new_window_ptr);
        wrefresh(new_window_ptr);
        sleep(2);

        popup_window_ptr = newwin(10,20,8,8);
        box(popup_window_ptr,'|','-');
        mvwprintw(popup_window_ptr,5,2,"%s","pop up window");
        wrefresh(popup_window_ptr);
        sleep(2);

        touchwin(new_window_ptr);
        wrefresh(new_window_ptr);
        sleep(2);
        wclear(new_window_ptr);
        wrefresh(new_window_ptr);
        sleep(2);
        delwin(new_window_ptr);

        touchwin(popup_window_ptr);
        wrefresh(popup_window_ptr);
        sleep(2);
        delwin(popup_window_ptr);
        touchwin(stdscr);
        refresh();
        sleep(2);
        endwin();

    }

    void subsc()
    {

    }
}


#endif // MYCURSES_H
