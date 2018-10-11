#ifndef MYLOCK_H
#define MYLOCK_H
#include<unistd.h>
#include<stdio.h>
#include<stdlib.h>
#include<fcntl.h>
#include<gdbm-ndbm.h>
namespace my_lock
{
    void lock_set(int fd,int type)
    {
        struct flock lock;
        lock.l_whence = SEEK_SET;
        lock.l_start = 0;
        lock.l_len = 10;
        while (1) {
            lock.l_type = type;
            if((fcntl(fd,F_SETLK,&lock))==0)
            {
                if(lock.l_type == F_RDLCK)
                {
                    printf("read lock set by %d\n",getpid());
                }
                else if (lock.l_type == F_WRLCK) {
                    printf("write lock set by %d\n",getpid());
                }
                else if (lock.l_type == F_UNLCK) {
                    printf("un lock set by %d\n",getpid());
                }
                return;
            }
            fcntl(fd,F_GETLK,&lock);
            if(lock.l_type != F_ULOCK)
            {
                if(lock.l_type == F_RDLCK)
                {
                    printf("read lock has set by %d\n",lock.l_pid);
                }
                else if (lock.l_type == F_WRLCK) {
                    printf("write lock has set by %d\n",lock.l_pid);
                    getchar();
                }
            }
        }
    }

    void mydbm()
    {

    }

}
#endif // MYLOCK_H
