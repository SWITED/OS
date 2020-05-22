#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int print_status(int status)
{
    if(WIFEXITED(status))
    {
        printf("exit with status: %d\n", WEXITSTATUS(status));
        return 0;
    }
    if(WIFSIGNALED(status))
    {
        printf("end after signal with number: %d\n", WTERMSIG(status));
        return 0;
    }

    return -1;
}

int main(int argc, char **argv){
    int status;

    if(argc < 2) {
        printf("Usage: %s parameters \n",argv[0]);
        return -1;
    }
    
    pid_t proc_id = fork();
    if (proc_id == -1) {
        perror("FORK ERROR: Can't create child process");
        return -1;
    }
    
    if(proc_id == 0) {
        execvp(argv[1], &argv[1]);
        perror(argv[1]);
        return -1;
    }
    if(proc_id > 0) {
        printf("Hey i'm in parent, pid=%d,fork returned=%d\n", getpid(), proc_id);
        pid_t wait_return = wait(&status);

        if(wait_return == -1) {
            perror("wait ERROR");
            return -1;
        }
        }
    return print_status(status);
}

