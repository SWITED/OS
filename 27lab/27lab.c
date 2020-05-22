#include <stdio.h>
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

        fclose(fin);
        pclose(fout);
        return 0;
}
