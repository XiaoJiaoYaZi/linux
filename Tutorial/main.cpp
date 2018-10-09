#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "TutorialConfig.h"
#ifdef USE_MYMATH
#include "mathfunctions.h"
#endif
using namespace std;

int main(int argc, char *argv[])
{
    if(argc <2){
        fprintf(stdout,"%s Version %d.%d\n",
                argv[0],
                Tutorial_VERSION_MAJOR,
                Tutorial_VERSION_MINOR);
        fprintf(stdout,"usage : %s numb\n",argv[0]);
        exit(1);
    }
    double inputValue = atof(argv[1]);
#ifdef USE_MYMATH
    double outputValue = mysqrt(inputValue);
#else
    double outputValue = sqrt(inputValue);
#endif
    fprintf(stdout,"thie quare root of %f is %f\n",inputValue,outputValue);

    cout << "Hello World!" << endl;
    return 0;
}
