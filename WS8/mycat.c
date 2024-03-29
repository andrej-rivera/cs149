#include "apue.h"

#define BUFSIZE	   4096

int
main(void)
{
    int    n;
    char   buf[BUFSIZE];
    
    while ((n = read(STDIN_FILENO, buf, BUFSIZE)) > 0) {
        if (write(STDOUT_FILENO, buf, n) != n)
            err_sys("write error");
        fprintf(stderr, "Bytes read from stdin: %d\n", n);
    }  
    
    if (n < 0)
        err_sys("read error");
        
    exit(0);
}
