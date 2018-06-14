#include "apue.h"
#include <fcntl.h>

int
main(int argc, char *argv[])
{
    int     fd, fd_flags;

    sscanf(argv[1], "%d", &fd);
    if  ((fd_flags = fcntl(fd, F_GETFD)) < 0)
        err_sys("get fd flags error");

    if (fd_flags & FD_CLOEXEC)
        printf("close-on-exec is on\n");
    else
        printf("close-on-exec is off\n");
    exit(0);

}


/*
     * 查找资料完成
     * 测试关闭 FD_CLOEXEC 标志，子进程是否能再次与打开目录流关联的打开文件描述符
     * 此时，子进程能正确打开与打开目录流关联的文件描述符fd。且是在fd的FD_CLOEXEC标志被关闭的前提下打开。 
     * 因此可以得出结论：系统默认保持 FD_CLOEXEC 标志打开，执行exec的时候会关闭打开目录的文件描述符。
*/
