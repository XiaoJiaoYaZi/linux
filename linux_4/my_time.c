#include<time.h>
#include<stdio.h>
#include<unistd.h>
using namespace std;
namespace my_time
{
    void my_time()
    {
        int i;
        time_t the_time;
        for(i=1;i<10;++i)
        {
            the_time = time((time_t*)0);
            printf("the time is %ld\n",the_time);
            sleep(2);
        }
    }
    void my_gmtime()
    {
        struct tm *tm_ptr;
        time_t the_time;
        time(&the_time);
        tm_ptr = gmtime(&the_time);
        printf("Raw time is %ld\n",the_time);
        printf("gmtime gives:\n");
        printf("date: %02d/%02d/%02d\n",tm_ptr->tm_year,tm_ptr->tm_mon,tm_ptr->tm_mday);
        printf("date: %02d:%02d:%02d\n",tm_ptr->tm_hour,tm_ptr->tm_min,tm_ptr->tm_sec);

        time(&the_time);
        tm_ptr = localtime(&the_time);
        printf("local time is %ld\n",the_time);
        printf("gmtime gives:\n");
        printf("date: %02d/%02d/%02d\n",tm_ptr->tm_year,tm_ptr->tm_mon,tm_ptr->tm_mday);
        printf("date: %02d:%02d:%02d\n",tm_ptr->tm_hour,tm_ptr->tm_min,tm_ptr->tm_sec);

        the_time = mktime(tm_ptr);

        printf("asctime the time:%s\n",asctime(tm_ptr));
        printf("ctime the time:%s\n",ctime(&the_time));

    }
}























