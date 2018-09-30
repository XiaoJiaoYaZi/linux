#include <iostream>
#include<time.h>
#include<stdio.h>
#include<unistd.h>
#include "my_time.c"
using namespace std;

int main()
{

    my_time::my_gmtime();
    my_time::my_tempfile();
    my_time::my_sys_info();
    my_time::my_log();
    my_time::my_resource();
    cout << "Hello World!" << endl;
    return 0;
}
