#include <iostream>
#include<time.h>
#include<stdio.h>
#include<unistd.h>
#include "my_time.c"
using namespace std;

int main()
{

    my_time::my_gmtime();
    cout << "Hello World!" << endl;
    return 0;
}
