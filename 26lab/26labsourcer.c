#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>
#include <sys/types.h>
#include <wait.h>

#define STRINGS_NUM 3

int main() {
        FILE *fout;
        char *strings[STRINGS_NUM] ={ "deadline\n","lover\n","Nikita\n"};
        int stat;

        fout = popen("./receiver.exe", "w");
        if(fout == NULL) {
            perror("popenError : STR10");
            return -1;
        }

        for(int i=0; i<STRINGS_NUM; i++) {
            if(fprintf(fout, "%s", strings[i]) != strlen(strings[i])) {
                perror("fprintfError");
                if(pclose(fout) == -1) {
                    perror("pcloseError");
                    return -1;
                }
                return -1;
            }
        }

        stat = pclose(fout);

        if (WIFEXITED(stat) == 0 ) {
            fprintf(stderr,"ploseError1 start : %d : STR28", stat); 
            return -1;
        }
        if (WEXITSTATUS(stat) != 0) {
            fprintf(stderr,"ploseError2 start : %d : STR28", stat); 
            return -1;
        }      
        return 0;
}

