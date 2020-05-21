#define _XOPEN_SOURCE 500
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <signal.h>
#include <errno.h>
#include <sys/mman.h>

#define MAX_AMOUNT 100  //max amount of lines in the file
#define MAX_LEN 80     //max len of the read line

int fd;
off_t file_size;
char *map_file;


void brk_error(const char *const msg) {
    if (errno == 0) {
        fprintf(stderr, "%s", msg);
    } else {
        perror(msg);
    }
    exit(1);
}


void sig_alarm() {
        write(1, map_file, file_size);
        exit(0);
}


int get_line_num() {
        int line_num;
        alarm(5);
        printf("Enter str Number: ");
        while (scanf("%d", &line_num) != 1) {
                alarm(0);
                printf("It's not a string number!\n");
                while (getchar() != '\n');
                alarm(5);
        }
        if(line_num == -1) {
                brk_error("ERROR on scanf ");
        }
        alarm(0);
        return line_num;
}


int main(int argc, char **argv) {
        if (argc != 2) {
                brk_error("Usage: ./a.out file_name\n");
        }

        if ((fd = open(argv[1], O_RDONLY, 0)) == -1) {
                brk_error("Error in opening file");
	}

	int  table[MAX_AMOUNT] = {0};
        int ch_num = 0;
        int lines = 0; 

        if ((file_size = lseek(fd, 0, SEEK_END)) == -1) {
                brk_error("lseek() failed");
        }

        map_file = mmap(0, file_size, PROT_READ, MAP_SHARED, fd, 0);

        if (map_file == MAP_FAILED) {
                if(close(fd)) {
                        perror("ERROR in closing file");
                }
                brk_error("mmap() failed");
        }
                
        
        for (int i = 0; i < file_size; i++) {
                ch_num++;
                if (map_file[i] == '\n') {
                        if (lines == MAX_AMOUNT) {
                                brk_error("Too many strings!");
                        }
                        table[++lines] = ch_num;
                }
        }

        sigset(SIGALRM, sig_alarm);

        int line_num = 0;
        while ((line_num = get_line_num()) != 0) {
                if (line_num < 0 || lines < line_num) {
                        printf("Impossible string number!\n");
                        continue;
                }

                line_num -= 1;
                int off_set = table[line_num];
                int len = table[line_num + 1] - table[line_num];
                printf("%.*s", len, map_file + off_set);
        }

        munmap(map_file, file_size);
        close(fd);
        return 0;
}

