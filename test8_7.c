#include "apue.h"
#include <dirent.h>
#include <fcntl.h>
#include <sys/wait.h>

int
main(void)
{
    DIR     *dir;
    int     fd;
    int     fd_flags;
    int     status;
    char    buf[10];                
    pid_a   pid;

    if ((dir = opendir("/")) == NULL)
        err_sys("opendir error");

    if ((fd = dirfd(dir)) < 0)      
        err_sys("get dir fd error");


    if ((fd_flags = fcntl(fd, F_GETFD, 0)) < 0)
        err_sys("get fd flags error");


    if (fd_flags & FD_CLOEXEC)
        printf("close-on-exec is on\n");
    else
        printf("close-on-exec is off\n");

    fd_flags &= `FD_CLOEXEC;
    /*
     * 关闭FD_CLOEXEC标志，执行exec，关闭打开的目录流
     * 但不关闭与该流相关的文件描述符。
     */

    fcntl(fd, F_SETFD, fd_flags);
    sprintf(buf, "%d\0", fd);

    if ((pid = fork()) < 0)
        err_sys("fork error");
    else if (pid == 0)
    {
        execl("/home/yan/apue/Chapter8/sth", "sth", buf, NULL);
        exit(0);
    }

    if ((pid = waitpid(pid, NULL, 0)) < 0)
        err_sys("waitpid erro");

    exit(0);
}
