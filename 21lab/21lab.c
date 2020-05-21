
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>

int Sound_CNT;
char buffer[BUFSIZ]; //8192 on my PC
int devTERM;


void signal_int(int sig) {

    if (write(devTERM,"\a",strlen("\a")) == -1) {
        perror("SIGINT ERROR");
        exit(0);
    }
    Sound_CNT++;
    if(signal(SIGINT, signal_int) == SIG_ERR) {
        perror("SIGINT ERROR");
        exit(0);
    }
}


void signal_quit(int sig) {
    snprintf(buffer, BUFSIZ, "\nCount of bells = %d\n", Sound_CNT); 

    if (write(devTERM, buffer, strlen(buffer)) == -1) {
        perror("WRITE ERROR");
        exit(0);
    }
    if(close(devTERM) == -1) {
        perror("CLOSE ERROR");
        exit(0);
    }
    exit(1);
}


int main() {
    if (devTERM = open("/dev/tty", O_RDWR) == -1) { 
        perror("dev/tty");
        return -1;
    }

    if(signal(SIGINT, signal_int) == SIG_ERR) {
        perror("SIGINT ERROR");
        return -1;
    }
   
    signal(SIGQUIT, signal_quit);
    while (1) {
        pause();
    }
}

