#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

int main(int argc, char** argv) {
    int maybe_error, status;
        
    if (argc < 2) {
        printf("Usage: ./a.out file_name\n");
        return -1;
    }

    pid_t proc_id = fork();

    if(proc_id == -1) {
        perror("FORK ERROR: Can't create child process");
        return -1;
    }

    if(proc_id > 0) {
        printf("Hey i'm in parent, pid=%d,fork returned=%d\n", getpid(), proc_id);
        pid_t wait_return = wait(&status);

        if(wait_return == -1) {
            perror("wait ERROR");
            return -1;
        }

        printf("\nI'm in parent now, my child status is %d\n", WEXITSTATUS(status));
    }

    if(proc_id == 0) {
        maybe_error = execvp("cat",argv);
        if(maybe_error == -1) {
            perror("Execvp ERROR");
            return -1;
        }  
    }
    return 0;
}

