#include <iostream>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <termio.h>
#include <termios.h>
#include "myterm.c"
using namespace std;

int main()
{
    isatty(fileno(stdout));
//    struct termios initset,newset;
//    char pwd[9];
//    tcgetattr(fileno(stdin),&initset);
//    newset = initset;
//    newset.c_lflag  &=  ~ECHO;
//    printf("input pwd:\n");
//    if(tcsetattr(fileno(stdin),TCSAFLUSH,&newset)!=0)
//    {
//        fprintf(stderr,"could not set atrribute\n");
//    }
//    //fprintf(stderr,"could not set atrribute\n");
//    fgets(pwd,8,stdin);
//    tcsetattr(fileno(stdin),TCSANOW,&initset);

    int ch = 0;
//    my_term::init_keyboard();
//    while (ch != 'q') {
//        printf("looping\n");
//        sleep(1);
//        if(my_term::kbhit()){
//            ch = my_term::readch();
//            printf("you hit %c\n",ch);
//        }
//    }
//    my_term::close_keyboard();



    cout << "Hello World!" << endl;
    return 0;
}
