#include <stdio.h>
#include <ctype.h>
#include <unistd.h>
#include <sys/types.h>
#include <string.h>
#include <wait.h>
#include <errno.h>

#define MSG_SIZE 100

int main() {
    int fd[2];
    if(pipe(fd) == -1) {
        perror("pipe ERROR");
        return -1;
    }

    pid_t proc_id = fork();

    if(proc_id == -1) {
        perror("FORK ERROR: Can't create child process");
        return -1;
    }

    if(proc_id == 0) {
        char* messageOut = "BiG BrOtHeR is WAtching yoU!\n";

        if(write(fd[1], messageOut, strlen(messageOut)) == -1) {

            if(close(fd[0]) == -1) {
                perror("Close ERROR1");
                return -1;
            }

            perror("write ERROR!");
        }

    }

    if(close(fd[1]) == -1) {
        perror("Close ERROR2");
        return -1;
    }

    char messageIn[MSG_SIZE];

    if(read(fd[0], messageIn, MSG_SIZE) <= 0) {

        if(errno == EINTR){
            errno = 0;
        }

    }

    for(int i = 0; i < strlen(messageIn); i++) {
            printf("%c", (char)toupper(messageIn[i]));
    }

    if(close(fd[0]) == -1) {
        perror("Close ERROR3");
        return -1;
    }
    
    return 0;
}
