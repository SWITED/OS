#include <stdio.h>
#include <sys/wait.h>
#define BUFFER_SIZE 100

int main(int argc, char **argv) {
        FILE *fin;
        char buff[BUFFER_SIZE];
        int ret;

        if(argc < 2) {
            fprintf(stderr, "usage: %s filename\n",argv[0]);
            return -1;
        }
    
        snprintf(buff, sizeof(buff), "cat %s | grep '^$' | wc -l", argv[1]);
        
        fin = popen(buff, "r");

        if(fin == NULL) {
            perror("popen ERROR:STR20");
            return -1;
        }
        fscanf(fin, "%d", &ret);

        int stat = pclose(fin);
        if(stat = -1){
            perror("pclose ERROR : STR25");
            return -1;
        }

        if (WIFEXITED(stat) == 0 ) {
            fprintf(stderr,"plose ERROR1 stat : %d : STR29", stat); 
            return -1;
        }
        if (WEXITSTATUS(stat) != 0) {
            fprintf(stderr,"plose ERROR2 stat : %d : STR29", stat); 
            return -1;
        }          
        printf("answer : %d\n", ret);
        return 0;
}

        


