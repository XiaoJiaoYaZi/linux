#include<time.h>
#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<sys/types.h>
#include<pwd.h>
#include<sys/utsname.h>
#include<syslog.h>
#include<sys/resource.h>
#include<limits>
#include<sys/time.h>
#include<math.h>
#include<iostream>
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


/*
 *  %a  z
 *
*/
        char tm_buf[128];
        strftime(tm_buf,sizeof (tm_buf),"%Y %m %d %I:%M:%S %P",tm_ptr);
        printf("strftime :  %s\n",tm_buf);

        char *result;
        result = strptime(tm_buf,"",tm_ptr);
        printf("strptime :  %s\n",result);
    }
    void my_tempfile()
    {
        //tmpnam/tempfile

        char tempname[128] = "helloworld";
        char *filename;
        FILE *tmpfp;
        filename = tmpnam(tempname);
        printf("tempnam : %s\n",filename);
        tmpfp = tmpfile();
        printf("tmpfile ID :%d\n",tmpfp);

        //char* maktemp_name = mktemp("XXXXXX");
        //printf("%s\n",maktemp_name);

//        int id = mkstemp("helloXXXXXX");
//        printf("ID:%d\n",id);
    }
    void my_sys_info()
    {
        uid_t uid;
        gid_t gid;
        uid = geteuid();
        gid = getgid();

        struct passwd *pw;
        printf("Usr is %s\n",getlogin());
        printf("Usr ID: uid=%d,gid=%d\n",uid,gid);

        pw = getpwuid(uid);
        printf("uid pwd :\n name=%s,uid=%d,gid=%d,home=%s,shell=%s,pwd=%s\n",
               pw->pw_name,pw->pw_uid,pw->pw_gid,pw->pw_dir,pw->pw_shell,pw->pw_passwd);
        pw = getpwnam(("root"));
        printf("root pwd :\n name=%s,uid=%d,gid=%d,home=%s,shell=%s,pwd=%s\n",
               pw->pw_name,pw->pw_uid,pw->pw_gid,pw->pw_dir,pw->pw_shell,pw->pw_passwd);

        char computer[256];
        struct utsname uts;
        gethostname(computer,256);
        uname(&uts);
        printf("computer host name is %s\n",computer);
        printf("System is %s on %s hardware\n",uts.sysname,uts.machine);
        printf("nodename is %s\n",uts.nodename);
        printf("version is %s, %s\n",uts.release,uts.version);

        printf("hostid : %d\n",gethostid());
    }
    void my_log()
    {
        FILE *f = fopen("not_here","r");
        if(!f){
            syslog(LOG_ERR|LOG_USER,"oops - %m\n");
        }

        openlog("logmask",LOG_PID|LOG_CONS,LOG_USER);
        syslog(LOG_INFO,"information message,pid=%d\n",getpid());
        syslog(LOG_ERR,"error message\n");

    }
    void test_work()
    {
        FILE *f = NULL;
        int i=0;
        double x = 4.5;
        f = tmpfile();
        for(i=0;i<10000;i++)
        {
            fprintf(f,"do some output\n");
            if(ferror(f))
            {
                fprintf(stderr,"error writing to template file\n");
                return ;
            }
        }
        for(i=0;i<100000;i++)
        {
            x = log(x*x+3.21);
        }
    }
    void my_resource()
    {

        struct rusage r_usage;
        struct rlimit r_limit;
        int priority;
        test_work();
        getrusage(RUSAGE_SELF,&r_usage);
        printf("cpu usage:usr = %ld,%ld,system = %ld,%ld\n",
               r_usage.ru_utime.tv_sec,r_usage.ru_utime.tv_usec,
               r_usage.ru_stime.tv_sec,r_usage.ru_utime.tv_usec);
        priority = getpriority(PRIO_PROCESS,getpid());
        printf("current progress priority = %d\n",priority);
        getrlimit(RLIMIT_FSIZE,&r_limit);
        printf("current file limit :soft=%ld,hard=%ld\n",
               r_limit.rlim_cur,r_limit.rlim_max);

    }

}























