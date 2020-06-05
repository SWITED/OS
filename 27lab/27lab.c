#include <stdio.h>
#include <sys/wait.h>
#define BUFFER_SIZE 256

int main(int argc, char **argv) {
        FILE *fin, *fout;

        if(argc < 2) {
            fprintf(stderr, "usage: %s filename\n",argv[0]);
            return -1;
        }
    
        char buff[BUFFER_SIZE];

        if ((fin = fopen(argv[1], "r")) == NULL) {
                perror("fopen ERROR");
                return -1;
        }
        
        fout = popen("wc -l", "w");

        if(fout == NULL) {
            perror("popen ERROR");
            return -1;
        }
        
        while (fgets(buff, BUFFER_SIZE, fin) != NULL) {

            if (buff[0] == '\n') {
                fputs(buff, fout);
            }

        }
        if(fclose(fin) == -1) {
            perror("Close ERROR");
            return -1;
        }
        int peclose = pclose(fout);
        if (WIFEXITED(peclose) != 0 && WEXITSTATUS(peclose) == 0) {
            return 0;
        }
        return -1;
}
